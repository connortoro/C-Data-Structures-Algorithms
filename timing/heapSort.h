/*****************************************
Template written by Kazumi Slott
CS311

Your name: Connor Toro
Your programmer number: 31
Hours spent: 1.5
Any difficulties?: nope
*******************************************/
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

/*
Parent of i = (i-1)/2
Left child of i = 2i + 1
Right child of i = 2i + 2
*/

//print an integer array of size n
void print(int ar[], int n)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//called from max_heapify and heapSort
void exchange(int& a, int& b)
{
  int temp = a;
  a = b;
  b = temp;
}

//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
void max_heapify(int ar[], int n, int i)
{

  int l = (2*i) + 1; //the index of the left child of i
  int r = (2*i) + 2; //the index of the right child of i

  //the index of the largest value amoung the values at i, l and r
  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range.
  //I have 4 lines of code here. You can have more or less.
  int largest = i;
  if(l < n && ar[largest] < ar[l]) largest = l;
  if(r < n && ar[largest] < ar[r]) largest = r;

  //The largest is either the right or left child. We need to exchange the parent with it.
  if(largest != i)
    {
      //exchange the 2 values
      exchange(ar[i], ar[largest]);
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
      max_heapify(ar, n, largest);
    }

}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
void build_max_heap(int ar[], int n)
{
  //2 lines of code in this function
  /*
  for each non-leaf node
     call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
  */
  for(int i = (n/2)-1; i >= 0; i--) {
    max_heapify(ar, n , i);
  }
}

//a is an unordered list to start with
//use max_heapify to sort a
//n is the number of elements in the array
void heapSort(int a[], int n)
{
  //I have 6 lines of code in this function. You can have more or less.

  //build max heap from an unordered list
  //call build_max_heap
  build_max_heap(a, n);

  int size = n; //size of the unsorted portion of the array

    while(size > 0) //repeat until heap is empty
    {
      //swap max element with last element - max element is now the last element
      exchange(a[0], a[size-1]);
      //discard the last element from the heap
      size--;
      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.
      max_heapify(a, size, 0);
    }
}

//this function corrects a violiation at i by bubbling it up to the correct place
//a is a heap
void bubbleUp(int a[], int i)
{
  if(i == 0) return;

  int parent = (i-1)/2;

  if(a[parent] < a[i]) {
    exchange(a[parent], a[i]);
    bubbleUp(a, parent);
  }
}

//a is a max heap
//cap is the capacity of the heap
//n is the number of elements the heap currently has before insertion
//el is the new element to be inserted
void insert(int a[], int cap, int& n, int el)
{
  if(n >= cap) throw "The array is full";
  a[n] = el;
  bubbleUp(a, n);
  n++;
}

//This function returns the index where key was found or throws an exception if key is not found.
//a is a max heap.
//n is the number of elements in the heap.
//key is the element we are looking for.
int find(const int a[], int n, int key)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)
    if(a[i] == key)
      return i;

  throw "The element doesn't exist";
}

//a is a max heap
//n is the number of elements the heap currently has before deletion, then decrememted after deletion
//i is the index of the element to be removed.
void remove(int a[], int& n, int i)
{
  if(i >= n) throw "The index to be removed is invalid";
  exchange(a[i], a[n-1]);
  n--;
  max_heapify(a, n, i);
  if(i > 0 && a[(i-1)/2] < a[i]) bubbleUp(a, i);

}
#endif
