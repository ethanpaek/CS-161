//this method is for the stack process of the RPN
#ifndef STACK_H
#define STACK_H
#include <iostream>

struct Node{
  char token;
  Node* next;
};

class Stack {
 public:
  Stack();//basic constructor
  ~Stack();//deconstructor
  char pop();//pop method
  void push(char token);//push method
  char peek();//peek method
 private:
  Node* header;
};

#endif
