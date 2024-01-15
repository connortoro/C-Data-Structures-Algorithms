/***************************************
Template prepared by Kazumi Slott
CS311
This program sorts an array of persons.

Your name: Connor Toro
Your programmer number: 31
Hours spent: 2
Any difficulties?: Instructions are very unclear as to what to do
****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()
bool firstComparison(person a, person b) {
  return a.fN < b.fN;
}

bool lastComparison(person a, person b) {
  return a.lN < b.lN;
}

bool gradeComparison(person a, person b) {
  return a.grade < b.grade;
}

void stableSort(person ar[], int n, bool (&check)(person, person))
{
  for(int i = 0; i < n-1; i++) {
    int j = i+1;
    while(j > 0 && check(ar[j], ar[j-1])) {
      swap(ar[j], ar[j-1]);
      j--;
    }
  }
}

int main()
{
  person ar[SIZE];
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      stableSort(ar, 13, firstComparison);
      stableSort(ar, 13, lastComparison);
      stableSort(ar, 13, gradeComparison);

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  return 0;
}


