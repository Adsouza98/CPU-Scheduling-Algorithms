/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Grace Period: 03/19/22
 * Extension: 03/26/22
 * This file comprises the utility functions for the program
*/
#include "utilities.h"

ThreadInformation* threadTable = NULL;
int table_size = 0;
bool detailed_Mode = false;
bool verbose_Mode = false;
bool rr_Mode = false;

int modeCheck(int argc, const char* argv[])
{
  int i = 0;
  int q = -1;

  for (i=0; i<argc; i++) {
    // printf("argv[%d] = %s\n", i, argv[i]);
    if (strcmp(argv[i], "-dvr") == 0) {
      // printf("Detailed, Verbose, RR Modes Enabled\n");
      detailed_Mode = true;
      verbose_Mode = true;
      rr_Mode = true;
    } else if (strcmp(argv[i], "-dv") == 0) {
      // printf("Detailed, Verbose Modes Enabled\n");
      detailed_Mode = true;
      verbose_Mode = true;
    } else if (strcmp(argv[i], "-dr") == 0) {
      // printf("Detailed, RR Modes Enabled\n");
      detailed_Mode = true;
      rr_Mode = true;
    } else if (strcmp(argv[i], "-vr") == 0) {
      // printf("Verbose, RR Modes Enabled\n");
      verbose_Mode = true;
      rr_Mode = true;
    } else if (strcmp(argv[i], "-d") == 0) {
      // printf("Detailed Mode Enabled\n");
      detailed_Mode = true;
    } else if (strcmp(argv[i], "-v") == 0) {
      // printf("Verbose Mode Enabled\n");
      verbose_Mode = true;
    } else if (strcmp(argv[i], "-r") == 0) {
      // printf("Round Robin Scheduling Mode\n");
      rr_Mode = true;
    } else if (rr_Mode == true) {
      q = atoi(argv[i]);
      // printf("Quantum Value = %d\n", q);
    }
  }

  return q;
}

