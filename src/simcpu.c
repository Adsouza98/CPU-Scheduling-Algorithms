/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Extension: 03/23/22
 *
 * This File comprises of the main.c infinite loop of the program
*/

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

// Local Libraries
#include "heapPriorityQueue.h"
#include "utilities.h"

// Global Variables
char test_FileName_FCFS[100] = "Test/FCFS/FCFS.txt";
char test_FileName_RR[100] = "Test/RR/RR.txt";

int process_Size = 0;
int threadOverhead_Time = 0;
int processOverhead_Time = 0;
int thread_Size = 0;
int cpuSize = 0;

int main(int argc, char const *argv[]) {

  Process* processes = NULL;

  processes = getFileInput(test_FileName_FCFS, processes);
  printFileInput(processes);
  free(processes);
  return 0;
}
