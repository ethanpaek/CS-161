#include <iostream>
#include "music.h"

using namespace std;

music::music(){//gets artist, publisher, and duration
  type = 2;
  /*cout << "Who's the artist?" << endl;
  cin.get(artist,100);
  cin.ignore();
  cout << "Who's the publisher?" << endl;
  cin.get(publisher,100);
  cin.ignore();
  cout << "How many minutes long is it? (Ex: 3.25)" << endl;
  cin >> duration;
  cin.ignore();*/
  publisher = new char[32];
  artist = new char[32];
  cout << "Who's the publisher?" << endl;
  cin.get(publisher,32);
  cin.ignore();
  cout << "How long is the song?" << endl;
  cin >> duration;
  cin.ignore();
  cout << "Who sings the song?" << endl;
  cin.get(artist, 32);
  cin.ignore();
}
char* music::getArtist(){//returns artist
  return artist;
}
char* music::getPublisher(){//returns publisher
  return publisher;
}
float music::getDuration(){//returns duration
  return duration;
}
music::~music(){
  delete artist;
  delete publisher;
}
