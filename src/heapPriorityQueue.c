/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Extension: 03/23/22
 * This file comprises the functions to create and use the Heap Priority Queue
*/

#include "heapPriorityQueue.h"

// Global Variables
int size = -1;
ReadyQueue rdyQ[50];

int parent(int i)
{
  return (i - 1) / 2;
}

int leftChild(int i)
{
  return ((2 * i) + 1);
}

int rightChild(int i)
{
  return ((2 * i) + 2);
}

void shiftUp(int i)
{
  while (i > 0 && rdyQ[parent(i)].arrivalTime >= rdyQ[i].arrivalTime) {
    if (rdyQ[parent(i)].arrivalTime == rdyQ[i].arrivalTime) {
      if (rdyQ[parent(i)].processNumber > rdyQ[i].processNumber) {
        swap(&rdyQ[parent(i)], &rdyQ[i]);
        i = parent(i);
      } else {
        return;
      }
    } else {
      swap(&rdyQ[parent(i)], &rdyQ[i]);
      i = parent(i);
    }
  }
}

void shiftDown(int i)
{
  int minIndex = i;
  int l = leftChild(i);

  if (l <= size && rdyQ[l].arrivalTime <= rdyQ[minIndex].arrivalTime) {
    if (rdyQ[l].arrivalTime == rdyQ[minIndex].arrivalTime) {
      if (rdyQ[l].processNumber < rdyQ[minIndex].arrivalTime) {
        minIndex = l;
      }
    } else {
      minIndex = l;
    }
  }

  int r = rightChild(i);

  if (r <= size && rdyQ[r].arrivalTime <= rdyQ[minIndex].arrivalTime) {
    if (rdyQ[l].arrivalTime == rdyQ[minIndex].arrivalTime) {
      if (rdyQ[l].processNumber < rdyQ[minIndex].arrivalTime) {
        minIndex = r;
      }
    } else {
      minIndex = r;
    }
  }

  if (i != minIndex) {
    swap(&rdyQ[i], &rdyQ[minIndex]);
    shiftDown(minIndex);
  }
}

void insert(int a, int p, int t, int b, int cpu, int io, int entCPU)
{
  size = size + 1;
  rdyQ[size].arrivalTime = a;
  rdyQ[size].processNumber = p;
  rdyQ[size].threadNumber = t;
  rdyQ[size].burstNumber = b;
  rdyQ[size].cpu = cpu;
  rdyQ[size].io = io;
  rdyQ[size].enterCPUTime = entCPU;

  shiftUp(size);
}

ReadyQueue extractMin()
{
  ReadyQueue result = rdyQ[0];

  rdyQ[0] = rdyQ[size];
  size = size - 1;

  shiftDown(0);
  return result;
}

void changePriority(int i, int p)
{
  int oldp = rdyQ[i].arrivalTime;
  rdyQ[i].arrivalTime = p;

  if (p < oldp) {
    shiftUp(i);
  } else {
    shiftDown(i);
  }
}

int findinHeap(int p, int t, int b)
{
  int i = 0;
  while (i <= size) {
    if (rdyQ[i].processNumber == p && rdyQ[i].threadNumber == t && rdyQ[i].burstNumber == b+1) {
      return i;
    }
    i++;
  }
  return -1;
}

ReadyQueue getMin()
{
  return rdyQ[0];
}

void removeFromHeap(int i)
{
  rdyQ[i] = getMin();

  shiftUp(i);

  extractMin();
}

void swap(ReadyQueue* a, ReadyQueue* b)
{
  ReadyQueue tmp = *b;
  *b = *a;
  *a = tmp;
}
