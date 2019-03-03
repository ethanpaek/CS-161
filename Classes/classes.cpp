//Ethan Paek, November 15th, 2016; this is a database to sort and store different types of media such as: music, movies, and videogames
#include <iostream>
#include <cstring>
#include <vector>
#include "parent.h"
#include "music.h"
#include "videogames.h"
#include "movies.h"

using namespace std;

void addItem(vector<Parent*>* list);
void searchItem(vector<Parent*>* list);
void deleteItem(vector<Parent*>* list);

int main() {
  vector<Parent*> list;
  char input[20];
  bool run = true;
  cout << "Please enter a command." << endl;
  cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
  while (run == true) {
    cin.get(input, 20);
    cin.ignore();
    if (!strcmp(input,"ADD")) {//when you type "ADD"
      addItem(& list);
    }
    else if (!strcmp(input,"SEARCH")) {//when you type "SEARCH"
      searchItem(& list);
    }
    else if (!strcmp(input,"DELETE")) {//when you type "DELETE"
      deleteItem(& list);
    }
    else if (!strcmp(input,"QUIT")) {//when you type "QUIT"
      run = false;
    }
    else {//if it's not one of the three commands
      cout << "Invalid command. Try again por favor. Gracias." << endl;
    }
  }
}

void searchItem(vector<Parent*>* list){//search for certain items in database 
    bool find = false;
    char search[100];
    cout << "Enter a title or year to search" << endl;
    cin.get(search,100);
    cin.ignore();
    for(vector<Parent*>::iterator it = list->begin(); it != list-> end(); it++){
      if(!strcmp((*it)->getTitle(),search) || !strcmp((*it)->getYear(),search)){//search by title or year
	find = true;
	Parent* parent = *it;
	cout << "Title: " << parent->getTitle() << endl;
	cout << "Year: " << parent->getYear() << endl;
	if (parent->getType() == 1){//checks in music
	  music* m = (music*)parent;
	  cout << "Publisher: " << m->getPublisher() << endl;
          cout << "Duration: " << m->getDuration() << endl;
          cout << "Artist: " << m->getArtist() << endl;
	  cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
	}
	else if (parent->getType() == 2){//checks in movies
	  movie* m = (movie*)parent;
	  cout << "Director: " << m->getDirector() << endl;
          cout << "Duration: " << m->getDuration() << endl;
          cout << "Rating: " << m->getRating() << endl;
	  cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
	}
	else if (parent->getType() == 3){//checks in videogames
	  videogame* v = (videogame*)parent;
	  cout << "Publisher: " << v->getPublisher() << endl;
          cout << "Rating: " << v->getRating() << endl;
	  cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
	}
      }
    }
    if (!find){//if there is no applicable title or year
      cout << "No item was found" << endl;
    }
  }
void addItem(vector<Parent*>*list){//add an item to the vector either a movie, music, or videogame
  char command[15];
  cout << "Enter what type of media you want to add to the directory: movie, music, or videogames." << endl;
  cin.get(command,15);
  cin.ignore();
  if (!strcmp(command, "movie")){
    movie* m= new movie();
    list -> push_back(m);
    cout << "Movie has been added!" << endl;
    cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
  }
  else if (!strcmp(command, "music")){
    music* c = new music();
    list -> push_back(c);
    cout << "Song has been added!" << endl;
    cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
  }
  else if (!strcmp(command, "videogames")){
    videogame* v = new videogame();
    list -> push_back(v);
    cout << "Videogame has been added!" << endl;
    cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
  }
  else{//if none of the commands were typed in                                          
    cout << "Invalid command. Smh" << endl;                                             
    cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;                            
  }
}

void deleteItem(vector<Parent*>*list){//go through array and delte anything with the same title
  char deletetitle[32];
  cout << "Enter the name of the media you wish to delete." << endl;
  cin.get(deletetitle,32);
  cin.ignore();
  cout << "Media has been successfully deleted. Good job. You're a star!." << endl;
  cout << "Type in: ADD, SEARCH, DELETE, or QUIT" << endl;
  for (vector<Parent*>::iterator it =(*list).begin(); it !=(*list).end(); ++it){
    if (0 == strcmp((*it)->getTitle(), deletetitle)){
      // cout << deletetitle << endl;
      Parent* parent = *it;
      if (parent->getType() == 1){
	movie* m = (movie*)parent;
	delete m;
      }
      if (parent->getType() == 2){
	music* m = (music*)parent;
	delete m;
      }
      if (parent->getType() == 3){
	videogame* v = (videogame*)parent;
	delete v;
      }   
      (*list).erase(it);
      break;
    }
  }
}
