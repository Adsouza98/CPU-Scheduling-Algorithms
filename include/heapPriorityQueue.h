#ifndef HEAP_PRIORITY_QUEUE
#define HEAP_PRIORITY_QUEUE

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

// Local Libraries


// Global Variables
int heap[50];

int parent(int i);
int leftChild(int i);
int rightChild(int i);
void shiftUp(int i);
void shiftDown(int i);
void insert(int p);
int extractMax();
void changePriority(int i, int p);
int getMax();
void removeFromHeap(int i);
void swap(int* a, int* b);

#endif
