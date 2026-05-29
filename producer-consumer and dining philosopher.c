#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 3
#define N 4

/* =======================
   PRODUCER-CONSUMER
   ======================= */

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        printf("Produced: %d at buffer[%d]\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        usleep(200000);

        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

void run_producer_consumer() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}


/* =======================
   DINING PHILOSOPHERS
   ======================= */

sem_t chopstick[N];
sem_t room;

void *philosopher(void *num) {
    int id = *(int *)num;

    printf("Philosopher %d is thinking.\n", id);
    sleep(1);

    sem_wait(&room);

    printf("Philosopher %d picked up left fork %d.\n", id, id);
    sem_wait(&chopstick[id]);

    printf("Philosopher %d picked up right fork %d.\n", id, (id + 1) % N);
    sem_wait(&chopstick[(id + 1) % N]);

    printf("Philosopher %d is eating.\n", id);
    sleep(1);

    printf("Philosopher %d put down forks %d and %d.\n", id, id, (id + 1) % N);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % N]);

    sem_post(&room);

    return NULL;
}

void run_dining_philosophers() {
    pthread_t ph[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
        usleep(150000);
    }

    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

    sem_destroy(&room);
}


/* =======================
   MAIN MENU
   ======================= */

int main() {
    int choice;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Producer-Consumer Problem\n");
        printf("2. Dining Philosophers Problem\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Producer-Consumer Output ---\n");
                run_producer_consumer();
                break;

            case 2:
                printf("\n--- Dining Philosophers Output ---\n");
                run_dining_philosophers();
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
