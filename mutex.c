#include <pthread.h>
#include <stdio.h>

long counter = 0;
pthread_mutex_t mutex_lock;

void *increment(void *arg) {
    for (long i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex_lock);
        counter++;
        pthread_mutex_unlock(&mutex_lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex_lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex_lock);

    printf("Final expected counter value: %d\n", 2 * 1000000);
    printf("Final actual counter value: %ld\n", counter);

    return 0;
}
