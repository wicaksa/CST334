#include <stdio.h>      /* printf, stderr */ 
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/*
 * Name: <Wicaksa Munajat>
 * Date: <Monday July 5, 2021> (Due: Tuesday July 6, 2021) 
 * Title: Lab 2 – Programming in C and Use of System Calls
 * Description: Lab 2 Step 1 -  This program is for practicing 
 * the use of fork() in creating parent and child process>.
 */

/* Step 1 Please write the following C program in a Linux 
 * environment using vi, emacs, or an editor of your choice.
 * 
 * Step 2.Compile the program using gcc compiler by typing gcc 
 * YourProgram.c – o ExecutableName. When it compiles without 
 * errors or warnings, make a copy of the source file then go to step 3.
 *
 * Step 3: Run the program by typing ./ExecutableName and take 
 * a note of your observation.
 *
 * Step 4: Re-run the program by typing ./ExecutableName 3000. 
 * Note that the delay in the loop depends on the command line 
 * argument you give, here the delay is 3000 microseconds.
 * a. Enter delays of 500 and 5000, what happens? 
 */

// Main function with command-line arguments to pass
int main(int argc, char *argv[]) {
    pid_t pid; 
    int i, n = atoi(argv[1]); // n microseconds o input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    
    // Check for Error 
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    
    // Parent Process 
    if (pid) {
        for (i = 0; i < 100; i++) {
        printf("\t\t\t Parent Process %d \n", i); 
	// suspend execution for microsecond intervals
	usleep(n);
        }
    }

    // Child Process  
    else {
        for (i = 0; i < 100; i++) {
	    printf("Child Process %d\n", i);
	    usleep(n);
	    }
    }
    return 0;
}

// End of Step 1
