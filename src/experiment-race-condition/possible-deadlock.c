#include <pthread.h>

pthread_mutex_t lock_one = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_two = PTHREAD_MUTEX_INITIALIZER;

void *thread_one (__attribute__ ((unused)) void *args) {
    pthread_mutex_lock (&lock_one);
    pthread_mutex_lock (&lock_two);
    pthread_mutex_unlock (&lock_two);
    pthread_mutex_unlock (&lock_one);
    return (NULL);
}

void *thread_two (__attribute__ ((unused)) void *args) {
    pthread_mutex_lock (&lock_two);
    pthread_mutex_lock (&lock_one);
    pthread_mutex_unlock (&lock_one);
    pthread_mutex_unlock (&lock_two);
    return (NULL);
}

int main (void) {
    pthread_t one;
    pthread_t two;
    pthread_create (&one, 0, thread_one, NULL);
    pthread_create (&two, 0, thread_two, NULL);
    pthread_join (one, NULL);
    pthread_join (two, NULL);
    return (0);
}
