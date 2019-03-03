//Ethan Paek, January 18th, 2017; this is a program for nodes to organize themselves in alinkedlist for a student directory                                                       
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"

 using namespace std;

void addStudent(Node* header, Student* newInfo);//adds students to the list
void printStudent(Node* header);//prints students from the list
void deleteStudent(Node* current, Node* previous, int inputID);//deletes students from the list
void averageGPA(Node* header);//averages all of the GPAs

int main(){
  Node* header = new Node(NULL);
  cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
  bool running = true;
  while(running == true){
    char input[50];
    cin.get(input,50);
    cin.ignore();
    if(!strcmp(input, "ADD")){//use the add function
      addStudent(header, new Student);
      cout << "Student successfully added! You're fantastic!" << endl;
      cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    }
    else if(!strcmp(input, "PRINT")){//use the print function
      printStudent(header->getNext());
      cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    }
    else if(!strcmp(input, "DELETE")){//use the delete function
      cout << "Enter the ID of the student you want to delete por favor." << endl;
      int inputID;
      cin >> inputID;
      cin.ignore();
      deleteStudent(header, NULL, inputID);
      cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    }
    else if(!strcmp(input, "AVERAGE")){//use the average function
      averageGPA(header->getNext());
      cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    }
    else if(!strcmp(input, "QUIT")){//quit the program
      running = false;
    }
    else{
      cout << "Invalid command! Try again por favor." << endl;
      cout << "Type in ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    }
  }
}

void addStudent(Node* header, Student* newInfo){//works
  /*Node* current = header;
  if (current->getNext()){
    current = current->getNext();
  }
  current->setNext(new Node(new Student));*/
  if (!header->getNext()){
    header->setNext(new Node(newInfo));
  }
  else if(header->getNext()->getStudent()->getID() > newInfo->getID()){
    Node* current = header->getNext();
    header->setNext(new Node(newInfo)); //create the new student and put them on the list
    header->getNext()->setNext(current);
  }
  else{
    addStudent(header->getNext(),newInfo);
  }
}

void printStudent(Node* header){
  if(!header){
    return;
  }
  header->getStudent()->returnValues();
  if (header->getNext()){
    printStudent(header->getNext());
  }
}

void deleteStudent(Node* current, Node* previous, int inputID){
  //Node* current = header;
  //Node* previous;
  if(current->getStudent() != NULL && current->getStudent()->getID() == inputID){
    previous->setNext(current->getNext());
    delete current;
    cout << "Student successfully deleted. You're a superstar!" << endl;
  }
  else if(current->getNext()){
    deleteStudent(current->getNext(), current, inputID);
  }
  else{
    cout << "Student does not exist! Try again por favor." << endl; 
  }
  /*Node* previous;
  Node* student;
  while (current->getNext()){
    previous = current;
    current = current->getNext();
    if(current->getStudent()->getID() == inputID){
      student = current;
      previous->setNext(current->getNext());
      delete student;
      current = previous;
      cout << "Student deleted! You're a superstar!" << endl;
    }
    else {
      cout << "Student does not exist. Try again por favor." << endl;
    }
    }*/
}

void averageGPA(Node* header){
  int counter = 0;
  float totalGPA = 0;
  Node* current = header;
  cout << "Average GPA of all students:" << endl;
  while(current){
  //for(Node* current = header; current != NULL; current = current->getNext()){
    counter++;
    totalGPA += (current -> getStudent()) -> getGPA();
    current = current->getNext();
  }
  cout << setprecision(2) << fixed << (totalGPA/counter) << endl;
}
