#ifndef HASHTABLE_HPP
#define HASTABLE_HPP
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

struct Student{
  Student(const char* newFirstname, const char* newLastname, int newID, float newGPA){
    firstname = strcpy(new char[strlen(newFirstname) + 1], newFirstname);
    lastname = strcpy(new char[strlen(newLastname) + 1], newLastname);
    id = newID;
    gpa = newGPA;
  }
  char* firstname;
  char* lastname;
  int id;
  float gpa;
  void print(){//prints out the student info with cstring
    cout << lastname << ", " << firstname << ", ID: " << id << ", GPA: ";
    cout << setprecision(2) << fixed << gpa << endl;
  }
  ~Student(){
    delete[] firstname;
    delete[] lastname;
  }
};

struct Node{
  Node(Student* data):data(data), next(0) {}
  ~Node() {}
  Student* data;
  Node* next;
};

class HashTable{
public:
  HashTable();//constuctor
  ~HashTable();//deconstructor
  Student* getStudent(int id);//retrieve the student's info
  void addStudent(char* firstname, char* lastname, int id, float gpa);//add in a new student with personal info
  bool deleteStudent(int id);//delete a student corresponding to the entered ID
  void print();//print out the student list
private:
  Node** list;//the actual list where the students are stored
  int size;//size of the array
  int hash(int id);//return the hash value
  void getStudentInfo(Student*);//retrieves the student info
};

#endif
