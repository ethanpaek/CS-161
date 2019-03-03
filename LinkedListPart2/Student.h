//this class defines all of the variables and methods for the student class
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <cstring>

class Student{
 private:
  char* firstname;
  char* lastname;
  float gpa;
  int id;
 public:
  Student();//gets all of the private variables, constructor
  ~Student();//destructor
  char* getFirstname();//returns the first name
  char* getLastname();//returns the last name
  float getGPA();//returns GPA
  int getID();//returns ID
  void returnValues();//print out the student's info
};

#endif
