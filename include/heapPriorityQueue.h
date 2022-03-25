#ifndef HEAP_PRIORITY_QUEUE
#define HEAP_PRIORITY_QUEUE

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

// Local Libraries

typedef struct {
  int arrivalTime;
  int processNumber;
  int threadNumber;
  int burstNumber;
  int cpu;
  int io;
  int enterCPUTime;
} ReadyQueue;

int parent(int i);
int leftChild(int i);
int rightChild(int i);
void shiftUp(int i);
void shiftDown(int i);
void insert(int a, int p, int t, int b, int cpu, int io, int entCPU);
int findinHeap(int p, int t, int b);
ReadyQueue extractMin();
void changePriority(int i, int p);
ReadyQueue getMin();
void removeFromHeap(int i);
void swap(ReadyQueue* a, ReadyQueue* b);

#endif
