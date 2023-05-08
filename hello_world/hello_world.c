#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_THREAD_COUNT 1024
#define DEFAULT_THREAD_COUNT 2

typedef struct
{
    pthread_mutex_t *mtx;
    int counter;
} thread_data_t;

void *thread(void *data)
{
    thread_data_t *t_data = (thread_data_t *)data;

    pthread_mutex_lock(t_data->mtx);
    t_data->counter++;
    printf("Thread #%lu, counter: %d\n", (uint64_t)pthread_self(), t_data->counter);
    pthread_mutex_unlock(t_data->mtx);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    thread_data_t data = {&mtx, 0};
    pthread_t threads[MAX_THREAD_COUNT];
    int num_threads, error, i;

    if (argc < 2) {
        num_threads = DEFAULT_THREAD_COUNT;
    } else {
        num_threads = atoi(argv[1]);
    }

    if (num_threads < 1 || MAX_THREAD_COUNT < num_threads) {
        printf("NUM_THREADS must be a positive integer between 1 and %d, has: %d (%s)\n",MAX_THREAD_COUNT, num_threads, argv[1]);
        return -1;
    }

    for (i = 0; i < num_threads; i++)
    {
        printf("Creating thread %d\n", i);
        error = pthread_create(&threads[i], NULL, thread, &data);
        if (error)
        {
            printf("failed to create thread: %d\n", error);
            return -1;
        }
    }

    for (i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", data.counter);

    return 0;
}
