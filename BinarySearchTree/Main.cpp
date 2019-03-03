#include <iostream>
#include <cstring>
#include <fstream>
#include "BinarySearch.h"

using namespace std;

void addToTree(BinarySearch &binarySearch, char *numbers);//adds numbers to the tree

int main(){
  cout << "Welcome to the Binary Search Tree!" << endl;
  cout << "Would you like to enter your numbers manually or through a file? (manual or file)" << endl;
  cout << "Enter 'quit' to quit the program" << endl;
  bool running = true;
  while (running == true){
    BinarySearch binarySearch;
    char input[10];
    cin.get(input, 10);//read in the input
    cin.ignore();
    if(!strcmp(input, "manual")){//manually entering each number
      cout << "Please enter your numbers, separated by spaces" << endl;
      char numbers[150];
      cin.get(numbers, 150);
      cin.ignore();
      addToTree(binarySearch, numbers);
    }
    else if(!strcmp(input, "file")){//using a file to enter numbers
      cout << "Please enter your file name:" << endl;
      char filename[40];
      cin.get(filename, 40);
      cin.ignore();
      ifstream stream(filename);
      if(stream.is_open()){//read in the numbers from file
	char numbers[1000];
	stream.getline(numbers, 1000);
	stream.close();
	addToTree(binarySearch, numbers);
      }
      else{//if file name is not found
	cout << "OH NO! Your file created a virus on the computer!" << endl;
	cout << "Lol jk. You probably just didn't input the name correctly." << endl;
	break;
      }
    }
    else if(!strcmp(input, "quit")){//quits the program
      running = false;
    }
    else {//if the command is not recognized
      cout << "OH NO! You crashed the system!" << endl;
      cout << "Lol jk. Invalid command. Try again por favor" << endl;
      break;
    }

    while (running == true){
      cout << "Would you like to print out your numbers in descending order? \nOr maybe you want to add another number? \nOr delete one? \nIdk it's up to you I guess. (print, add, delete, quit)" << endl;
      cin.get(input, 10);//read in the next input
      cin.ignore();
      if (!strcmp(input, "print")){//print out the beautiful tree
	binarySearch.print();
      }
      else if (!strcmp(input, "add")){//add in one more number and update tree
	int token;
	cout << "Please enter your desired number" << endl;
	cin >> token;
	cin.ignore();
	binarySearch.insert(token);
	cout << "Insertion was successful. Great job! You deserve a pat on the back." << endl;
	binarySearch.print();
      }
      else if (!strcmp(input, "delete")){//delete one number and update tree
	int token;
	cout << "Please enter your desired number" << endl;
	cin >> token;
	cin.ignore();
	if(binarySearch.deletion(token)){//if the number exists
	  cout << "Deletion was successful. Great job! You deserve a pat on the back." << endl;
	  binarySearch.print();
	}
	else{//if the number doesn't exist
	  cout << "Uhhhh I don't think that number exists. Sorry amigo." << endl;
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

void addToTree(BinarySearch &binarySearch, char *numbers){
  int index = 0;
  while(numbers[index]){//while there are numbers on the array
    if(isdigit(numbers[index])){
      int key = numbers[index] - '0';
      while(isdigit(numbers[++index])){
	key = 10*key + (numbers[index] - '0');
      }
      binarySearch.insert(key);
    }
    else{
      index++;
    }
  }
}

/*Ex: 500 4 672 673 90 1
         500
     4        672
   1  90         673
*/
