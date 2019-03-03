#ifndef MUSIC_H//header guards to prevent double declaration
#define MUSIC_H
#include <iostream>
#include "parent.h"

using namespace std;

class music : public Parent{//gets and sets variables
 public:
  music();
  virtual ~music();
  char* getArtist();
  char* getPublisher();
  float getDuration();
 protected:
  char* artist;
  char* publisher;
  float duration;
};
#endif
