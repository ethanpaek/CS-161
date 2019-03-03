//tree's gotta hold cstrings too!
#ifndef STRINGS_H
#define STRINGS_H
#include <iostream>

struct StringNode{
  char token[50];//using arrays for the tree
  StringNode* next;
};

class StringStack{
 public:
  StringStack();//basic constructor
  ~StringStack();//deconstructor
  char* pop();//pop method
  void push(char* token);//push method
  char* peek();//peek method
 private:
  StringNode* header;
};

#endif
