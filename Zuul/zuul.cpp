//Ethan Paek, November 29th, 2016; this is my code for a game called, "Zuul"
#include <iostream>
#include <cstring>
#include <vector>
#include "room.h"
#include "item.h"

using namespace std;

bool firstWordCmp(char* a, const char* b);
//void checkItems();

void Rooms(vector<Room*>* list){//print all the rooms here as pointers
  Room* mysteriousroom = new Room("awake and find yourself in a dark and mysterious room", list);
  Room* theatre = new Room("in a dusty lecture theatre", list);
  Room* pub = new Room("in a pub, with cobwebs everywhere", list);
  Room *lab = new Room("in a science lab. There are broken beakers and flasks everywhere", list);
  Room* office = new Room("in a dark closet... Tom Cruise is in the corner", list);
  Room* trophyroom = new Room("in a trophy room. There are multiple shining torphies scattered on shelves", list);
  Room* pool = new Room("on a pool deck, but the pool in the middle of the room is empty", list);
  Room* cozyroom = new Room("in a cozy room with a fire blazing next to a few leather seats", list);
  Room* gym = new Room("in a dark gym with a light flickering above. Suddenly, countless dodgeballs are thrown at you. \nYou die not knowing how you even ended up here....", list);
  Room* cellar = new Room("in a wine cellar with endless racks of wine that looks to have aged for decades from all the dust", list);
  Room* dungeon = new Room("in a large dungeon with dozens of empty jail cells. There appears to be an amethyst in one of them...", list);
  Room* arsenal = new Room("in an arsenal with limitless weapons and treasures", list);
  Room* onetwenty = new Room("in 1-20 - the best room in the world. A Russian man named Danila Fedorin stands before you, \nwho is known to read the past and future. \nYou ask him how to return home...", list);
  Room* storage = new Room("in a storage room with organized, empty shelves", list);
  Room* closet = new Room("in a small closet... There appears to be a mysterious door ahead...", list);

  //all of the exits for the rooms
  mysteriousroom->makeExit("east", theatre);
  mysteriousroom->makeExit("south", lab);
  mysteriousroom->makeExit("west", pub);
  mysteriousroom->makeExit("north", trophyroom);
        
  gym->makeExit("west", theatre);
        
  cellar->makeExit("east", pub);
  cellar->makeExit("north", dungeon);
        
  dungeon->makeExit("south", cellar);
        
  storage->makeExit("west", pool);
  storage->makeExit("north", office);
        
  closet->makeExit("north", onetwenty);
  closet->makeExit("south", trophyroom);
        
  onetwenty->makeExit("south", closet);

  theatre->makeExit("west", mysteriousroom);
  theatre->makeExit("east", gym);
  theatre->makeExit("south", office);

  pub->makeExit("east", mysteriousroom);
  pub->makeExit("west", cellar);

  lab->makeExit("north", mysteriousroom);
  lab->makeExit("east", office);
  lab->makeExit("south", pool);
        
  pool->makeExit("east", storage);
  pool->makeExit("north", lab);
  pool->makeExit("south", cozyroom);
        
  cozyroom->makeExit("north", pool);
  cozyroom->makeExit("south", arsenal);
        
  arsenal->makeExit("north", cozyroom);

  office->makeExit("west", lab);
  office->makeExit("north", theatre);
  office->makeExit("south", storage);
        
  trophyroom->makeExit("south", mysteriousroom);
  trophyroom->makeExit("north", closet);

  Item* diamond = new Item ("diamond");
  Item* emerald = new Item ("emerald");
  Item* amethyst = new Item ("amethyst");
  Item* sapphire = new Item ("sapphire");
  Item* ruby = new Item ("ruby");

  closet->addItem(diamond);
  theatre->addItem(emerald);
  dungeon->addItem(amethyst);
  cozyroom->addItem(sapphire);
  arsenal->addItem(ruby);

  onetwenty->setEnd();
  gym->setLose();
}

int main() {
  vector<Room*> list;
  vector<Item*> inventory;
  bool run = true;
  char input[50];
  Room* currentRoom;

  cout << "Please enter a command." << endl;
  cout << "Type in: go (exit name), inventory, get, drop, or quit" << endl;
  cout << "At anytime, type in 'help' for help" << endl;
  Rooms(&list);
  cout << "**********************" << endl;
  currentRoom = *list.begin();
  currentRoom->setInfo();

  while (run == true) {
    cin.get(input, 50);
    if (firstWordCmp(input, "go")){//when you type "go"
      Room* newRoom = currentRoom->getExit(input + 3);
      if (newRoom) {
	currentRoom = newRoom;
	currentRoom->setInfo();
	cout << "**********************" << endl;
	if (currentRoom->isEnd()){
	  cout << "Congrats! You have reached the best room in the world!!" << endl;
	  cout << "Give yourself a pat on the back because you have just won the game of Zuul." << endl; 
	  run = false;
	}
	else if (currentRoom->isLose()){
	  cout << "You have lost the game of Zuul. Maybe you should try again." << endl;
	  run = false;
	}
      }
    }
    else if (firstWordCmp(input, "help")){
      cout << "Type in: go (exit name), inventory, get, drop, or quit" << endl;
    }
    else if (firstWordCmp(input, "inventory")){//when you type "inventory"
      cout << "You have: " << endl;
      for(vector<Item*>::iterator it = inventory.begin(); it != inventory.end(); it++){
	cout << (*it)->getName();
      }
    }
    else if (firstWordCmp(input, "get")){//when you type "get"
      currentRoom->pickupItem(&inventory, input + 4);
    }
    else if (firstWordCmp(input, "drop")){//when you type "drop"
      currentRoom->dropItem(&inventory, input + 5);
    }
    else if (firstWordCmp(input, "quit")){//when you type "quit"
      run = false;
    }
    else {
      cout << "Invalid command. Try again por favor. Gracias." << endl; 
    }
    cin.ignore();
  }
  for(vector<Item*>::iterator it = inventory.begin(); it != inventory.end(); it++){
    delete *it;
  }
  for(vector<Room*>::iterator it = list.begin(); it != list.end(); it++){
    delete *it;
  }
}

/*void checkItems(){
  int size = inventory.size();
  if (size == 5) {
    cout << "Congrats! You have acquired all five of the jewels.!" << endl;
    cout << "Give yourself a pat on the back because you have just won the game of Zuul." << endl;
    run = false;
  }
  }*/

 bool firstWordCmp(char* a, const char* b){
    for(int i = 0; i < strlen(b); i++){
      if (a[i] != b[i])
	return false;
    }
    return true;
  }
