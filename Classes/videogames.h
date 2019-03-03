#ifndef VIDEOGAMES_H//header guards to prevent double declaration 
#define VIDEOGAMES_H
#include <iostream>
#include "parent.h"

using namespace std;

class videogame : public Parent {//get and set variables
 public:
 videogame();
 virtual ~videogame();
 void print();
 char* getPublisher();
 char* getRating(); 
 protected:
 char* publisher;
 char* rating;
};
#endif
