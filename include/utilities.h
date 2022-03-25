#ifndef UTILITIES
#define UTILIEITES

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Local Libraries
#include "heapPriorityQueue.h"

// Global Variables
extern int process_Size;
extern int threadOverhead_Time;
extern int processOverhead_Time;
extern int size;
extern ReadyQueue* rdyQ;

typedef struct {
  int arrivalTime;
  int processNumber;
  int threadNumber;
  int serviceTime;
  int ioTime;
  int turnAroundTime;
  int finishTime;
  bool dnf;
} ThreadInformation;

int modeCheck(int argc, const char* argv[]);
void getFileInput();
int max(int num1, int num2);
int min(int num1, int num2);
void fcfs();
void rr(int q);

#endif
