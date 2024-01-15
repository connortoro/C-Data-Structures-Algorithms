/**************************************************************************
~/cs311/stack_L_T_client.cpp
Implemented by Kazumi Slott
2-9-2022

Testing stack implemented with a linked list with an exception class
**************************************************************************/
#include <iostream>
using namespace std;
#include "stack_L_T.h"

void func(const Stack<int>& s);

int main()
{
/**********************************************************************************
You know what data type you are using for the stack in client. You don't use T here.
***********************************************************************************/

  Stack<int> s;

  if(s.empty())
    cout << "Empty" << endl; //Empty

  try
    {
      s.pop();
    }
  catch(Stack<int>::Underflow)
    {
      cout << "Illegal operation. - Stack is empty" << endl;
    }

  //recovered from the error - If we didn't use try-catch, the program would abort here.

  //cout << s.getSize() << endl; //0
  s.push(1);
  s.push(2);
  //cout << s.getSize() << endl; //2

  cout << s << endl; /*--- Top ---
		       2
		       1
		       --- Bottom ---*/

  s.getTop()++; //T& return type lets you change top element. Top is now 3 from 2.

  int& r = s.getTop(); //r points to the top element
  cout << "address of top->elem" << &r << endl; //You could compare the address of r to the address of top element inside stack class. They are the same.

  r += 200; //adds 200 to top element
  cout << r << endl; //203

  int top = s.getTop(); //top gets 203
  cout << top << endl; //203
  top++; //top becomes 204
  cout << s.getTop() << endl; //But the top element is still 203

  cout << s << endl; /*--- top ---
		       203
		       1
		       --- Bottom ---*/

  Stack<int> s2;
  s2 = s; //operator=() is called here.
  //cout << s.getSize() << endl; //2

  cout << s2 << endl; /*--- top ---
			203
			1
			--- Bottom ---*/

  func(s); //testing const T& getTop() const

  Stack<int> s3(s); //testing the copy constructor
  cout << s3 << endl; /*--- top ---
			203
			1
			--- Bottom ---*/

  return 0;
}

//s is a const object, so it needs to call the const version of getTop().
void func(const Stack<int>& s)
{
  cout << "Calling the const version of getTop()" << endl;
  cout << s.getTop() << endl;
  //s.getTop()++; //compilation error. We cannot change s.
}
