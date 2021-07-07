#include <stdio.h>      /* printf, stderr */ 
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/*
 * Name: <Wicaksa Munajat>
 * Date: <Monday July 5, 2021> (Due: Tuesday July 6, 2021) 
 * Title: Lab 2 – Programming in C and Use of System Calls
 * Description: Lab 2 Step 5: This program illustrates how 
 * the parent can wait until the child finishes running it's program .
 */

/* Step 5. Rewrite the program in Step 1., so that the child process 
 * runs the ls command, and that the parent parent process waits 
 * until the child process terminates before it exits. Demonstrate 
 * your code. You may use the following code snippet.
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
    
    // Child process
    // Will go first since parent has wait()
    // WIll list the files in the current directory
    if (pid == 0) {
        execlp("/bin/ls","ls",NULL);  
        }

    // Parent process  
    // Will wait until child executes line 37 
    // Then parent will print out statement
    else {
        wait(NULL);
        printf("Child Complete");
	exit(0);	
    }
    return 0;
}

// End of Step 5 
