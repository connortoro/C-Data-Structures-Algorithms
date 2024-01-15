/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: connor toro
Your programmer number: 31
Hours spent making and testing your min heap class: 1
An y difficulties?: nope
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();
  int getNum() const;
  void fixHeap(int* curDist, int* locator, int i);
  void bubbleUp(int* curDist, int* locator, int i);

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

template <class T>
minHeap<T>::minHeap(int c) {
  capacity = c;
  ar = new T[c];
  num = 0;
}

template <class T>
void exchange(T& a, T& b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
void minHeap<T>::bubbleUp(int i) {
  if(i == 0) return;

  int parent = (i-1)/2;

  if(ar[parent] > ar[i]) {
    exchange(ar[parent], ar[i]);
    bubbleUp(parent);
  }
}

template <class T>
void minHeap<T>::insert(const T& el)
{
  if(num >= capacity) throw Overflow();
  ar[num] = el;
  bubbleUp(num);
  num++;
}

template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++) {
    //cout << "Key: " << key << ", ar[i]: " << ar[i] << endl;
    if(ar[i] == key) {
      return i;
    }
  }


  //The element doesn't exist
  return -1;
}

template <class T>
void minHeap<T>::remove(int i)
{
  if(i >= num) throw BadIndex();
  exchange(ar[i], ar[num-1]);
  num--;
  min_heapify(i);
  if(i > 0 && ar[(i-1)/2] < ar[i]) bubbleUp(i);
}

template <class T>
void minHeap<T>::min_heapify(int i) {
  int l = (2*i) + 1; //the index of the left child of i
  int r = (2*i) + 2; //the index of the right child of i

  int smallest = i;
  if(l < num && ar[smallest] > ar[l]) smallest = l;
  if(r < num && ar[smallest] > ar[r]) smallest = r;

  //The smallest is either the right or left child. We need to exchange the parent with it.
  if(smallest != i)
    {
      //exchange the 2 values
      exchange(ar[i], ar[smallest]);
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
      min_heapify(smallest);
    }
}

template <class T>
T minHeap<T>::getMin()
{
  //This function removes the top element and returns it.
  //You should be calling remove()
  T temp = ar[0];
  remove(0);
  return temp;
}

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h) {
if(h.num == 0) {
  cout << "none" << endl;
  return o;
}
for(int i = 0; i < h.num; i++) {
  cout << h.ar[i] << " ";
}
return o;
}

//return the number of elements in the heap.
template <class T>
int minHeap<T>::getNum() const
{
  return num;
}

//i is the index (within heap) of the vertex whose distance was changed.
//For example, if vertex 0's distance changed when it is located at 3, i is 3. This is where the heap needs to be fixed by either going up or down.
//curDist is the array that contains the shortest distance from start to every other vertex.
//locator is the array that contains the location of each vertex within the heap. Make sure you understand the homework document posted on Canvas to understand how locator works.
template <class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{

  //We need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. Make sure you understand how each array works by reading the homework document (there are pictures to explain).

  //From i, either bubble up or down.
  if(i >= num) return;
  bubbleUp(curDist, locator, i);
  //For up, call bubbleUp(). For down, call min_heapify().

  //Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.

  //Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.
}

template <class T>
void minHeap<T>::bubbleUp(int* curDist, int* locator, int i)
{
  if(i == 0) return;
  int parent = (i-1)/2;
  if(curDist[ar[parent]] > curDist[ar[i]]) {
    exchange(locator[ar[parent]], locator[ar[i]]);
    exchange(ar[parent], ar[i]);
    bubbleUp(curDist, locator, parent);
  }
}

#endif
