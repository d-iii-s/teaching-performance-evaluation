// An example JVMTI agent that reports compilation events.
// - Compiled method load reported.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jni.h"
#include "jvmti.h"


// --------------------------------------------------------------
// Compilation Callbacks

static void compiled_method_load (
    jvmtiEnv *jvmti,
    jmethodID method,
    jint code_size,
    const void *code_addr,
    jint map_length,
    const jvmtiAddrLocationMap *map,
    const void *compile_info) {

    jthread thread;

    jvmti->GetCurrentThread (&thread);

    jvmtiThreadInfo thread_info;

    jvmti->GetThreadInfo (thread, &thread_info);
    printf ("[LOAD] Calling thread %p %s\n", thread, thread_info.name);

    jvmti->Deallocate ((unsigned char *) thread_info.name);

    jclass klass;

    jvmti->GetMethodDeclaringClass (method, &klass);

    char *class_signature_ptr;
    char *class_generic_ptr;

    jvmti->GetClassSignature (klass, &class_signature_ptr, &class_generic_ptr);

    char *method_name_ptr;
    char *method_signature_ptr;
    char *method_generic_ptr;

    jvmti->GetMethodName (method, &method_name_ptr, &method_signature_ptr, &method_generic_ptr);
    printf ("[LOAD] Compiled method %s::%s %s loaded at addresses %p:%d\n", class_signature_ptr, method_name_ptr, method_signature_ptr, code_addr, code_size);

    jvmti->Deallocate ((unsigned char *) class_signature_ptr);
    jvmti->Deallocate ((unsigned char *) class_generic_ptr);
    jvmti->Deallocate ((unsigned char *) method_name_ptr);
    jvmti->Deallocate ((unsigned char *) method_signature_ptr);
    jvmti->Deallocate ((unsigned char *) method_generic_ptr);
}


// --------------------------------------------------------------
// Virtual Machine Lifecycle Callbacks

static void JNICALL vm_start (jvmtiEnv *jvmti, JNIEnv *env) {
    printf ("[VMSTART] Virtual machine start callback executed\n");
}

static void JNICALL vm_init (jvmtiEnv *jvmti, JNIEnv *env, jthread thread) {
    printf ("[VMINIT] Virtual machine initialization callback executed\n");
}

static void JNICALL vm_death (jvmtiEnv *jvmti, JNIEnv *env) {
    printf("[VMDEATH] Virtual machine death callback started\n");

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
    jint rc = vm->GetEnv ((void**)(&jvmti), JVMTI_VERSION_1_0);
    if (rc != JNI_OK) {
        printf ("[ONLOAD] Failed to GetEnv\n");
        return (-1);
    }

    jvmtiCapabilities capabilities;
    memset (&capabilities, 0, sizeof (capabilities));
    capabilities.can_generate_compiled_method_load_events = 1;

    jvmtiError err = jvmti->AddCapabilities (&capabilities);
    if (err != JVMTI_ERROR_NONE) {
        printf ("[ONLOAD] Failed to AddCapabilities\n");
        return (-1);
    }

    // Set callbacks and enable event notifications
    jvmtiEventCallbacks callbacks;
    memset (&callbacks, 0, sizeof (callbacks));
    callbacks.CompiledMethodLoad = &compiled_method_load;
    callbacks.VMInit = &vm_init;
    callbacks.VMStart = &vm_start;
    callbacks.VMDeath = &vm_death;
    jvmti->SetEventCallbacks (&callbacks, sizeof (callbacks));

    // Event notification can be per thread or global if no thread provided.
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_START, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH, (jthread) NULL);
    jvmti->SetEventNotificationMode (JVMTI_ENABLE, JVMTI_EVENT_COMPILED_METHOD_LOAD, (jthread) NULL);

    printf ("[ONLOAD] Agent load callback finished\n");

    return (JNI_OK);
}

JNIEXPORT void JNICALL Agent_OnUnload (JavaVM *vm) {
    printf ("[ONUNLOAD] Agent unload callback executed\n");
}
