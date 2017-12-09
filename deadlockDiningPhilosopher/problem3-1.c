#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define NUM_THREADS 5

pthread_mutex_t locks[NUM_THREADS];

void *napping(int t) {
    unsigned int Time = time(NULL); 
    usleep(rand_r(&Time) % (t * 1000000));
    return(NULL);
}

void *philosopher(void *args) {
    int *thread = args;
    
    printf("Philosopher %d is thinking...\n", *thread);
    napping(2);
    printf("Philosopher %d is hungry...\n", *thread);

    if (*thread % 2) {
        pthread_mutex_lock(&locks[(*thread + 1) % NUM_THREADS]); 
        printf("phila %d has %d stick\n", *thread, (*thread + 1) % NUM_THREADS);

        napping(10);

        pthread_mutex_lock(&locks[(*thread) % NUM_THREADS]);
        printf("phila %d has %d stick\n", *thread, *thread);
    } else {
        pthread_mutex_lock(&locks[(*thread) % NUM_THREADS]);
        printf("phila %d has %d stick\n", *thread, *thread);

        napping(10);

        pthread_mutex_lock(&locks[(*thread + 1) % NUM_THREADS]); 
        printf("phila %d has %d stick\n", *thread, (*thread + 1) % NUM_THREADS);    
    }

    printf("Philosopher %d is starting to eat...\n", *thread);
    napping(1);
    printf("Philosopher %d is done eating...\n", *thread);
    
    pthread_mutex_unlock(&locks[(*thread + 1) % NUM_THREADS]);
    pthread_mutex_unlock(&locks[(*thread) % NUM_THREADS]);
    
    return (NULL);
}

int main(int argc, char *argv[]) {
    pthread_t tid[NUM_THREADS];
    int numID[NUM_THREADS] = {0, 1, 2, 3, 4};
    
    int i = NUM_THREADS;
    while (i >= 0) {
        pthread_mutex_init(&locks[i], NULL);
        i--;
    }

    for(i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tid[i], NULL, philosopher, (void *) &numID[i]);
    }

    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    
return (1);
}



