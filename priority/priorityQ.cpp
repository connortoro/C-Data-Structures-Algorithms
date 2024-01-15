/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: priority queue
Your name: connor toro
Your programmer number: 31
Hours spent making this application: 2
Are you rejecting invalid inputs?: yes
Any difficulties: nope
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std;
#include "minHeap.h"
//#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
int getNum();

void checkIn(minHeap<int>& heap, int pos) {
  int severity;
  cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
  cin >> severity;
  heap.insert(severity * 10000 + pos);
  cout << "The queue has " << heap << endl;
}

void takePatient(minHeap<int>& heap) {
  try {
    cout << heap.getMin() << " is going to be treated now" << endl;
  } catch(...) {
    cout << "There are no patients waiting" << endl;
  }

  cout << "The queue has " << heap << endl;
}

const int START = 1000; //assuming this number will not go over 9999

int main(){
  int choice = 0;
  minHeap<int> heap(1000);
  int pos = START;
  showMenu();

  while(choice != 3){

    choice = getNum();

    switch(choice) {
      case 1:
        checkIn(heap, pos);
        pos++;
        showMenu();
        break;
      case 2:
        takePatient(heap);
        showMenu();
        break;
      case 3:
        break;
      default:
        cout << "Invalid choice. The choice should be 1, 2, or 3. ";
        break;
    }

    //You need to have the following prompt somewhere. You can move it to a different function.
    //cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
  }


  return 0;
}

//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer only.
int getNum()
{
   string choice; //For example, when asking for 10, the user enters ab
   bool bad;
   int num;

   do
     {
       bad = false;
       cout << "Enter a number: ";
       cin >> choice;

       try
	 {
	   num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
	 }
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. ";
	   bad = true;
	 }
     }while(bad == true);

   return num;
}

