/******************************************************************************************************
Prepared by Kazumi Slott
CS311
Additional functions for graph part 2
*******************************************************************************************************/

/******************************************************************************************************
Add the following 3 functions to your graph.h.
Notice the first 2 functions are not member functions. I could have made them member functions, but I decided
not to. showShortestDistance() is like a part of an application. printHeapArrays() is just for testing.
You can list them above dijkstraShortestPath() in graph.h.
*******************************************************************************************************/

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

 
  cout << "\nThe distance is " << ??????? << endl;      
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
  minHeap<int> toBeChecked(num_ver); //the top of this heap has the vertex with the shortest distance
  declare a dynamic array called curDist //contains the current shortest distance from start to every other vertex
  declare a dynamic array called predecessor //contains the predecessor of each vertex
  declare a dynamic array called locator //tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertext 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap

  //The algorithm is in my lecture notes. Make sure you understand how each array and heap changes by reading my homework document posted on Canvas.

  //initialize each array
  //curDist should be 999 for all vertices to start with 

  //populate toBeChecked heap 
  //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers

  //to start with, locator [0, 1, 2, 3, 4, ...] 
    
  //Initialize predecessor for each vertex to -1

  //A lof of code here - check the algorithm in my lecture notes	


  //Now currDist and predecessor have the info about the shortest distance from start to every other vertex and the predecessor of each vertex
  showShortestDistance(curDist, predecessor, start);//print the result 
}


/******************************************************************************
Make a copy of minHeap.h and name it minHeap-graph.h (dash not underscore)
Add the following 2 functions to your minHeap-graph.h
A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.
To see why, check minHeap::fixHeap() below.
Don't forget to include minHeap-graph.h to graph.h
******************************************************************************/

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
  //For up, call bubbleUp(). For down, call min_heapify().                                                                      

  //Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.

  //Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.	
}



