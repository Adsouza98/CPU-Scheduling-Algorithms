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

extern int size;
extern ReadyQueue rdyQ[50];
extern ThreadInformation* threadTable;

// Global Variables
const char test_FileName_FCFS[100] = "Test/FCFS/FCFS.txt";
const char test_FileName_RR[100] = "Test/RR/RR.txt";

int process_Size = 0;
int threadOverhead_Time = 0;
int processOverhead_Time = 0;

int main(int argc, char const *argv[]) {

  Process* processes = NULL;

  processes = getFileInput(test_FileName_FCFS, processes);
  //printFileInput(processes);

  // int i = 0;
  // printf("Original Heap\n");
  // while (i <= size) {
  //   printf("A_Time = %d \t P_# = %d \t T_# = %d \t B_# = %d \t CPU_T = %d \t IO_T = %d \t EnterCPU_T = %d\n", rdyQ[i].arrivalTime, rdyQ[i].processNumber, rdyQ[i].threadNumber, rdyQ[i].burstNumber, rdyQ[i].cpu, rdyQ[i].io, rdyQ[i].enterCPUTime);
  //   i++;
  // }

  fcfs();

  free(processes);
  free(threadTable);

  return 0;
}
