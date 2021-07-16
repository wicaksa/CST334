/*
 * Name: Wicaksa Munajat
 * Date: <July 12, 2021> (Due: July 13, 2021)
 * Title: Lab3 Step 3 – Inter-process Communication – Pipes
 * Description: This program practices the use of pipes for IPC.
 * Step 3. Write a C program that implements the shell command: cat/etc/passwd | grep root
 */

// libraries
#include<stdio.h>
#include<unistd.h>   // pipe() function is defined here
#include<stdlib.h>
#include<sys/wait.h>

// cat/etc/passwd
/*
 * /etc/passwd Format
 * The /etc/passwd file keeps track of all users on the system.
 *
 * The /etc/passwd file is a text file with one entry per line, representing a user account.
 * To view the contents of the file, use a text editor or a command such as cat : cat /etc/passwd
 *
 */

 // grep root
 /*
  * grep searches the named input FILEs (or standard input if no files are named,
  * or if a single hyphen-minus (-) is given as file name) for lines containing
  * a match to the given PATTERN.  By  default,  grep  prints the matching lines.
  *
  */
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
      // execlp("cat","cat","/etc/passwd", 0);
      execlp("grep","grep","root", 0); // The execlp() function replaces the current
                               // process image with a new process image specified by file.
     }
     // child 2 duplicates upstream into stdout
    else if (fork() == 0) {
      dup2(fds[1],1);
      close(fds[0]);
      // execlp("grep","grep","root", 0);
      execlp("cat","cat","/etc/passwd", 0);
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
