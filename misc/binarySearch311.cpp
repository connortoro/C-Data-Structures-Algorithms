/*************************
Template created by Kazumi Slott
CS311

[kslott@empress cs311]$ ./a.out
TEST0-1
-1
TEST0-2
0
TEST1
L, R = 0, 8
L, R = 0, 3
L, R = 2, 3
2
TEST2
L, R = 0, 5
L, R = 0, 1
L, R = 1, 1
1
TEST3
L, R = 0, 8
L, R = 0, 3
L, R = 2, 3
L, R = 2, 1
-1
[kslott@empress cs311]$
**************************/
#include <iostream>
using namespace std;

/****************************************************************************
This function returns the index where key is found or -1 if key is not found.

a is an integer array of any size sorted in descending order.
s is the size of the array.
key is the number being searched for.
****************************************************************************/
int binarySearchDescend(const int a[], int s, int key)
{
  int l = 0; //left boudary starts at first index
  int r = s-1; //right boundary starts at last index
  int m; //middle point between left and right.

  //When l and r cross over, search ends. --> key was not found.
  while(l < r)
    {
      //calculate the middle point between l and r
      m = (l+r)/2;

      if(a[m] == key){
        return m;
      } else if(a[m] < key){
        r = m;
      } else{
        l = m;
      }
    }

  return -1; //key wasn't found
}

//a is sorted in ascending order
//key is what you are looking for
//L and R: you are searching for key in a[L..R]
//This function returns index where key was found or -1 if not found.
int binarySearch(const int a[], int key, int L, int R)
{
  int m = (L+R)/2; //middle of [L..R]
  //keep this cout. You need to verify your code by comparing your outputs to the expected outputs listed above.
  cout << "L, R = " << L << ", " << R << endl;
  if(L >= R) return -1;
  if(a[m] == key) return m;
  if(a[m] < key){
    return binarySearch(a, key, m+1, R);
  } else if(a[m] > key){
    return binarySearch(a, key, L, m-1);
  }
  //complete this function by using recursion.
}

//Don't change this main.
//These test cases 1 to 3 are from my CS111 lecture notes and lecture recording.  If your outputs are different, check the following lec notes and video.
//CS111 Lecture Notes 6-1: arrays - single dimensional Pages 14-16
//CS111 Recording of lecture on November 13(Fri) - binary search and selection sort
int main()
{
  cout << "TEST0-1" << endl;
  int ar0[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  cout << binarySearchDescend(ar0, 10, 11) << endl; //-1

  cout << "TEST0-2" << endl;
  cout << binarySearchDescend(ar0, 10, 10) << endl; //0
  cout << "TEST1" << endl;

  int ar1[] = {5, 10, 11, 28, 55, 59, 62, 80, 98};
  cout << binarySearch(ar1, 11, 0, 8) << endl;

  cout << "TEST2" << endl;
  int ar2[] = {1, 10, 20, 30, 40, 50};
  cout << binarySearch(ar2, 10, 0, 5) << endl;

  cout << "TEST3" << endl;
  int ar3[] = {5, 9, 11, 28, 55, 59, 62, 80, 98};
  cout << binarySearch(ar3, 10, 0, 8) << endl;

  return 0;
}
