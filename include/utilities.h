#ifndef UTILITIES
#define UTILIEITES

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

//Global Variables
extern int process_Size;
extern int threadOverhead_Time;
extern int processOverhead_Time;
extern int thread_Size;
extern int cpuSize;

typedef struct {
  int threadIONumber;
  int cpu_Time;
  int io_Time;
} IO;

typedef struct {
  int threadNumber;
  int arrivalTime;
  int io_Size;
  IO ioArray[100];
} Threads;

typedef struct {
  int processNumber;
  int thread_Size;
  Threads threadsArray[50];
} Process;

Process* getFileInput(char* fileName, Process* processes);
void printFileInput(Process* processes);

#endif
