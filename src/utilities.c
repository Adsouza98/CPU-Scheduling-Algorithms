/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Extension: 03/23/22
 * This file comprises the utility functions for the program
*/
#include "utilities.h"

ThreadInformation* threadTable = NULL;
int table_size = 0;

Process* getFileInput(const char* fileName, Process* p)
{
  FILE* fp;
  int i, j, k;
  // int numBursts = 0;
  int numThreads = 0;

  fp = fopen(fileName, "r");
  if (fp == NULL) {
    fprintf(stderr,"\nFailed to Open File\n");
    exit(-1);
  }

  fscanf(fp, "%d %d %d", &process_Size, &threadOverhead_Time, &processOverhead_Time);

  p = (Process*)malloc(process_Size * sizeof(Process));

  for (i = 0; i<process_Size; i++) {
    fscanf(fp, "%d %d", &p[i].processNumber, &p[i].thread_Size);
    numThreads += p[i].thread_Size;
    for (j = 0; j<p[i].thread_Size; j++) {
      fscanf(fp, "%d %d %d", &p[i].threadsArray[j].threadNumber, &p[i].threadsArray[j].arrivalTime, &p[i].threadsArray[j].io_Size);
      // numBursts += p[i].threadsArray[j].io_Size;
      //p[i].threadsArray[j].ioArray = (IO*)malloc(cpuSize * sizeof(IO));
      for (k = 0; k<p[i].threadsArray[j].io_Size-1; k++) {
        fscanf(fp, "%d %d %d", &p[i].threadsArray[j].ioArray[k].threadIONumber, &p[i].threadsArray[j].ioArray[k].cpu_Time, &p[i].threadsArray[j].ioArray[k].io_Time);
        if (k == 0) {
          insert(p[i].threadsArray[j].arrivalTime, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[k].threadIONumber, p[i].threadsArray[j].ioArray[k].cpu_Time, p[i].threadsArray[j].ioArray[k].io_Time, 0);
        } else {
          insert(999, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[k].threadIONumber, p[i].threadsArray[j].ioArray[k].cpu_Time, p[i].threadsArray[j].ioArray[k].io_Time, 0);
        }
      }
      fscanf(fp, "%d %d", &p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, &p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time);
      if (k == 0) {
        insert(p[i].threadsArray[j].arrivalTime, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time, 0, 0);
      } else {
        insert(999, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time, 0, 0);
      }
    }
  }

  threadTable = (ThreadInformation*)malloc((numThreads) * sizeof(ThreadInformation));
  table_size = numThreads;
  fclose(fp);
  return p;
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

/**
 * Find maximum between two numbers.
 */
int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

/**
 * Find minimum between two numbers.
 */
int min(int num1, int num2)
{
    return (num1 > num2 ) ? num2 : num1;
}

void fcfs()
{
  int i = 0;
  int j = 0;
  int table_Index = 0;
  int check = 0;

  ReadyQueue tmp;
  int totalRunTime = 0;
  int timeinCPU = 0;
  float utilizationCPU = 0.0;
  float avgTurnaroundTime = 0;

  int prev_process = 0;
  int prev_thread = 0;
  int prev_CPU = 0;
  int prev_EnterCPU = 0;

  int tmp_EnterCPU = 0;
  int tmp_RunTime = 0;

  int overHeadCost = 0;
  //int burstRunTime = 0;

  int nextBurstinThread = -1;
  int updatedArrivalTime = -1;

  while (size != -1) {
    tmp = extractMin();

    if (prev_process == 0) {
      overHeadCost = 0;
    } else if (prev_process != tmp.processNumber) {
      overHeadCost = processOverhead_Time;
    } else if (prev_thread != tmp.threadNumber) {
      overHeadCost = threadOverhead_Time;
    }

    // Update all Previous Varaibels used to calculate following Burst Arrival Time
    tmp_EnterCPU = prev_CPU + overHeadCost + prev_EnterCPU;
    prev_process = tmp.processNumber;
    prev_thread = tmp.threadNumber;
    prev_CPU = tmp.cpu;
    prev_EnterCPU = tmp_EnterCPU;

    // Update Run Time
    tmp_RunTime = tmp_EnterCPU + tmp.cpu;

    // Update Total Time in CPU
    timeinCPU += tmp.cpu;


    //Update Thread Information Table
    for (j = 0; j<table_size; j++) {
      check = 0;
      if (threadTable[j].processNumber == tmp.processNumber && threadTable[j].threadNumber == tmp.threadNumber) {
        threadTable[j].finishTime = tmp_RunTime;
        threadTable[j].turnAroundTime = threadTable[j].finishTime - threadTable[j].arrivalTime;
        threadTable[j].serviceTime += tmp.cpu;
        threadTable[j].ioTime += tmp.io;

        check = 1;
        break;
      }
    }
    if (check == 0 && table_Index < table_size) {
      threadTable[table_Index].arrivalTime = tmp.arrivalTime;
      threadTable[table_Index].processNumber = tmp.processNumber;
      threadTable[table_Index].threadNumber = tmp.threadNumber;
      threadTable[table_Index].serviceTime += tmp.cpu;
      threadTable[table_Index].ioTime += tmp.io;
      threadTable[table_Index].finishTime = tmp_RunTime;
      threadTable[table_Index].turnAroundTime = threadTable[table_Index].finishTime - threadTable[table_Index].arrivalTime;

      table_Index++;
    }


    // Update Arrival Time of following Burst in current thread
    nextBurstinThread = findinHeap(tmp.processNumber, tmp.threadNumber, tmp.burstNumber);
    if (nextBurstinThread != -1) {
      updatedArrivalTime = tmp_EnterCPU + tmp.cpu + tmp.io;
      changePriority(nextBurstinThread, updatedArrivalTime);
    }
    // i = 0;
    // printf("\n\nUpdated Heap\n");
    // while (i <= size) {
    //   printf("A_Time = %d \t P_# = %d \t T_# = %d \t B_# = %d \t CPU_T = %d \t IO_T = %d \t EnterCPU_T = %d\n", rdyQ[i].arrivalTime, rdyQ[i].processNumber, rdyQ[i].threadNumber, rdyQ[i].burstNumber, rdyQ[i].cpu, rdyQ[i].io, rdyQ[i].enterCPUTime);
    //   i++;
    // }
  }

  totalRunTime = tmp_EnterCPU + tmp.cpu + tmp.io;
  utilizationCPU = ((float)timeinCPU / (float)totalRunTime) * 100;

  // Calculate Average Turnaround Time (P1_finsih - P1_Arrive)... + (Pn_finish - Pn_Arrive) / # of Processes
  int p = 0;
  int* arrivalTime = (int*)malloc((process_Size + 1) * sizeof(int));
  int* finishTime = (int*)malloc((process_Size + 1) * sizeof(int));
  for (p = 0; p < process_Size + 1; p++) {
    arrivalTime[p] = 999;
    finishTime[p] = 0;
  }
  for (i = 0; i < table_size; i++) {
    for (p = 1; p < process_Size + 1; p++) {
      if (threadTable[i].processNumber == p) {
        arrivalTime[p] = min(threadTable[i].arrivalTime, arrivalTime[p]);
        finishTime[p] = max(threadTable[i].finishTime, finishTime[p]);
      }
    }
  }
  for (p = 1; p < process_Size + 1; p++) {
    avgTurnaroundTime += finishTime[p] - arrivalTime[p];
  }
  avgTurnaroundTime = avgTurnaroundTime / process_Size;
  free(arrivalTime);
  free(finishTime);

  printf("Total Time Required = %d units\n", totalRunTime);
  printf("Average Turnaround Time is %.1lf\n", avgTurnaroundTime);
  printf("Total Time in CPU = %d units\n", timeinCPU);
  printf("CPU Utilization is %.1lf\n", utilizationCPU);

  for (i = 0; i < table_size; i++) {
    printf("Thread %d of Process %d:\n", threadTable[i].threadNumber, threadTable[i].processNumber);
    printf("Arrival Time: %d\n", threadTable[i].arrivalTime);
    printf("Service Time: %d units, I/O Time: %d units, Turnaround Time: %d units, Finish Time: %d units\n", threadTable[i].serviceTime, threadTable[i].ioTime, threadTable[i].turnAroundTime, threadTable[i].finishTime);
  }

}
