//David Rasper
//Assignment 4
//Due: 10/14/15 @ 11:59 PM
//Simulating Round Robin Scheduling

#include "Process.h"
#include <fstream>
#include <queue>


int main()
{
  const int MAX_TIME=500;
  const int TIME_SLICE=5;
  const int IN_USE=5;

  ifstream ifs; //in file stream

  int pID=101;  //starting process ID
  string pName = ""; //process name
  int pArray[12]; //process array
  int Timer =0;
  int timeSlice =0;

  queue<Process*> entryQ;
  queue<Process*> readyQ;
  queue<Process*> ioQ;
  Process* ioactive = NULL;
  Process* active = NULL;
  bool flag = true; //flag for staying in the main loop

  ifs.open("data4.txt", std::ifstream::in);
  //put all processes into the entryQ
  while(true)
  {
    ifs >> pName;
    if(pName == "STOPHERE")
      break;
    for(int n=0; n<12; n++)
      ifs >> pArray[n];
    Process* point = new Process(pName, pID, pArray);
    entryQ.push(point);
    pID++;
  }
  ifs.close();
  bool cpuBurst = true;
  int check, sub;
  
  //check all are in entryQ
  /****************************************************************
  Start of main while loop
  ****************************************************************/
  while( (flag != false && Timer != MAX_TIME) )
  {
	if(Timer%25 == 0)
	  cout << "Timer is at: " << Timer;
    //if the readyQ is below 5 get another process
    //will only add to the queue if active isn't in use
    if(readyQ.size()<IN_USE)
    {
      if(active != NULL)
        flag = true;
      else //if active is NULL get a new process into ready queue
        //fill ready queue
        while( (readyQ.size()<IN_USE && entryQ.size() !=0) )
        {
          if(entryQ.size() == 0)
            break;
          readyQ.push(entryQ.front());
          entryQ.pop();
        }
    }
    /****************************************************************
    Start of Active phase of process
    
    ****************************************************************/
    //if the cpuburst is in effect
    if (cpuBurst == true)
    {
	  /****************************************************************
      Checking of active being NULL
      ****************************************************************/
      if (active == NULL)
      {
        //check if queues are empty
        if(readyQ.size() != 0) {
            active = readyQ.front();
            cout << "\nCPU process: " << active->ProcessName
                 << " Sub: " << active->Sub << " #: " << active->Array[sub];
            if (active->Array[sub] < 0)
              active->Array[sub] *= -1;
            readyQ.pop();
          //}
        }
        else
        {
          if(ioQ.size() == 0)
            flag = false; //exit if both queues empty
        }
      }
      
      /****************************************************************
      Checking of active not NULL    
      ****************************************************************/
      //if there is a process  that's active
      else if(active != NULL)
      {
		if (active->Array[sub] < -20)
		  break;
        check = active->CPUCheck();
        if(check == 0)
        { //if check 0, no more to do
          cout << "Terminating: " << active->ProcessName << endl;
          active->CPUCount++;
          active->Terminate();
          active = NULL;
          ioactive = NULL;
        }
        else if(check == 1)
        { //if check 1, switch to IO
          active->CPUCount++;
          ioQ.push(active);
          ioactive = NULL;
          cpuBurst = false;
        }
        else
        { //if check 2, continue the process
          if(timeSlice == TIME_SLICE)
          {
			cout << "time = tslice " << endl;
            readyQ.push(active);
            active = NULL;
            timeSlice = 0;
          }
          else
          {
            active->CPUTick();
            timeSlice++;
          }
        }
        timeSlice++;
      }
    }//close cpuBurst if
    
    /****************************************************************
    Start of IO phase of process     
    ****************************************************************/
    else
    {
	  /****************************************************************
      Checking if ioactive is NULL     
      ****************************************************************/
      if(ioactive == NULL)
      {
        //check if queues are empty
        if(ioQ.size() == 0)
        {
          if(readyQ.size() == 0)
            flag = false; //exit if queues empty
        }
        //get process
        else
        {
		  ioactive = ioQ.front();
          ioQ.pop();
          sub = ioactive->Sub;
          ioactive->Array[sub] *= -1;
          cout << "\nIO process: " << ioactive->ProcessName
               << " Sub: " << ioactive->Sub << " #: "
               << ioactive->Array[sub] << endl;
        }
      }
      /****************************************************************
      checking if ioactive is NULL
      ****************************************************************/
      else //if(ioactive != NULL)
      {
        check = ioactive->IOCheck();
        sub = ioactive->Sub;
        if(ioactive->Array[sub]<0)
          ioactive->Array[sub] *= -1;
        if(check == 0)
        {
		  cout << "Terminating: " << ioactive->ProcessName;
		  ioactive->IOCount++;
          ioactive->Terminate();
          ioactive = NULL;
          active = NULL;
          cpuBurst = true;
        }
        else if(check == 1)
        { //if check 1 go back to CPU
          ioactive->IOCount++;
          cpuBurst = true;
        }
        else //if check 2 continue looping
        {
          if(timeSlice == TIME_SLICE) //if the timeslice == 5
          {			
			cout << "resetting timeslice in IO";
            ioQ.push(ioactive);
            ioactive = NULL;
            timeSlice = 0;
          }
          else
          {
            ioactive->IOTick();
            timeSlice++;
          }
        }
      }
    }
    Timer++;
  }

  return 0;
}
