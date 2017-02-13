/**
Process class
*/
//#include "data4.txt"

#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

class Process {
  public:
  string ProcessName;
  int ProcessID;
  int Array[12];
  int Sub;
  int CPUTimer;
  int IOTimer;
  int CPUTotal;
  int IOTotal;
  int CPUCount;
  int IOCount;

  Process(string, int, int*);
  void Terminate();
  void upCPUTimer();
  void upIOTimer();
  int CPUCheck();
  int IOCheck();
  void CPUTick();
  void IOTick();
};

//Constructor Process(string, int, int*)
//takes a string, int and pointer to an array of ints
//and initializes all of the processor variables
Process::Process(string inStr, int inID, int* inArray) {
  ProcessName = inStr;
  ProcessID = inID;
  for(int i=0; i<12; i++)
    Array[i] = inArray[i];

  Sub=0;
  CPUTimer=0;
  IOTimer=0;
  CPUTotal=0;
  IOTotal=0;
  CPUCount=0;
  IOCount=0;
}

/****************************************************************
void Terminate()
FUNCTION:   terminate the process and print out results
ARGUMENTS:  none
RETURNS:    nothing
****************************************************************/
void Process::Terminate() {
  cout << "\nProcess: " << ProcessName << "\nCPU timer ticks: " << CPUTimer
       << "\nIO timer ticks: " << IOTimer << "\nCPU bursts completed: " << CPUCount
       << "\nIO bursts completed: " << IOCount << "\n";
  delete this;
}

/****************************************************************
void upCPUTimer()
FUNCTION:   increase CPUTimer by 1
ARGUMENTS:  none
RETURNS:    nothing
****************************************************************/
void Process::upCPUTimer() {
  CPUTimer++;
}

/****************************************************************
void upIOTimer()
FUNCTION:   increase IOTimer by 1
ARGUMENTS:  none
RETURNS:    nothing
****************************************************************/
void Process::upIOTimer() {
  IOTimer++;
}

/****************************************************************
int CPUCheck()
FUNCTION:   on return of 0: terminate the process
                         1: switch to IO Burst
                         2: continue process
ARGUMENTS:  none
RETURNS:    an int
****************************************************************/
int Process::CPUCheck()
{
  if(Array[Sub] == 0)
  {
	Sub++;
    if(Array[Sub] == 0)
      return 0; //return 0 to terminate
    else
      return 1; //return 1 to submit to IO
  }
  else
    return 2;
}

/****************************************************************
int IOCheck()
FUNCTION:   on return of 0: terminate the process
                         1: switch to CPU Burst
                         2: continue process
ARGUMENTS:  none
RETURNS:    an int
****************************************************************/
int Process::IOCheck()
{
  if(Array[Sub] == 0)
  {
	Sub++;
    if(Array[Sub] == 0)
      return 0; //return 0 to terminate
    else
      return 1; //return 1 to submit to ready
  }
  return 2;
}

/****************************************************************
void CPUTick()
FUNCTION:   subtract 1 from # in array and increase CPUTimer
ARGUMENTS:  none
RETURNS:    nothing
****************************************************************/
void Process::CPUTick()
{
  Array[Sub]--;
  this->upCPUTimer();
}

/****************************************************************
void IOTick()
FUNCTION:   subtract 1 from # in array and increase IOTimer
ARGUMENTS:  none
RETURNS:    nothing
****************************************************************/
void Process::IOTick()
{
  Array[Sub]--;
  this->upIOTimer();
}
