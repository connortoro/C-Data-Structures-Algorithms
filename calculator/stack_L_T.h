/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Connor Toro
Your programmer number here: 31
Hours spent: 2
Any problems you had? Explain here: nope
###### Don't forget to specify the complexity above each function. ######
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream>
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template < class T >
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;
  Node* next;  //check how right and left pointers are declared in BST class --> /cs/slott/cs211/BST_T.h
 public:
  Node(){elem=NULL; next = nullptr;} //default constructor
  Node(const T& e) : elem(e), next(nullptr) {} //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

 private:
  Node<T>* top;

 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() {top = nullptr;} //Implement a small function inside the class definition
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{return top == NULL;} //implement a small function inside the class definition
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an empty exception class here. Underflow or/and Overflow? - You need to figure out where to throw an exception - I am throwing in 3 functions.
  class Underflow{};
};


//Complexity of this operation: O(1)
template <class T>
void Stack<T>::push(const T& val)
{
   //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h
  Node<T>* newNode = new Node<T>(val);
  newNode->next = top;
  top = newNode;
}



//Complexity of this operation: O(1)
template <class T>
void Stack<T>::pop()
{
  //throw an exception if the stack is empty. (You shouldn't call pop if the stack is empty.)
  if(empty()) {
    throw Underflow();
  }
  Node<T>* popped = top;
  top = top->next;
  delete popped;
}



//Complexity of this operation: O(1)
template <class T>
T& Stack<T>::getTop()
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  if(empty()) {
    throw Underflow();
  }
  return top->elem; //return the top element. Since the return type is T&, the client can change the top.
}



//Complexity of this operation: O(1)
template <class T>
const T& Stack<T>::getTop() const
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
  if(empty()) {
    throw Underflow();
  }
  return top->elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}




//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj);
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object).
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(n)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.
  Node<T>* temp = s.top;

  cout << "--- Top ---" << endl;

  while(temp) {
    cout << temp->elem << endl;
    temp = temp->next;
  }

  cout << "--- Bottom ---" << endl;

}



template <class T>
Stack<T>::~Stack()
{
  destroy();
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(n)
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  //destroy all nodes

  while(!empty()) {
    Node<T>* temp = top;
    top = top->next;
    delete temp;
  }

}


//Complexity of this operation: O(n)
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&).
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;


  //deep copy
  if(this != &rhs) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      destroy();
      copy(rhs);
    }
  return *this; //return the "this" object (not the address of the "this" object). Notice the return type is not void.
                  //By returning the this object, we can use multiple assignment operators.
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2).
}



//Complexity of this operation: O(n)
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from.
{
  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty. If the source stack is empty, "this" stack is also empty
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().
  if(source.empty()) return;

  top = new Node<T>(source.top->elem);
  Node<T>* temp = top;
  Node<T>* sourceTemp = source.top->next;


  while(sourceTemp) {
    temp->next = new Node<T>(sourceTemp->elem);
    temp = temp->next;
    sourceTemp = sourceTemp->next;
  }


}



//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object.
  //You still need to initialize the data member, top.
  top = nullptr;

  //Then you can call the copy function
  copy(other);
}



#endif // end the definition here
