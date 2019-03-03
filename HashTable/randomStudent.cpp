#include "randomStudent.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

RandomStudents::RandomStudents(const char* firstnameFile, const char* lastnameFile) : randomId(000001) {
  srand(time(0));//lol throw back to guessing game
  ifstream fileFirstnames;
  ifstream fileLastnames;
  fileFirstnames.open(firstnameFile);
  fileLastnames.open(lastnameFile);
  if(fileFirstnames.is_open()){
    while(!fileFirstnames.eof()){//go through the whole file
      char* current = new char[50];
      fileFirstnames.getline(current, 50);
      firstnames.push_back(current);
    }
  } 
  if(fileLastnames.is_open()){
    while(!fileLastnames.eof()){
      char* current = new char[50];
      fileLastnames.getline(current, 50);
      lastnames.push_back(current);
    }//files will always exist, so no need for else statments
  }
}

RandomStudents::~RandomStudents(){
  for(int i = 0; i < firstnames.size(); i++){
    delete firstnames[i];
  }
  for (int j = 0; j < lastnames.size(); j++){
    delete lastnames[j];
  }
}

char* RandomStudents::getFirstname(){
  return firstnames[rand() % firstnames.size()];
}

char* RandomStudents::getLastname(){
  return lastnames[rand() % lastnames.size()];
}

int RandomStudents::getID(){
  return randomId++;
}

float RandomStudents::getGPA(){
  float gpa = (rand() % 1000);
  gpa /= 100;
  while (gpa > 4){
    gpa--;
  }
  return gpa;
}
