/**************************************
Template created by Kazumi Slott
CS311

Your name:Connor Toro
Your programmer number:31
Hours spent:1
Any difficulties?:nope
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}


//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int ar[], int n)
{
  for(int i = 0; i < n-1; i++) {
    int j = i+1;
    while(j > 0 && ar[j] < ar[j-1]) {
      swap(ar[j], ar[j-1]);
      j--;
    }
  }
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document
void selectionSort(int array[], int N)
{
  int smallIndx; //the index of the smallest value

  //first is the first index in unsorted part
  for(int first = 0; first < N-1; first++)
    {
      smallIndx = N-1; //assume the last item is the smallest
      //find the smallest in unsorted part ([first..last])
      for(int i = N-1; i >= first; i--)
      {
        if(array[i] < array[smallIndx]) //The current item is smaller
          smallIndx = i;
      }

      //swap the smallest with the first item in the unsorted part
      swap(array[smallIndx],array[first]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum"
void bubbleSort(int ar[], int s)
{

  bool swapped = true; //true if there was swapping in the current iteration, false otherwise
  int last = s-1; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(swapped) //swapping required in the previous iteration or the first iteration starts
    {
      swapped = false; //no swapping has happened yet when a new iteration starts.

      for(int i = 1; i <= last; i++) //check each adjacent pair of items in the unsorted part
        {
	  if(ar[i-1] > ar[i]) //the pair is out of order
	    {
	      swap(ar[i], ar[i-1]);
	      swapped = true; //swapping required - meaning we need to proceed to the next iteration.
	    }
        }
      last--; //the area to be checked shrinks down after each iteration
    }//end of while

}


int partition(int ar[], int start, int end)
{
  swap(ar[(start+end)/2], ar[end]);
  int pivot = ar[end];
  int i = start;

  for(int j = start; j < end; j++) {
    if(ar[j] <= pivot) {
      swap(ar[j], ar[i]);
      i++;
    }
  }
  swap(ar[i], ar[end]);
  return i;
}

void quickSort(int ar[], int start, int end)
{
  if(end <= start) return;

  int pivot = partition(ar, start, end);
  quickSort(ar, start, pivot - 1);
  quickSort(ar, pivot + 1, end);
}


void merge(int ar[], int first, int last)
{
  int size = last - first + 1;
  int* temp = new int[size];

  int middle = (first + last) / 2;
  int left = first;
  int right = middle+1;

   for(int i = 0; i < size; i++){
     if(left > middle) {
       temp[i] = ar[right];
       right++;
       continue;
     }
     if(right > last) {
       temp[i] = ar[left];
       left++;
       continue;
     }
     if(ar[right] <= ar[left]) {
       temp[i] = ar[right];
       right++;
       continue;
     }
     if(ar[left] < ar[right]) {
       temp[i] = ar[left];
       left++;
       continue;
     }
   }
    //fill ar with temp and delete
    for(int i = 0; i < size; i++) {
      ar[first+i] = temp[i];
    }
    delete[] temp;
}

void mergeSort(int ar[], int first, int last)

{
  if(first >= last) return;
  int middle = (first + last)/2;
  mergeSort(ar, first, middle);
  mergeSort(ar, middle+1, last);
  merge(ar, first, last);
}


