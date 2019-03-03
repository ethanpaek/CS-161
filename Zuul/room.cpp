#include <iostream>
#include "item.h"
#include <cstring>
#include <vector>
#include <map>
#include "room.h"

using namespace std;

Room::Room(const char* roomInfo, vector<Room*>* list){
    description = strdup(roomInfo);
    list -> push_back(this);
    end = false;
}

Room::~Room(){
  delete description;
  for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++){
    delete *it;
  }
  exits.erase(exits.begin(), exits.end());
}

void Room::makeExit(const char* exitName, Room* exitRoom){
    exits[exitName] = exitRoom;
}

void Room::addItem(Item* item){
  items.push_back(item);
}

void Room::pickupItem(vector<Item*>* inventory, char* itemName){
  for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++){
    if (!strcmp((*it)->getName(), itemName)) {
      inventory->push_back(*it);
      items.erase(it);
      cout << "Picked up: " << itemName << endl;
      return;
    }
  }
  cout << itemName << " is not in the room. Try again por favor." << endl;
}

void Room::dropItem(vector<Item*>* inventory, char* itemName){
  for (vector<Item*>::iterator it = inventory->begin(); it != inventory->end(); it++){
    if (!strcmp((*it)->getName(), itemName)) {
      items.push_back(*it);
      inventory->erase(it);
      cout << "You have just dropped: " << itemName << endl;
      return;
    }
  }
  cout << "You do not have that item!" << endl;
}

void Room::setItem(){
  //bool itemsExist = false;
  for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {  
    cout << (*it)->getName() << endl;
    //itemsExist = true;
  }
}

void Room::setExit(){
  for(map<const char*, Room*>::iterator it = exits.begin(); it != exits.end(); it++){
    cout << (*it).first << endl;//(*it).first will give me the key value to the map
  }
}

void Room::setInfo(){
  cout << "You are in " << description << endl;
  cout << "On the ground lies: " << endl;
  setItem();
  cout << "There are also exits here: " << endl;
  setExit();
}

Room* Room::getExit(char* exitKey){
  map<const char*, Room*>::iterator it = exits.find(exitKey);
  if(it != exits.end()){
    return exits[exitKey];
  }
  else{
    return NULL;
  }
}
void Room::setEnd(){
  end = true;
}
bool Room::isEnd(){
  return end;
}
void Room::setLose(){
  lose = true;
}
bool Room::isLose(){
  return lose;
}
