/************************
Templated created by Kazumi Slott
CS311

Your name: Connor Toro
Your programmer number: 31
Hours spent: 2
Any difficulties?: nope
*********************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

class entry //this is basically a node
{
  //What do you do if hashTbl needs to access the private members of entry?
  //If you don't say private or public, it is private by default.
  friend class hashTbl;
  string ID;
  string name;
  int age;
  double GPA;
  entry* next; //points to the next entry

public:
  entry() { ID = name = "", age = -999, GPA = -999.0, next = NULL; }
  entry(const string& ID, const string& name, int age, double GPA ) { this->ID = ID, this->name = name, this->age = age, this->GPA = GPA, next = NULL; }
  string getID() const { return ID; }
  string getName() const { return name; }
  int getAge() const { return age; }
  double getGPA() const { return GPA; }
  entry* getNext() const { return next; }
};

class hashTbl
{
  entry** table;   //table points to a dynamic array. Each slot points to an entry, which points to the next entry, ...
  int size; //size of the array
public:
  hashTbl(int size);
  ~hashTbl();
  void put(entry* e); //add a new entry to the table
  entry* get(const string& key) const; //look up a key
  entry remove(const string& key); //remove an entry
  entry** getTbl() const {return table;} //return the pointer to the table
  class underflow //exception class - used when key wasn't found
  {
    string message;
  public:
    underflow(const string& mes) { message = mes; }
    string getMessage() { return message; }
  };
};

//constructor
//s is the size of the table
hashTbl::hashTbl(int s)
{
  //set private member size
  size = s;
  //make a dynamic array that has s slots
  table = new entry*[s];
  //put NULL in each slot of the array. Remember Each slot contains a pointer to an entry.
  for(int i = 0; i < s; i++){
    table[i] = NULL;
  }
}

//destructor
hashTbl::~hashTbl()
{
  //you need to destroy everything created using new.
  //destroy all the entries belong to each slot of the table
  //don't forget to destroy the dynamic array
  for(int i = 0; i < size; i++) {
    delete table[i];
  }
  delete[] table;
}

//insert an entry to the table
//e is a pointer to an entry
void hashTbl::put(entry* e)
{
  string key = e->getID();
  int index = (hashNum(key)) % (size);
  e->next = table[index];
  table[index] = e;
}

//look up key and return the pointer to it. Assume keys are unique.
entry* hashTbl::get(const string& key) const
{
  //look for key in the linked list. Return the pointer to the entry with key.
  //After traversed the list, if key wan't found, throw exception just like above where the slot was empty.
  int index = hashNum(key) % size;
  if(table[index] == NULL) throw underflow(key);
  entry* cur = table[index];
  while(cur) {
    if(cur->getID() == key) return cur;
    cur = cur->next;
  }
  throw underflow(key);
}

//remove the entry with key. Assume keys are unique.
entry hashTbl::remove(const string& key)
{

 int index = hashNum(key) % size;

 //slot empty
 if(table[index] == NULL) throw underflow(key);

 //entrys in first slot
 if(table[index]->getID() == key) {
   entry* temp = table[index];
   table[index] = table[index]->next;
   return *temp;
 }

 //go through "list"
 entry* prev = table[index];
 entry* cur = prev->next;

 while(cur) {
  if(cur->getID() == key) {
    prev->next = cur->next;
    return *cur;
  }
  cur = cur->next;
  prev = prev->next;
 }
 throw underflow(key);
}

//well known hash function called djb2
//http://www.cse.yorku.ca/~oz/hash.html
//For explanation of bit shifting, http://www.cplusplus.com/forum/beginner/95670/
//unsigned for positive numbers or zero only. long takes up 8 bytes (8 bytes * 8 bits = 64 bits). The range in decimal is 0 through 2^64 - 1(18446744073709551615)
unsigned long hashNum(const string& key)
{
  const char* cstr = key.c_str(); //converting C++ string to c-string. A c-string is a character array that is terminated by a '\0' (NULL terminator).

  unsigned long hash = 5381;
  int c;
  while (c = *cstr++) //checking each character until it reaches '\0'. When it reaches '\0', c gets the ascii number of '\0', which is 0. 0 means false -> getting out of while.
    {
      hash = ((hash << 5) + hash) + c;//hash * 33 + c;
    }
  return hash;
}

void showInfo(const entry& e);
void showTable(const int count[], const hashTbl& students);

const int SIZE = 1009; //For closed addressing, you don't need to worry about load factor.
                       //The table size still should be at least the number of items and also a prime number.
                       //There are 1000 people in the input file.
int main()
{
  //make a hash table object called students with SIZE slots
  hashTbl students(SIZE);


  int count[SIZE] = {0}; //set all slots to 0. Used to see count in each index

  ifstream fin;
  fin.open("hash.in");
  string id;
  string name;
  int age;
  double gpa;

  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      return 0;
    }

  //adding entries from the input file
  fin >> id >> name >> age >> gpa;
  while(fin)
    {
      count[hashNum(id)%SIZE]++;//trying to see how many entries go into each slot
      students.put(new entry(id, name, age, gpa));
      fin >> id >> name >> age >> gpa;
    }

  //show the statistic about the table
  showTable(count, students);

  //put entries into the table
  //students.put(new entry("T1234567891", "Tom", 23, 4.0));
  //students.put(new entry("F5432112345", "Fred", 45, 3.5));
  //students.put(new entry("L1357915987", "Linsey", 48, 2.0));

  //searches and returns students in table without removing
  try
    {
      cout << "trying to search" << endl;
      showInfo(*(students.get("P1429911332")));//middle at index 377
      showInfo(*(students.get("Y1098431884"))); //first entry at index 377
      showInfo(*(students.get("V1025438181"))); //last entry at index 377
      showInfo(*(students.get("A1234567891"))); //probably doesn't exist
      //search for key and show their info
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be found" << endl;
    }

  //Try to remove a student from table
  try
    {
      cout << "trying to remove" << endl;
      showInfo((students.remove("P1429911332"))); //3rd entry at index 377
      showInfo((students.remove("V1025438181"))); //last entry(now 4th) at index 377
      showInfo((students.remove("Y1098431884"))); //first entry at index 377
      showInfo((students.remove("A1234567891"))); //probably it doesn't exist
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be removed" << endl;
    }

  return 0;
}

//Show the information about an entry
void showInfo(const entry& e)
{
  cout << e.getID() << " " << e.getName() << " " << e.getAge() << " " << e.getGPA() <<  endl;
}

//Show the statistic about the hash table
void showTable(const int count[], const hashTbl& students)
{
  //we want to know the highest, lowest and empty counts
  int lowest = 1001;
  int highest = -1;
  int empty = 0;
  int hi_i; //index of the highest count

  cout << "print table" << endl;
  for(int i = 0; i < SIZE; i++)
    {
      if(count[i] < lowest)
        lowest = count[i];
      if(count[i] > highest)
	{
	  highest = count[i];
	  hi_i = i;
	}
      if(count[i] == 0)
        empty++;

      cout << setw(3) << count[i];
      if((i+1)%50 == 0)//Show 50 numbers per line
        cout << endl;
    }
  cout << endl << endl << "lowest is " << lowest << " highest is " << highest << " empty is " << empty << endl;

  cout << "highest count is at " << hi_i << endl;
  //Show the entries at the index that has the highest count
  entry* p = students.getTbl()[hi_i];
  while(p != NULL)
    {
      showInfo(*p);
      p = p->getNext();
    }
  cout << endl;

}

