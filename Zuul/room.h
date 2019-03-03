#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include "item.h"

using namespace std;

struct cmp_string{//overloading operator() for map
  bool operator()(char const *a, char const *b) const{
    return strcmp(a,b) < 0;
  }
};

class Room{
 private:
  map<const char*, Room*, cmp_string> exits;
  vector<Item*> items;
  char* description;
  bool end;
  bool lose;
 public:
  Room(const char* roomInfo, vector<Room*>* list);
  ~Room();
  void addItem(Item* item);//set items in rooms
  void makeExit(const char* exitName, Room* exitRoom); //make the exits
  void setItem();//print out items in current room
  void setExit();//print possible exits in current room
  void setInfo();//print info about current room
  void pickupItem(vector<Item*>* inventory, char* itemName);//pickup item in room
  void dropItem(vector<Item*>* inventory, char* itemName);//drop item in room
  Room* getExit(char* exitKey);//to find the exits for each room
  bool isEnd();
  void setEnd();
  bool isLose();
  void setLose();
};

#endif
