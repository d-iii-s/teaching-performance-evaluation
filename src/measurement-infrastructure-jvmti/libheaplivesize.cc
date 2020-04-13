// An example JVMTI agent that collects the number of objects on the heap.
// - All and live object count reported at VM init and VM death.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jni.h"
#include "jvmti.h"


// --------------------------------------------------------------
// Heap Traversal

// Heap iteration callback simply increments object counter.
static jint JNICALL heap_iteration_callback_object_counter (jlong class_tag, jlong size, jlong *tag_ptr, jint length, void *user_data) {
    long *counter = (long*) user_data;
    (*counter) ++;
    return (0);
}

long count_objects_on_heap (jvmtiEnv * jvmti ) {

    // Prepare the callback structure.
    jvmtiHeapCallbacks heapCallbacks;
    memset (&heapCallbacks, 0, sizeof (heapCallbacks));
    heapCallbacks.heap_iteration_callback = &heap_iteration_callback_object_counter;

    // Iterates through all objects on the heap (both live and dead) in no particular order.
    // Heap is guaranteed to be constant during iteration (including object states).
    long counter = 0;
    jvmti->IterateThroughHeap (0, NULL, &heapCallbacks, &counter);

    return (counter);
}


// --------------------------------------------------------------
// Garbage Collection Callbacks

static void gc_start (jvmtiEnv *jvmti) {
    printf ("[GCSTART] GC start event executed\n");
    // It may look tempting to do the heap count here,
    // but JVMTI does not permit heap traversal
    // inside memory callback handlers.
}

static void gc_finish(jvmtiEnv *jvmti) {
    printf ("[GCFINISH] GC finish event executed\n");
    // It may look tempting to do the heap count here,
    // but JVMTI does not permit heap traversal
    // inside memory callback handlers.
}


// --------------------------------------------------------------
// Virtual Machine Lifecycle Callbacks

static void JNICALL vm_start (jvmtiEnv *jvmti, JNIEnv *env) {
    printf ("[VMSTART] Virtual machine start callback executed\n");
}

static void JNICALL vm_init (jvmtiEnv *jvmti, JNIEnv *env, jthread thread) {
    printf ("[VMINIT] Virtual machine initialization callback started\n");

    long count_all = count_objects_on_heap (jvmti);
    jvmti->ForceGarbageCollection ();
    long count_live = count_objects_on_heap (jvmti);
    printf ("Saw %ld objects of which %ld were live\n", count_all, count_live);

    printf ("[VMINIT] Virtual machine initialization callback finished\n");
}

static void JNICALL vm_death (jvmtiEnv *jvmti, JNIEnv *env) {
    printf("[VMDEATH] Virtual machine death callback started\n");

    long count_all = count_objects_on_heap (jvmti);
    jvmti->ForceGarbageCollection ();
    long count_live = count_objects_on_heap (jvmti);
    printf ("Saw %ld objects of which %ld were live\n", count_all, count_live);

    // Disable event callbacks
    jvmtiEventCallbacks callbacks;
    memset (&callbacks, 0, sizeof (callbacks));
    jvmti->SetEventCallbacks (&callbacks, (jint) sizeof (callbacks));

    printf ("[VMDEATH] Virtual machine death callback finished\n");
}

JNIEXPORT jint JNICALL Agent_OnLoad (JavaVM *vm, char *options, void *reserved) {
    printf ("[ONLOAD] Agent load callback started\n");

    // Get JVMTI environment.
    jvmtiEnv *jvmti;
    jint rc = vm->GetEnv ((void**)(&jvmti), JVMTI_VERSION);
    if (rc != JNI_OK) return (-1);

    jvmtiCapabilities capabilities;
    memset (&capabilities, 0, sizeof (capabilities));
    capabilities.can_generate_garbage_collection_events = 1;
    capabilities.can_tag_objects = 1;

    jvmtiError err = jvmti->AddCapabilities (&capabilities);
    if (err != JVMTI_ERROR_NONE) return (-1);

    // Set callbacks and enable event notifications
    jvmtiEventCallbacks callbacks;
    memset (&callbacks, 0, sizeof (callbacks));
    callbacks.VMInit = &vm_init;
    callbacks.VMStart = &vm_start;
    callbacks.VMDeath = &vm_death;
    callbacks.GarbageCollectionStart = &gc_start;
    callbacks.GarbageCollectionFinish = &gc_finish;
    jvmti->SetEventCallbacks (&callbacks, sizeof (callbacks));

    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_START, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, (jthread) NULL);

    printf ("[ONLOAD] Agent load callback finished\n");

    return (JNI_OK);
}

JNIEXPORT void JNICALL Agent_OnUnload (JavaVM *vm) {
    printf ("[ONUNLOAD] Agent unload callback executed\n");
}
