/**********************************
Templated created by Kazumi Slott
CS311

Your name: Connor Toro
Your programmer number: 31
Hours spent: 1
Any difficulties?: nope
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
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

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
