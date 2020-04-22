#include <pthread.h>

int shared = 0;

void *thread (__attribute__ ((unused)) void *args) {
    shared ++;
    return (NULL);
}

int main (void) {
    pthread_t one;
    pthread_t two;
    pthread_create (&one, 0, thread, NULL);
    pthread_create (&two, 0, thread, NULL);
    pthread_join (one, NULL);
    pthread_join (two, NULL);
    return (0);
}
