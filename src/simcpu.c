/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Grace Period: 03/19/22
 * Extension: 03/26/22
 * This File comprises of the main.c infinite loop of the program
*/

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

// Local Libraries
#include "heapPriorityQueue.h"
#include "utilities.h"

extern int size;
extern ReadyQueue* rdyQ;
extern ThreadInformation* threadTable;
extern bool detailed_Mode;
extern bool verbose_Mode;
extern bool rr_Mode;

// Global Variables
const char test_FileName_FCFS[100] = "Test/FCFS/FCFS.txt";
const char test_FileName_RR[100] = "Test/RR/RR.txt";

int process_Size = 0;
int threadOverhead_Time = 0;
int processOverhead_Time = 0;

int main(int argc, char const *argv[]) {

  int q = -1;

  q = modeCheck(argc, argv);
  getFileInput();

  if (rr_Mode == true) {
    if (q != -1) {
      rr(q);
    } else {
      printf("Invalid or Missing Quantum Number Exiting Program\n");
      return(-1);
    }
  } else {
    fcfs();
  }

  // free(processes);
  free(threadTable);
  free(rdyQ);

  return 0;
}
