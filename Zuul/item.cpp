#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

Item::Item(const char* someName){
  name = strdup(someName);
}

Item::~Item(){
  delete name;
}

char* Item::getName(){
  return name;
}

