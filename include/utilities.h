#ifndef UTILITIES
#define UTILIEITES

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local Libraries
#include "heapPriorityQueue.h"

// Global Variables
extern int process_Size;
extern int threadOverhead_Time;
extern int processOverhead_Time;
extern int size;
extern ReadyQueue rdyQ[50];

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

typedef struct {
  int arrivalTime;
  int processNumber;
  int threadNumber;
  int serviceTime;
  int ioTime;
  int turnAroundTime;
  int finishTime;
} ThreadInformation;

Process* getFileInput(const char* fileName, Process* processes);
void printFileInput(Process* processes);
int max(int num1, int num2);
int min(int num1, int num2);
void createReadyQueue(Process* p);
void fcfs();

#endif