Process* getFileInput(Process* p)
{
  //FILE* fp;
  int i, j, k;
  int numThreads = 0;

  // fp = fopen(fileName, "r");
  // if (fp == NULL) {
  //   fprintf(stderr,"\nFailed to Open File\n");
  //   exit(-1);
  // }

  fscanf(stdin, "%d %d %d", &process_Size, &threadOverhead_Time, &processOverhead_Time);

  p = (Process*)malloc(process_Size * sizeof(Process));

  for (i = 0; i<process_Size; i++) {
    fscanf(stdin, "%d %d", &p[i].processNumber, &p[i].thread_Size);
    numThreads += p[i].thread_Size;
    for (j = 0; j<p[i].thread_Size; j++) {
      fscanf(stdin, "%d %d %d", &p[i].threadsArray[j].threadNumber, &p[i].threadsArray[j].arrivalTime, &p[i].threadsArray[j].io_Size);
      for (k = 0; k<p[i].threadsArray[j].io_Size-1; k++) {
        fscanf(stdin, "%d %d %d", &p[i].threadsArray[j].ioArray[k].threadIONumber, &p[i].threadsArray[j].ioArray[k].cpu_Time, &p[i].threadsArray[j].ioArray[k].io_Time);
        if (k == 0) {
          insert(p[i].threadsArray[j].arrivalTime, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[k].threadIONumber, p[i].threadsArray[j].ioArray[k].cpu_Time, p[i].threadsArray[j].ioArray[k].io_Time, 0);

          // if (verbose_Mode == true) {
          //   printf("At Time %d: Thread %d of Process %d moves from new to ready\n", p[i].threadsArray[j].arrivalTime, p[i].threadsArray[j].threadNumber, p[i].processNumber);
          // }

        } else {
          insert(999, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[k].threadIONumber, p[i].threadsArray[j].ioArray[k].cpu_Time, p[i].threadsArray[j].ioArray[k].io_Time, 0);
        }
      }
      fscanf(stdin, "%d %d", &p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, &p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time);
      if (k == 0) {
        insert(p[i].threadsArray[j].arrivalTime, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time, 0, 0);

        // if (verbose_Mode == true) {
        //   printf("At Time %d: Thread %d of Process %d moves from new to ready\n", p[i].threadsArray[j].arrivalTime, p[i].threadsArray[j].threadNumber, p[i].processNumber);
        // }

      } else {
        insert(999, p[i].processNumber, p[i].threadsArray[j].threadNumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].threadIONumber, p[i].threadsArray[j].ioArray[p[i].threadsArray[j].io_Size].cpu_Time, 0, 0);
      }
    }
  }

  threadTable = (ThreadInformation*)malloc((numThreads) * sizeof(ThreadInformation));
  table_size = numThreads;
  //fclose(fp);
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

  int nextBurstinThread = -1;
  int updatedArrivalTime = -1;

  while (size != -1) {
    tmp = extractMin();

    if (verbose_Mode == true) {
      printf("At Time %d: Thread %d of Process %d moves from new to ready\n", tmp.arrivalTime, tmp.threadNumber, tmp.processNumber);
    }
    // Update Overhead Costs (First Burst vs Process vs Thread)
    if (prev_process == 0) {
      overHeadCost = 0;
    } else if (prev_process != tmp.processNumber) {
      overHeadCost = processOverhead_Time;
    } else if (prev_thread != tmp.threadNumber) {
      overHeadCost = threadOverhead_Time;
    }

    // Update all Previous Varaibels used to calculate following Burst Arrival Time
    tmp_EnterCPU = prev_CPU + overHeadCost + prev_EnterCPU;
    if (verbose_Mode == true) {
      printf("At Time %d: Thread %d of Process %d moves from ready to running\n", tmp_EnterCPU, tmp.threadNumber, tmp.processNumber);
    }
    prev_process = tmp.processNumber;
    prev_thread = tmp.threadNumber;
    prev_CPU = tmp.cpu;
    prev_EnterCPU = tmp_EnterCPU;

    // Update Run Time
    tmp_RunTime = tmp_EnterCPU + tmp.cpu;
    if (verbose_Mode == true) {
      printf("At Time %d: Thread %d of Process %d moves from running to terminated\n", tmp_RunTime, tmp.threadNumber, tmp.processNumber);
    }

    // Update Total Time in CPU
    timeinCPU += tmp.cpu;


    // Update Thread Information Table
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
  printf("CPU Utilization is %.1lf\n", utilizationCPU);
  // printf("Total Time in CPU = %d units\n", timeinCPU);

  if (detailed_Mode == true) {
    for (i = 0; i < table_size; i++) {
      printf("Thread %d of Process %d:\n", threadTable[i].threadNumber, threadTable[i].processNumber);
      printf("Arrival Time: %d\n", threadTable[i].arrivalTime);
      printf("Service Time: %d units, I/O Time: %d units, Turnaround Time: %d units, Finish Time: %d units\n", threadTable[i].serviceTime, threadTable[i].ioTime, threadTable[i].turnAroundTime, threadTable[i].finishTime);
    }
  }


}

