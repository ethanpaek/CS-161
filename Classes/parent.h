#ifndef PARENT_H //if not defined
#define PARENT_H //define
#include <iostream>

using namespace std;

class Parent {//to get and set variables
 public:
  Parent();
  virtual ~Parent();
  char* getTitle();
  char* getYear();
  int getType();
 protected:
  int type;
  char* year;
  char* title;
};

#endif
