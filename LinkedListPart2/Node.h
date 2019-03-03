//Sanil Hattangadi, the header uses link list to go through the nodes and print out the students until the end is reached

#include <cstring>
#include <iostream>
#include "Student.h"

using namespace std;

class Student;

class Node{
 protected:
  Student* info;//keeps track of the students info
  Node* node;
 public:
  Node(Student* student); //create a new node
  ~Node(); //deleting the current node, including the corresponding student
  void setNext(Node* newnode); //set the next pointer to the corresponding node point
  Student* getStudent(); //get student pointer
  Node* getNext(); //get the next Node pointer
  void push_back(Student* student); //adds a new node to the end
  Node* end();
  //void erase();
};
