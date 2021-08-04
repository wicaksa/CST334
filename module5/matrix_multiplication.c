/*
 * Name: Wicaksa Munajat
 * Date: <July 26, 2021> (Due: July 27, 2021)
 * Title: CST 334 Lab 5 – Developing multi-threaded applications
 * Description: Write a program that uses threads to perform a parallel matrix multiply.
     * To multiply two matrices C = A*B,
     * the result entry C(i,j) is computed by taking the dot product of the ith row
     * of A and the jth column of B: Ci,j = SUM A(i,k)*B(k,j) for k = 0 to N-1,
     * where N is the matrix size.

     * We can divide the work by creating one thread to compute each value (or each row) in C, and
     * then executing those threads on different processors in parallel on multi-processor
     * systems. As shown in the following figure, each is cell in the resulting matrix
     * is the sum of the multiplication of row elements of the first matrix by the column
     * elements of the second matrix.
 */


/* From justin
It will be helpful to break the lab down into steps.

1. Create 2 matrix arrays of integers.
2. Fill those two matrix arrays with random values using the code provided in the lab document.
3. Use a loop to create the necessary amount of threads that use a calculation function that you will write.
   (This will look a bit similar to the code you used in solving the first section of this lab)
4. The calculation function will fill a third matrix with the product of the first and second matrix.
5. Join the threads
6. Print the values of the third matrix
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// define max values for N, M, L
#define MAX 1024
#define N 1024
#define M 1024
#define L 1024

// create matrices A B C
double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

// declare variables
int i, j;

// create threads
pthread_t threads[MAX];

// call the calc()
void *calc(void* arg);

// create a main
int main() {
    // use rng provided to fill in entries of A
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
           // double num = rand();
           matrixA[i][j] = rand();
       }
    }

    // use rng provided to fill in entries of B
    srand(time(NULL));
    for (i = 0; i < M; i++) {
        for (j = 0; j < L; j++) {
           // double num = rand();
           matrixB[i][j] = rand();
       }
    }

    // create threads
    for (i = 0; i < MAX; i++) {
        int *p = malloc(sizeof(int)); // allocate heap
        *p = i; // holds the row number 
        pthread_create(&threads[i], NULL, calc, p);
    }

    // join threads
    for (int i = 0; i < MAX; i++) {
        pthread_join(threads[i], NULL);
    }

    // print values of third matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("value = %f row = %d col = %d", matrixC[i][j], i, j);
        printf("\n");
        }
    }
    return 0;
}

// create function to be executed by the threads
void *calc(void* arg) {
    int i = *(int *) arg;
    for (int j = 0; j < L; j++) {
        double temp = 0;
        for (int k = 0; k < M; k++) {
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    }
    return 0;
}
