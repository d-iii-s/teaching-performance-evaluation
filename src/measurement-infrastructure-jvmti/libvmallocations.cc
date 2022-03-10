// An example JVMTI agent that monitors object allocations done by the JVM.
// - Lifecycle reported individually for each JVM allocated object.
// - Summary per class reported at VM init and VM death.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jni.h"
#include "jvmti.h"

using namespace std;

// Should really be atomic.
jlong tag_to_use = 1;


// --------------------------------------------------------------
// Heap Traversal

// Heap iteration callback simply increments object counter.
static jint JNICALL heap_iteration_callback_object_counter (jlong class_tag, jlong size, jlong *tag_ptr, jint length, void *user_data) {
    long *counter = (long*) user_data;
    (*counter) ++;
    return (0);
}

static void summarize_heap_loaded_classes (jvmtiEnv *jvmti) {

    // Prepare the callback structure.
    jvmtiHeapCallbacks heapCallbacks;
    memset (&heapCallbacks, 0, sizeof (heapCallbacks));
    heapCallbacks.heap_iteration_callback = &heap_iteration_callback_object_counter;

    // Get the list of all loaded classes.
    jint count;
    jclass *classes;
    jvmti->GetLoadedClasses (&count, &classes);

    // Do a heap traversal for each class to count the number of allocated instances.
    // The traversal is limited to tagged objects, the agent tags on JVM object allocation.
    for (int i = 0 ; i < count ; i++) {
        char *signature;
        jvmti->GetClassSignature (classes [i], &signature, NULL);
        long counter = 0;
        jvmti->IterateThroughHeap (JVMTI_HEAP_FILTER_TAGGED, classes [i], &heapCallbacks, &counter);
        if (counter != 0) printf ("%ld instances of class %s\n", counter, signature);
        jvmti->Deallocate ((unsigned char *) signature);
    }

    jvmti->Deallocate ((unsigned char *) classes);
}


// --------------------------------------------------------------
// Object Allocation Event Callbacks

static void JNICALL vm_objectAlloc (jvmtiEnv *jvmti, JNIEnv* jni, jthread thread, jobject object, jclass object_klass, jlong size) {
    char *signature;
    if (size > 0) {
        jvmti->GetClassSignature (object_klass, &signature, NULL);
        if (signature != NULL) {
            printf ("[ALLOC] JVM allocated object #%ld of type %s and size %ld\n", tag_to_use, signature, size);
            jvmti->SetTag (object, tag_to_use);
            tag_to_use ++;
            jvmti->Deallocate ((unsigned char*) signature);
        }
    }
}

static void JNICALL vm_objectFree (jvmtiEnv *jvmti, jlong tag) {
    // Free event is only reported for tagged objects.
    printf ("[FREE] GC collected object #%ld\n", tag);
}


// --------------------------------------------------------------
// Virtual Machine Lifecycle Callbacks

static void JNICALL vm_start (jvmtiEnv *jvmti, JNIEnv *env) {
    printf ("[VMSTART] Virtual machine start callback executed\n");
}

static void JNICALL vm_init (jvmtiEnv *jvmti, JNIEnv *env, jthread thread) {
    printf ("[VMINIT] Virtual machine initialization callback started\n");
    summarize_heap_loaded_classes (jvmti);
    printf ("[VMINIT] Virtual machine initialization callback finished\n");
}

static void JNICALL vm_death (jvmtiEnv *jvmti, JNIEnv *env) {
    printf("[VMDEATH] Virtual machine death callback started\n");

    // Force full garbage collection so that garbage is released.
    jvmti->ForceGarbageCollection ();
    summarize_heap_loaded_classes (jvmti);

    // Disable event callbacks
    jvmtiEventCallbacks callbacks;
    memset (&callbacks,0, sizeof (callbacks));
    jvmti->SetEventCallbacks (&callbacks, (jint) sizeof(callbacks));

    printf ("[VMDEATH] Virtual machine death callback finished\n");
}

JNIEXPORT jint JNICALL Agent_OnLoad (JavaVM *vm, char *options, void *reserved) {
    printf ("[ONLOAD] Agent load callback started\n");

    // Get JVMTI environment.
    jvmtiEnv *jvmti;
    jint rc = vm->GetEnv ((void**)(&jvmti), JVMTI_VERSION);
    if (rc != JNI_OK) return (-1);

    jvmtiCapabilities capabilities;
    memset (&capabilities,0, sizeof (capabilities));
    capabilities.can_tag_objects = 1;
    capabilities.can_signal_thread = 1;
    capabilities.can_get_owned_monitor_info = 1;
    capabilities.can_generate_vm_object_alloc_events = 1;
    capabilities.can_generate_object_free_events = 1;
    capabilities.can_generate_garbage_collection_events = 1;

    jvmtiError err = jvmti->AddCapabilities (&capabilities);
    if (err != JVMTI_ERROR_NONE) return (-1);

    // Set callbacks and enable event notifications
    jvmtiEventCallbacks callbacks;
    memset (&callbacks, 0, sizeof (callbacks));
    callbacks.VMInit        = &vm_init;
    callbacks.VMStart       = &vm_start;
    callbacks.VMDeath       = &vm_death;
    callbacks.VMObjectAlloc = &vm_objectAlloc;
    callbacks.ObjectFree    = &vm_objectFree;
    jvmti->SetEventCallbacks (&callbacks, sizeof (callbacks));

    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_START, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_OBJECT_FREE, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH, (jthread) NULL);

    printf ("[ONLOAD] Agent load callback finished\n");

    return (JNI_OK);
}

JNIEXPORT void JNICALL Agent_OnUnload (JavaVM *vm) {
    printf ("[ONUNLOAD] Agent unload callback executed\n");
}
