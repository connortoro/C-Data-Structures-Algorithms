/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: this multiplies two input matrices, one of consisting of housing area equation coefficients, and another consisting of the values for different houses. resulting in a matrix that shows the different cost for each house in each different area.

Your name:Connor Toro 
Your programmer number:31
Number of hours you spent:.5
Any difficulties?:nope
*******************************************/
//What do you need to include? HINT: What are you using in main()?
//include your matrix.h
#include <iostream>
using namespace std;
#include "matrix.h"

int main()
{
  /*
  ?????
  Your matrices need to be of the same data type.  When you do multiplication, the data types of the 2 matrices need to be the same.

  //Create 2 input files yourself. You need to name them house_info.in and house_func.in, otherwise my auto-grader will not run your program.

  //Check matrixClient.cpp to see an example
  create fin
  open the first file (which file should be the first? You need to figure it out.)
  load the data into the first matrix
  close fin

  open the second file
  load the data into the second matrix
  close fin

  ?????
  use try and catch
  In catch, show the following message.
  cout << "SIZE ERROR" << endl;


  */
  Matrix<double> func(4, 3);
  Matrix<double> house(4, 4);

  ifstream fin;
  fin.open("house_func.in");
  fin >> func;
  fin.close();
  fin.open("house_info.in");
  fin >> house;
  fin.close();

  Matrix<double> result = house * func;
  cout << result << endl;
  return 0;
}
