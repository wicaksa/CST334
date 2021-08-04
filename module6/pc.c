// # Name: <Wicaksa Munajat>
// # Date: <08/03/2021> (Due: 08/03/2021)
// # Title: Lab6 – Producer – Consumer as a classical problem of synchronization
// # Description: Write a program* that solves the producer - consumer problem.
// # program to write: produce -consumer problem to produce and consume the alphabet.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Max size of buffer
#define N 1

// Initialize semaphores
sem_t mutex;
sem_t full;
sem_t empty;

// Create buffer of size N (1)
char buffer[N];

// Keep track of index of buffer
int in = 0; // add
int out = 0; // remove

// Keeps track of letters in producer
int p = 0;

// Keeps track of letters in consumer
int c = 0;

// Create alphabet list
char letters[26] = {'a','b','c','d','e','f','g',
                    'h','i','j','k','l','m','n',
                    'o','p','q','r','s','t','u',
                    'v','w','x','y','z'};

// Consumer letter
char item;

// add letter to buffer
void add(char c) {
    buffer[in] = c;
    in = (in + 1) % N; // so it doesn't go out of range
    printf("\nProducer produces item %c", c);
}

// remove the letter from buffer
char del(){
    char c = buffer[out];
    out = (out + 1) % N;
    // consume the item
    printf("\nConsumer consumes item %c", c);
    return c;
}

// producer thread that adds letter of alphabet into the buffer
void *producer(void *arg) {
    char *input = (char *) arg;
    char item;
    // int count = 1;

    do {
        // produce next item
        // wait before writing into buffer
        sem_wait(&empty);
        sem_wait(&mutex);

        // add the item to buffer
        add(letters[p++]);

        sem_post(&mutex);
        sem_post(&full);

    } while (p <= 26);
}

// consumer thread
void *consumer() {
    do {
        sem_wait(&full);
        sem_wait(&mutex);

        // remove next item from buffer
        item = del();

        sem_post(&mutex);
        sem_post(&empty);

        c++;
    } while (c < 26); // stop at z
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Initialize pthreads
    pthread_t producert;
    pthread_t consumert;

    // Create Threads
    pthread_create(&producert, NULL, producer, &letters);
    pthread_create(&consumert, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producert, NULL);
    pthread_join(consumert, NULL);

    // Destroy semaphores to prevent memory leak
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
