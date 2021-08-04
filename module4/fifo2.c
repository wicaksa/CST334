/*
 * Name: Wicaksa Munajat
 * Date: <July 19, 2021> (Due: July 20, 2021)
 * Title: CST 334 Lab 4 – FIFO Page Replacement Simulation File
 * Description: This program simulates how a FIFO algorithm is implemented
 * for a memory management program that uses paging.
 */

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

typedef struct {//to
    int pageno;
} ref_page;


int main(int argc, char *argv[]) {
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[C_SIZE]; // Cache that stores pages from incoming txt file
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int totalRead = 0;

    for (i = 0; i < C_SIZE; i++){ //initialise cache array
         cache[i].pageno = -1;
    }

    // initialize a queue to hold incoming pages
    // size of queue has to be equal to C_SIZE
    struct queue *q = queue_create(C_SIZE);
    struct queue *result_q = queue_create();

    // read txt file
    while (fgets(pageCache, 100, stdin)) {
    	int page_num = atoi(pageCache); //Stores number read from file as int

        // case1: queue is not full
        if (queue_length(q) < C_SIZE) {
            // page_num not in queue :
            if (queue_find(q, page_num) == NULL) {
                // miss
                // enqueue page_num
                enqueue(q, page_num);
                // increment totalFaults
                totalFaults = totalFaults + 1;
                // increment totalRead
                totalRead = totalRead + 1;
                // check if page_num already exists in the result_q
                if (queue_find(result_q, page_num) == NULL) {
                    // if not, add it to the result_q
                    enqueue(result_q, page_num);
                }
            }
            else {
            // page_num in queue
                // hit
                // increment totalRead
                totalRead = totalRead + 1;
            }

        }
        // case2: queue is full
        // if (queue_length(q) >= C_SIZE)
        else {
            // page_num not in queue:
            if (queue_find(q, page_num) == NULL) {
                // miss
                // dequeue first item
                dequeue(q);
                // enqueue page_num
                enqueue(q, page_num);
                // increment totalFaults
                totalFaults = totalFaults + 1;
                // incrememnt totalRead
                totalRead = totalRead + 1;
                // check if page_num already exists in the result_q
                if (queue_find(result_q, page_num) == NULL) {
                    // if not, add it to the result_q
                    enqueue(result_q, page_num);
                }
            }
            else {
                // page_num in queue:
                    // hit
                    // increment totalRead
                totalRead = totalRead + 1;
            }
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    printf("%d Total Page Read\n", totalRead);
    printf("Content of the queue as follows.\n");
    queue_traverse(result_q);
    return 0;

}