void rr(int q)
{
  int i = 0;
  int j = 0;
  int table_Index = 0;
  int check = 0;
  bool dnf = false;

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

  int nextBurstinThread = -1;
  int updatedArrivalTime = -1;

  while (size != -1) {
    tmp = extractMin();

    if (verbose_Mode == true) {
      printf("At Time %d: Thread %d of Process %d moves from new to ready\n", tmp.arrivalTime, tmp.threadNumber, tmp.processNumber);
    }

    // Update Overhead Costs (First Burst vs Process vs Thread)
    if (prev_process == 0) {
      overHeadCost = 0;
    } else if (prev_process != tmp.processNumber) {
      overHeadCost = processOverhead_Time;
    } else if (prev_thread != tmp.threadNumber) {
      overHeadCost = threadOverhead_Time;
    } else {
      overHeadCost = 0;
    }

    // Update all Previous Variables used to calcuate following Burst Arrival Time
    tmp_EnterCPU = prev_CPU + overHeadCost + prev_EnterCPU;

    if (verbose_Mode == true) {
      printf("At Time %d: Thread %d of Process %d moves from ready to running\n", tmp_EnterCPU, tmp.threadNumber, tmp.processNumber);
    }

    if (tmp.arrivalTime > tmp_EnterCPU) {
      tmp_EnterCPU = tmp.arrivalTime;
    }

    // Time Quantum Check and Update
    if (tmp.cpu > q) {
      prev_CPU = q;
      tmp.cpu = tmp.cpu - q;
      tmp.dnf = true;
      dnf = true;
    } else {
      prev_CPU = tmp.cpu;
      dnf = false;
    }

    prev_process = tmp.processNumber;
    prev_thread = tmp.threadNumber;
    prev_EnterCPU = tmp_EnterCPU;

    // Update Run Time
    tmp_RunTime = tmp_EnterCPU + prev_CPU;

    if (verbose_Mode == true) {
      if (dnf == false) {
        printf("At Time %d: Thread %d of Process %d moves from running to terminated\n", tmp_RunTime, tmp.threadNumber, tmp.processNumber);
      } else {
        printf("At Time %d: Thread %d of Process %d moves from running to blocked\n", tmp_RunTime, tmp.threadNumber, tmp.processNumber);
      }
    }

    // Update Total Time in CPU
    timeinCPU += tmp.cpu;

    // Update Thread Information Table
    for (j = 0; j<table_size; j++) {
      check = 0;
      if (threadTable[j].processNumber == tmp.processNumber && threadTable[j].threadNumber == tmp.threadNumber) {
        threadTable[j].finishTime = tmp_RunTime;
        threadTable[j].turnAroundTime = threadTable[j].finishTime - threadTable[j].arrivalTime;
        threadTable[j].serviceTime += tmp.cpu;
        if (tmp.dnf != true) {
          threadTable[j].ioTime += tmp.io;
        }
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
    if (dnf == true) {
      updatedArrivalTime = tmp_EnterCPU + tmp.cpu;
      insert(updatedArrivalTime, tmp.processNumber, tmp.threadNumber, tmp.burstNumber, tmp.cpu, tmp.io, true);
    } else {
      nextBurstinThread = findinHeap(tmp.processNumber, tmp.threadNumber, tmp.burstNumber);
      if (nextBurstinThread != -1) {
        updatedArrivalTime = tmp_EnterCPU + tmp.cpu + tmp.io;
        changePriority(nextBurstinThread, updatedArrivalTime);
      }
    }
    // i = 0;
    // printf("\n\nUpdated Heap\n");
    // while (i <= size) {
    //   printf("A_Time = %d \t P_# = %d \t T_# = %d \t B_# = %d \t CPU_T = %d \t IO_T = %d \t DNF = %d\n", rdyQ[i].arrivalTime, rdyQ[i].processNumber, rdyQ[i].threadNumber, rdyQ[i].burstNumber, rdyQ[i].cpu, rdyQ[i].io, rdyQ[i].dnf);
    //   i++;
    // }

  }
  totalRunTime = tmp_RunTime;
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
  // printf("Total Time in CPU = %d units\n", timeinCPU);
  printf("CPU Utilization is %.1lf\n", utilizationCPU);

  if (detailed_Mode == true) {
    for (i = 0; i < table_size; i++) {
      printf("Thread %d of Process %d:\n", threadTable[i].threadNumber, threadTable[i].processNumber);
      printf("Arrival Time: %d\n", threadTable[i].arrivalTime);
      printf("Service Time: %d units, I/O Time: %d units, Turnaround Time: %d units, Finish Time: %d units\n", threadTable[i].serviceTime, threadTable[i].ioTime, threadTable[i].turnAroundTime, threadTable[i].finishTime);
    }
  }

}
