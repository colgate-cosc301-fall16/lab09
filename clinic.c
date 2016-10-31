#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define USEC_PER_SEC (1000 * 1000)
#define SLEEP_MAX (5 * USEC_PER_SEC)

typedef pthread_mutex_t mutex_t;
#define mutex_init(l) pthread_mutex_init(l, NULL)
#define mutex_lock(l) pthread_mutex_lock(l)
#define mutex_unlock(l) pthread_mutex_unlock(l)
typedef pthread_cond_t cond_t;
#define cond_init(c) pthread_cond_init(c, NULL)
#define cond_wait(c,l) pthread_cond_wait(c, l)
#define cond_signal(c) pthread_cond_signal(c)
#define cond_broadcast(c) pthread_cond_broadcast(c)

void *doctor(void *arg) {
    int id = *((int *)arg);
    printf("Doctor %d hired\n", id);

    while(1) {
        // Enter the clinic
        printf("Doctor %d: entered\n", id);

        // Treat the patients after all are registered
        printf("Doctor %d: treated patients\n", id);

        // Exit the clinic
        printf("Doctor %d: exited\n", id);

        // Sleep for a random time
        usleep(random() % SLEEP_MAX);
    }
    return NULL;
}

void *patient(void *arg) {
    int id = *((int *)arg);
    printf("Patient %d born\n", id);

    while(1) {
        // Sleep for a random time
        usleep(random() % SLEEP_MAX);

        // (Get infected) enter the clinic
        printf("Patient %d: entered\n", id);

        // Register
        printf("Patient %d: registered\n", id);

        // Receive treatment
        printf("Patient %d: treated\n", id);

        // Exit the clinic
        printf("Patient %d: exited\n", id);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    // Check and read arguments
    if (argc != 3) {
        printf("Usage: clinic <num-doctors> <num-population>\n");
        return 1;
    }
    int numDoctors = atoi(argv[1]);
    int numPopulation = atoi(argv[2]);

    //srandom(1); // Seed random number generator

    // Create threads
    pthread_t doctors[numDoctors];
    pthread_t patients[numPopulation];
    for (int i = 0; i < numDoctors; i++) {
        int *j = malloc(sizeof(int));
        *j = i;
        pthread_create(&doctors[i], NULL, &doctor, j);
    }
    for (int i = 0; i < numPopulation; i++) {
        int *j = malloc(sizeof(int));
        *j = i;
        pthread_create(&patients[i], NULL, &patient, j);
    }

    // Finish main thread, but do not end program
    pthread_exit(NULL);
}
