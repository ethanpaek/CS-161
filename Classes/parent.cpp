#include <iostream>
#include "parent.h"

using namespace std;

Parent::Parent(){//gets title and year
  title = new char[32];
  year = new char[32];
  cout << "What's the title?" << endl;
  cin.get(title,32);
  cin.ignore();
  cout << "What year was is made in?" << endl;
  cin.get(year,32);
  cin.ignore();
}
char* Parent::getTitle(){//returns title
  return title;
}
int Parent::getType(){//returns type of media
  return type;
}
char* Parent::getYear(){//returns year
  return year;
}
Parent::~Parent(){
  delete year;
  delete title;
}
