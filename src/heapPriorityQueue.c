/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 03/16/22
 * Extension: 03/23/22
 * This file comprises the functions to create and use the Heap Priority Queue
*/

int size = -1;

#include "heapPriorityQueue.h"

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
  while (i > 0 && heap[parent(i)] < heap[i]) {
    swap(&heap[parent(i)], &heap[i]);
    i = parent(i);
  }
}

void shiftDown(int i)
{
  int maxIndex = i;
  int l = leftChild(i);

  if (l <= size && heap[l] > heap[maxIndex]) {
    maxIndex = l;
  }

  int r = rightChild(i);

  if (r <= size && heap[r] > heap[maxIndex]) {
    maxIndex = r;
  }

  if (i != maxIndex) {
    swap(&heap[i], &heap[maxIndex]);
    shiftDown(maxIndex);
  }
}

void insert(int p)
{
  size = size + 1;
  heap[size] = p;

  shiftUp(size);
}

int extractMax()
{
  int result = heap[0];

  heap[0] = heap[size];
  size = size - 1;

  shiftDown(0);
  return result;
}

void changePriority(int i, int p)
{
  int oldp = heap[i];
  heap[i] = p;

  if (p > oldp) {
    shiftUp(i);
  } else {
    shiftDown(i);
  }
}

int getMax()
{
  return heap[0];
}

void removeFromHeap(int i)
{
  heap[i] = getMax() + 1;

  shiftUp(i);

  extractMax();
}

void swap(int* a, int* b)
{
  int tmp = *b;
  *b = *a;
  *a = tmp;
}
