#include <iostream>
#include "videogames.h"

using namespace std;

videogame::videogame(){//get publisher and rating
  type = 3;
  publisher = new char[32];
  rating = new char [32];
  cout << "Who's the publisher?" << endl;
  cin.get(publisher,30);
  cin.ignore();
  cout << "What's the rating? E for everyone? M for mature?f?" << endl;
  cin.get(rating, 4);
  cin.ignore();
}
videogame::~videogame(){
  delete publisher;
  delete rating;
}
char* videogame::getPublisher(){//return publisher
  return publisher;
}
char* videogame::getRating(){//return rating
  return rating;
}
void videogame::print(){//print out videogame info
  cout << title << ", " << year << endl;
  cout << publisher << endl;
  cout << "Rated: " << rating << endl;
}
