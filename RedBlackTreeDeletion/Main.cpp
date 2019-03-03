//Ethan Oaek; May 4th, 2017; this is the complete code for a RBT (Red Black Tree)
#include <cstring>
#include <iostream>
#include <fstream>
#include "RBT.hpp"

using namespace std;

void addManual(RBT &rBT);
void addFile(RBT &rBT);
void addToTree(RBT &rBT, char *list);

int main(){
  cout << "Welcome to The Red Black Tree!" << endl;
  cout << "Would you like to enter your numbers manually or through a file? (manual or file)" << endl;
  cout << "Enter 'quit' to quit the program" << endl;
  bool running = true;
  while (running == true){
    RBT rBT;
    char input[10];
    cin.get(input, 10);//read in the input
    cin.ignore();
    if(!strcmp(input, "manual")){//manually entering each number
      addManual(rBT);
    }
    else if(!strcmp(input, "file")){
      addFile(rBT);
    }
    else if(!strcmp(input, "quit")){
      running = false;
    }
    else {
      cout << "Invalid command! Try again por favor." << endl;
    }

    while(running == true){
      cout << "Would you like to print out your numbers in descending order? \nOr maybe you want to add another number? \nOr maybe you want to check if there's a number in the tree? \nOr maybe you want to delete a number off of the tree? \nIdk it's up to you I guess. (print, add, find, delete, quit)" << endl;
      cin.get(input, 10);//read in the next input
      cin.ignore();
      if(!strcmp(input, "print")){//print out the beautiful tree
	rBT.print();//printing is a little off due to the addition of the words, but is still in the correct positions
      }
      else if (!strcmp(input, "add")){//add in one more number and update tree
	int token;
	cout << "Please enter your desired number" << endl;
	cin >> token;
	cin.ignore();
	rBT.insertion(token);
	cout << "Insertion was successful. Great job! You deserve a pat on the back." << endl;
	rBT.print();
      }
      else if (!strcmp(input, "find")){//check if a number exists in the tree
	int token;
	cout << "Please enter your desired number" << endl;
	cin >> token;
	cin.ignore();
	if (rBT.findNode(token)){
	  cout << "Radical! That number's in the tree fam!" << endl;
	}
	else {
	  cout << "That number ain't in the tree fam. Lo siento." << endl;
	}
      }
      else if (!strcmp(input, "delete")){//deleting and updating the tree AKA the hell method
	int token;
	cout << "Please enter your desired number" << endl;
	cin >> token;
	cin.ignore();
	if (rBT.deletion(token)){
	rBT.print();
	cout << "Deletion was successful. Great job! You deserve a pat on the back." << endl;
	}
	else {
	  cout << "That number ain't in the tree fam. Lo siento." << endl;
	}
      }
      else if (!strcmp(input, "quit")){//quits the program
	running = false;
      }
      else {//if the command is not found
	cout << "Invalid command. Try again por favor" << endl;
      }
      cout << "Press enter two times to continue" << endl;
      cin.ignore();
      cin.get();
    }
  }
}

void addToTree(RBT &rBT, char *list){//organizes the RBT by their respective index
  int index = 0;
  while(list[index]){
    if(isdigit(list[index])){
      int value = list[index] - '0';
      while(isdigit(list[++index])){
	value = 10*value + (list[index] - '0');
      }
      rBT.insertion(value);
    }
    else{
      index++;
    }
  }
}

void addManual(RBT &rBT){//reading in numbers from manual input
  char numbers[150];
  cout << "Enter the numbers, separated by commas and/or spaces:" << endl;
  cin.get(numbers, 150);
  cin.ignore();
  addToTree(rBT, numbers);
}

void addFile(RBT &rBT){//reading in numbers from a file
  char filename[50];
  cout << "Enter your file name por favor" << endl;
  cin >> filename;
  cin.ignore();
  ifstream stream(filename);
  if(stream.is_open()){
    char list[1000];
    stream.getline(list, 1000);
    stream.close();
    addToTree(rBT, list);
  }
  else{//if the filename does not exist
    cout << "Oh no! Your file created a virus!" << endl;
    cout << "Lol jk. It didn't work for some reason tho. Maybe try again" << endl;
  }
}

//Ex: 162, 161, 163, 999, 1, 3, 5, 78, 164
/*
                        162black
                 3red           164black
          1black    78black   163red   999red
                  5red   161red
*/
