#include <iostream>
#include "movies.h"

using namespace std;

movie::movie(){//gets director, rating, and duration
  type = 1;
  director = new char[32];
  rating = new char[32];
  cout << "Who's the director?" << endl;
  cin.get(director,30);
  cin.ignore();
  cout << "How many minutes long is it?" << endl;
  cin >> duration;
  cin.ignore();
  cout << "What's the rating? PG? PG13?" << endl;
  cin.get(rating, 5);
  cin.ignore();
}
movie::~movie(){
  delete director;
  delete rating;
}
char* movie::getDirector(){//returns director
  return director;
}
char* movie::getRating(){//returns rating
  return rating;
}
float movie::getDuration(){//returns duration
  return duration;
}
void movie::print(){//print out the movie info
  cout << title << ", created in: " << year << endl;
  cout << "Director: " << director << endl;
  cout << "Rating: " << rating << endl; 
  cout << duration << " minutes" << endl;
}
