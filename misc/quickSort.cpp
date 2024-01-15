/**********************************
Templated created by Kazumi Slott
CS311

Your name:Connor Toro
Your programmer number: 31
Hours spent: 2
Any difficulties?:nope.
***********************************/
#include <iostream>
using namespace std;
//?????????? include your swap.h for mySwap().  If you didn't make it for our first homework or it didn't work, you could implement it down below within this program.

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

/*
//Implement mySwap() here if you didn't make mySwap() in swap.h for our first homework.
//It is good to have the swap function so partition() won't get crowded. 
void mySwap(?????????????)
{
}
*/
template <class T>
void mySwap(T& a, T& b) {
   T temp = a;
   a = b;
   b = temp;
}

int partition(int ar[], int start, int end)
{
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.
  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).

  //For implementation of this function, refer to my lecture notes "quick sort". 
  //If you used a different algorithm, I would assume you cheated and give you zero points.

  //This function returns the index where the pivot value went in.
  mySwap(ar[(start+end)/2], ar[end]);
  int pivot = ar[end];
  int i = start;

  for(int j = start; j < end; j++) {
    if(ar[j] <= pivot) {
      mySwap(ar[j], ar[i]);
      i++;
    }
  }
  mySwap(ar[i], ar[end]);
  return i;
}

void quickSort(int ar[], int start, int end)
{
  /*
  if(????????) //If the partition has only one element or none, return. 
                   //In other words, if the partition has at least 2 elements, go inside the if.
                   //use start and end to figure out how many elements you have in the partition.
    {
      //call partition.
      //quickSort on the left partition
      //quickSort on the right partition
    }
  */
  if(end <= start) return;

  int pivot = partition(ar, start, end);
  quickSort(ar, start, pivot - 1);
  quickSort(ar, pivot + 1, end);  

}

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
