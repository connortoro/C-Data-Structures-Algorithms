/****************************
Templated created by Kazumi Slott
CS311

Your name: Connor Toro
Your programmer number: 31
Hours spent: 3
Any difficulties?:
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include "minHeap-graph.h"
using namespace std;

class edge
{
  friend class graph;  //What do you need here if you want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object
                       //Let's use the library's list class. It is actually a doubly linked list.
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void  DijkstraShortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object.
  //The element of a node in the linked list is a pointer to an edge object
  num_ver = num;
  ver_ar = new list<edge*>[num_ver];
}

graph::~graph()
{
  //destroy all the edge objects created in heap
  //For each vertex in ver_ar
  //  go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.

  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array
  for(int i = 0; i < num_ver; i++) {
    for(list<edge*>::iterator u = ver_ar[i].begin(); u != ver_ar[i].end(); u++) {
      delete *u;
    }
  }
  delete[] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
  ver_ar[v].push_back(new edge(u, w));
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  //I created a queue object of string data type from the library's queue class to save all the paths.

  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.


  //You could call displayQueue() implemented above to display all the paths.

  //Don't forget to destroy the dynamic array
  queue<string> q;
  int* num = new int[num_ver];
  for(int i = 0; i < num_ver; i++) num[i] = 0;

  int s = start;
  while(nextUnvisitedNodes(num, start, s) != -1) {
    int v = nextUnvisitedNodes(num, start, s);
    DFT_helper(v, s, num, q);
    s = v + 1;
  }
  displayQueue(q);
  delete[] num;
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertex we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.
//num is the array of vertices
//start is the start vertex
//s is the vertext right after the vertex we started last time
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.
  for(int i = s; i < num_ver; i++) {
    if(num[i] == 0) return i;
  }
  return -1;
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  //The algorithm is in my lecture notes

  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/
  //iterator class is nested inside list class
  // for (list<??????>::iterator u = ???????.begin(); u != ??????.end(); u++)
  //   {
  //     //From the example on https://www.cplusplus.com/reference/list/list/end/
  //     //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
  //     //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.

  //     //push each path e.g. 0->1 into q. to_string(int) converts int to string.
  //     //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp
  //     q.push(to_string(v) + "->" + to_string((*u)->neighbor));

  //   }

  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp
   **********************************************************************************************
   ***********************************************************************************************/
  num[v] = 1;
  cout << v << " ";
  for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++) {
        edge* curr = *u;
        if(num[curr->neighbor] == 0) {
          q.push(to_string(v) + "->" + to_string(curr->neighbor));
          DFT_helper(curr->neighbor, i, num, q);
        }
      }

}

//start is the index for the start vertex
void graph::BFT(int start)
{
  //The algorithm is in my lecture notes

  //Use the queue class from the library

  //I used another queue of strings to save all the paths.

  //I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited vertices.

  //Check the specification to figure out what member functionyou need to use.
  // https://www.cplusplus.com/reference/queue/queue/

  //You could call show all paths by calling displayQueue()s of the queue class

  //Don't forget to destroy the dynamic array if you used one
  queue<int> q;
  queue<string> edges;

  int* num = new int[num_ver];
  for(int i = 0; i < num_ver; i++) {num[i] = 0;}

  int s = start;
  while(nextUnvisitedNodes(num, start, s) != -1) {

    int v = nextUnvisitedNodes(num, start, s);
    num[v] = 1;
    q.push(v);
    s = v + 1;

    while(!q.empty()) {
      v = q.front();
      q.pop();
      cout << v << " ";
      for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++) {
        edge* curr = *u;
        if(num[curr->neighbor] == 0) {
          num[curr->neighbor] = 1;
          q.push(curr->neighbor);
          edges.push(to_string(v) + "->" + to_string(curr->neighbor));
        }
      }
    }
  }
  displayQueue(edges);
  delete[] num;
}

//dijkstra's algorithm calculates the shortest distance from start to every other vertex
//This stand alone function shows the shortest path from start to destination in the following format.
//  The shortest path from 3 to 5 is 3 0 4 5
//  The distance is 8
void showShortestDistance(int* curDist, int* predecessor, int start)
{
  int dest; //destination
  cout << "Enter the destination: ";
  cin >> dest;

  //trace the shortest path from dest back to start
  //I suggest you use either library's stack or queue. Which one will work?


  cout << "The shortest path from " << start << " to " << dest << " is ";

  stack<int> q;
  q.push(dest);
  int curr = dest;
  while(predecessor[curr] != -1) {
    q.push(predecessor[curr]);
    curr = predecessor[curr];
  }

  while(!q.empty()) {
    cout << q.top() << " ";
    q.pop();
  }

  cout << "\nThe distance is " << curDist[dest] << endl;
}

//You don't need to change the following function.
//This function is for checking the heap and all the arrays. You may want to call it while you are developing Dijkstra's function
//This is not part of the graph class.  It is made for testing anyway.
void printHeapArrays(const minHeap<int>& h, int* curDist, int* locator, int* predecessor, int num_ver)
{
  cout << "heap ------" << endl;
  cout << h << endl;  //This works if you made operator<<() to display a heap

  cout << "locator ------" << endl;
  for(int i = 0; i < num_ver; i++)
    cout << locator[i] << " ";
  cout << endl;

  cout << "curDist ------- " << endl;
  for(int i = 0; i < num_ver; i++)
    cout << curDist[i] << " ";
  cout << endl << endl;

  cout << "Predecessor ------- " << endl;
  for(int i = 0; i < num_ver; i++)
    cout << predecessor[i] << " ";
  cout << endl << endl;
}

//Dijkstra's shortest path. This function will generate a table that contains the shortest distance from start to every other vertex and the predecessor of each vertex.
void graph::DijkstraShortestPath(int start)
{
  minHeap<int> toBeChecked(num_ver);   //the top of this heap has the vertex with the shortest distance
  int* curDist = new int[num_ver];     //contains the current shortest distance from start to every other vertex
  int* predecessor = new int[num_ver]; //contains the predecessor of each vertex
  int* locator = new int[num_ver];     //tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertext 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap

  //The algorithm is in my lecture notes. Make sure you understand how each array and heap changes by reading my homework document posted on Canvas.

  //initialize each array
  //curDist should be 999 for all vertices to start with
  //populate toBeChecked heap
  //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers
  //to start with, locator [0, 1, 2, 3, 4, ...]
  //Initialize predecessor for each vertex to -1
  for(int i = 0; i < num_ver; i++) {
    curDist[i] = 999;
    locator[i] = i;
    predecessor[i] = -1;
    toBeChecked.insert(i);
  }
  int v = start;
  curDist[v] = 0;
  toBeChecked.fixHeap(curDist, locator, locator[v]);
 //while heap not empty, take smallest, iterate through edge list,
 //if new connection costs less, then replace curDist, and update heap(if still in)
  while(toBeChecked.getNum() > 0) {
    v = toBeChecked.getMin();
    for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++) {
      edge* curr = *u;
      if((curDist[v] + curr->wt) < curDist[curr->neighbor]) {
        curDist[curr->neighbor] = curDist[v] + curr->wt;
        predecessor[curr->neighbor] = v;
        toBeChecked.fixHeap(curDist, locator, locator[curr->neighbor]);
      }
    }
  }


  //Now currDist and predecessor have the info about the shortest distance from start to every other vertex and the predecessor of each vertex
  showShortestDistance(curDist, predecessor, start);//print the result
}
#endif
