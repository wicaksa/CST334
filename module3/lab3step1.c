/*
 * Name: Wicaksa Munajat
 * Date: <July 12, 2021> (Due: July 13, 2021)
 * Title: Lab3 Step 1 – Inter-process Communication – Pipes
 * Description: This program practices the use of pipes for IPC which is us
 * to communicate between two processes. You can read and write from it.
 */

// libraries
#include<stdio.h>
#include<unistd.h>   // pipe() function is defined here
#include<stdlib.h>
#include<sys/wait.h>

// main
int main() {
    // creating the pipe
    // if pipe returns 0, it is successful
    // if pipe returns -1, it is not successful
    // fd[0] - read
    // fd[1] - write
    int fds[2]; // file descriptor for the pipe
    pipe(fds);  // pipe takes an array of 2 integers

    // child 1 duplicates downstream into stdin
    if (fork() == 0) {
        dup2(fds[0], 0); // The dup2() system function is used to create a copy
                         // of an existing file descriptor
        close(fds[1]);   // close write file 
        execlp("more","more",0); // The execlp() function replaces the current
                                 // process image with a new process image specified by file.
    }
    // child 2 duplicates upstream into stdout
    else if (fork() == 0) {
        dup2(fds[1],1);
        close(fds[0]);
        execlp("ls","ls",0);
    }
    // parent closes both ends and wait for children
    else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
