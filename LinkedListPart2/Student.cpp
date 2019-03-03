//sets up all of the methods for the student class                                        
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Node.h"

using namespace std;

Student::Student(){
  firstname = new char[30];
  lastname = new char[30];
  cout << "What's the student's first name?" << endl;
  cin.get(firstname, 30);
  cin.ignore();
  cout << "What's the student's last name?" << endl;
  cin.get(lastname, 30);
  cin.ignore();
  cout << "What's his/her GPA?" << endl;
  cin >> gpa;
  cin.ignore();
  cout << "What's his/her student ID?" << endl;
  cin >> id;
  cin.ignore();
  //cout << "Name: " << firstname << " " << lastname << ", ID: " << id << ", GPA: " << setprecision(2) <<fixed << gpa << endl;
}

Student::~Student(){
  delete firstname;
  delete lastname;
}

/*char* Student::getFirstname(){
  return firstname;
}

char* Student::getLastname(){
  return lastname;
  }*/
float Student::getGPA(){
  return gpa;
}

int Student::getID(){
  return id;
}

void Student::returnValues(){
  cout << "Name: " << firstname << " " << lastname << ", GPA: " << setprecision(2) << fixed << gpa << ", ID: " << id << endl;
}
