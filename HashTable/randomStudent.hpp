#ifndef RANDOMSTUDENT_HPP
#define RANDOMSTUDENT_HPP
#include <vector>
#include <iostream>

using namespace std;

class RandomStudents{
public:
  RandomStudents(const char* firstnames, const char* lastnames);
  ~RandomStudents();
  char* getFirstname();//gets random first name from first name list
  char* getLastname();//gets random the last name from last name list
  int getID();//generates a random ID starting from 100000
  float getGPA();//generates a random GPA out of 4.00
private:
  vector<char*> firstnames;
  vector<char*> lastnames;
  int randomId;
};

#endif
