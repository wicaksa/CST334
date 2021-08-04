/*
 * Name: Wicaksa Munajat
 * Date: <July 26, 2021> (Due: July 27, 2021)
 * Title: CST 334 Lab 5 – Developing multi-threaded applications
 * Description: 1. To develop multi-threaded application programs
                2. To demonstrate the use of threads in matrix multiplication
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    // create an array for local storage of iteration number
    int aNum[NTHREADS];

    // declare variable
    int i;

    for (i = 0; i < NTHREADS; i++) {
        // create fork threads
        // race condition happens here
        // use array to have private iteration values for each
        aNum[i] = i;
        pthread_create(&threads[i], NULL, go, &aNum[i]);
    }

    // join threads
    for (i = 0; i < NTHREADS; i++) {
    printf("Thread %d returned\n", i);
    // waits for thread termination
        pthread_join(threads[i], NULL);
    }

    printf("Main thread done.\n");
    return 0;
}

// has a warning: cast to smaller integer type 'int' from 'pthread_t _Nonnull' error
// harmless in this case and can be ignored
void *go(void*arg) {
    printf("Hello from thread %d with iteration %d\n", (int)pthread_self(), *(int*)arg);
    return 0;
}
