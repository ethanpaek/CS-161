//Ethan Paek, January 8th, 2017; this is a program for nodes to organize themselves in a linkedlist for a student directory
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

/*void add(int newValue);//G's example
void print(Node* next);

Node * head = NULL;*/

class Student{//this will only test the id number of a student since int is easy
private:
  //char* name;
  //float gpa;
  int id;
public:
  Student(int idNumber){
    id = idNumber;
  }
  int getID(){//returns the ID number
    return id;
  }
};

int main(){
  /*add(5);//part of G's example
  print(head);
  add(7);
  print(head);
  add(2);
  print(head);*/

  Student* student1 = new Student(1);
  Student* student2 = new Student(3);
  Student* student3 = new Student(4);

  Node* head = new Node(student1);
  head->push_back(student2);
  head->push_back(student3);
  cout << head->end()->getStudent()->getID() << endl;

  for(Node* currentNode = head; currentNode->getNext() != NULL; currentNode = currentNode->getNext()){
    cout << currentNode->getStudent()->getID() << endl;
  }
}

/*void add(int newValue){//part of G's example
  Node* current = head;
  if (current == NULL){
    head = new Node();
    head->setValue(newValue);
  }
  else{
    while (current -> getNext() != NULL){
      current = current -> getNext();
    }
    current->setNext(new Node());
    current->getNext()->setValue(newValue);
  }
}

void print(Node* next){
  if (next == head){
    cout << "list: " << endl;
  }
  if (next != NULL){
    cout << next->getValue() << " " << endl;
    print(next->getNext());
  }
  else{
    //do nothing
  }
  }*/
