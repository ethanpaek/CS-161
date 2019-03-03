#include <iostream>
#include "node.h"
#include <cstring>

using namespace std;

Node::Node(Student* student){
  info = student;
  next = NULL;
}

Node* Node::getNext(){
  return next;
}

Student* Node::getStudent(){
  return info;
}

void Node::setNext(Node* newValue){
  next = newValue;
}

void Node::push_back(Student* student){
  Node* currentNode;
  for(currentNode = this; currentNode->getNext() != NULL; currentNode = currentNode->getNext());
  currentNode->setNext(new Node(student));
}

Node* Node::end(){
  Node* currentNode;
  for(currentNode = this; currentNode->getNext() != NULL; currentNode = currentNode->getNext());
  return currentNode;
}

/*void Node::setValue(int newValue){//these two methods are part of G's example
  value = newValue;
}

int Node::getValue(){
  return value;
  }*/

Node::~Node() {
  delete &info;
  next = NULL;
}
