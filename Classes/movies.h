#ifndef MOVIES_H//header guards to prevent double declaration                            
#define MOVIES_H
#include <iostream>
#include "parent.h"

using namespace std;

class movie : public Parent {//gets and sets variables
 public: 
  movie();
  virtual ~movie();
  void print();
  char* getDirector();
  char* getRating();
  float getDuration();
 protected:
  char* director;
  char* rating;
  float duration;
};
#endif
