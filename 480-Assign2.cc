/**************************************
Program 2
David Rasper
Z1642905
Due: 9/14/15 @ 11:59PM

The function of this program is to use
 Linux functions to show PID's after
 using the fork function to create
 child and grandchild processes.
**************************************/

#include <iostream>
#include <sys/wait.h> //needed for wait function
#include <cstdio>
#include <stdlib.h>
#include <unistd.h> //UNIX/POSIX constants and functions (fork)
#include <string.h> //needed for strlen

using namespace std;

/**************************************
Main:
Function: The function of main is to
 fork into a new process two times
 and get the PID/PPID of all processes
 and lastly execute the ps command.
**************************************/
int main() {
  cout << "--------Assignment 2-------" << endl;
  pid_t fSuc; //variable for fork success
  cerr << "We are currently in the parent process.\n";
  pid_t pid = getpid(); //variable for pid
  pid_t ppid = getppid(); //variable for parent pid
  cerr << "Parent PID = '" << pid << "' and its PPID = '"
       << ppid << "'.";
  cout << "\nAbout to fork into the child process.\n";
  fSuc = fork(); //attempt to fork to child
  if (fSuc<0) { //check if failed, print error and exit if true
    cout << "Fork failed! Exiting";
    exit(-1);
  }
  else //if fork works, get pid & ppid of child process and then fork again
    if (fSuc==0) {
      cerr << "  Fork successful.\n";
      pid = getpid();
      ppid = getppid();
      cerr << "We are in the child process! Child PID = '"
           << pid << "' and its PPID = '" << ppid
           << "'.\nAttempting to fork to grandchild\n";
      fSuc = fork(); //attempt to fork to grandchild
      if (fSuc < 0) { //check if failed, print error and exit if true
        cerr << "Fork Failed! Exiting.\n";
        exit(-1);
      }
      else //if fork works, get pid & ppid of grandchild process
        if (fSuc==0) {
          cerr << "  Fork successful.\n";
          pid = getpid();
          ppid = getppid();
          cerr << "We are in the grandchild process! Its PID = '"
               << pid << "' and PPID = " << ppid
               << ".\n";
          cerr << "About to exit grandchild process.\n";
          exit(0); //exit grandchild process
        }
      wait(0); //wait for grandchild process to terminate
      cerr << "We are back in the child process and about to exit.\n";
      exit(0); //exit child process
    }
  wait(0); //wait for child process to terminate
  pid = getpid();
  ppid = getppid();
  cerr << "We are back in the parent process. Its PID = '" << pid
       << "' and PPID = '" << ppid << "'.\n";
  cerr << "Calling the system function 'ps'." << endl;
  system("ps");
  cerr << "We are about to terminate the program.\n";
  exit(0);
  return 0;
}
