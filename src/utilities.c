/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Extension: 03/23/22
 * This file comprises the utility functions for the program
*/

#include "utilities.h"

Process* getFileInput(char* fileName, Process* processes)
{
  FILE* fp;
  int i, j, k;

  fp = fopen(fileName, "r");
  if (fp == NULL) {
    fprintf(stderr,"\nFailed to Open File\n");
    exit(-1);
  }

  fscanf(fp, "%d %d %d", &process_Size, &threadOverhead_Time, &processOverhead_Time);

  processes = (Process*)malloc(process_Size * sizeof(Process));

  for (i = 0; i<process_Size; i++) {
    fscanf(fp, "%d %d", &processes[i].processNumber, &processes[i].thread_Size);
    for (j = 0; j<processes[i].thread_Size; j++) {
      fscanf(fp, "%d %d %d", &processes[i].threadsArray[j].threadNumber, &processes[i].threadsArray[j].arrivalTime, &processes[i].threadsArray[j].io_Size);
      //processes[i].threadsArray[j].ioArray = (IO*)malloc(cpuSize * sizeof(IO));
      for (k = 0; k<processes[i].threadsArray[j].io_Size-1; k++) {
        fscanf(fp, "%d %d %d", &processes[i].threadsArray[j].ioArray[k].threadIONumber, &processes[i].threadsArray[j].ioArray[k].cpu_Time, &processes[i].threadsArray[j].ioArray[k].io_Time);
      }
      fscanf(fp, "%d %d", &processes[i].threadsArray[j].ioArray[processes[i].threadsArray[j].io_Size].threadIONumber, &processes[i].threadsArray[j].ioArray[processes[i].threadsArray[j].io_Size].cpu_Time);
    }
  }

  fclose(fp);
  return processes;
}

void printFileInput(Process* processes)
{
  int i, j, k;

  printf("%d %d %d\n", process_Size, threadOverhead_Time, processOverhead_Time);
  for (i = 0; i<process_Size; i++) {
    printf("%d %d\n", processes[i].processNumber, processes[i].thread_Size);
    for (j = 0; j<processes[i].thread_Size; j++) {
      printf("%d %d %d\n", processes[i].threadsArray[j].threadNumber, processes[i].threadsArray[j].arrivalTime, processes[i].threadsArray[j].io_Size);
      for (k = 0; k<processes[i].threadsArray[j].io_Size-1; k++) {
        printf("%d %d %d\n", processes[i].threadsArray[j].ioArray[k].threadIONumber, processes[i].threadsArray[j].ioArray[k].cpu_Time, processes[i].threadsArray[j].ioArray[k].io_Time);
      }
      printf("%d %d\n", processes[i].threadsArray[j].ioArray[processes[i].threadsArray[j].io_Size].threadIONumber, processes[i].threadsArray[j].ioArray[processes[i].threadsArray[j].io_Size].cpu_Time);
    }
  }

}
