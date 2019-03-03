//Ethan Paek; March 3rd, 2017; program creates a heap and orders numbers within the heap from greatest to least through a text file or manual input
#include <iostream>
#include <cstring>
#include <fstream>
#include "Heap.h"

//test array: [7 36 1 48 30 12 7 4 11 53 52 6 7 7 45]

using namespace std;

//example of how to input text (for my purpose lol):
/*string line;
ifstream myfile ("example.txt");
if (myfile.is_open()){
    while ( getline(myfile,line)){
        cout << line << '\n';
    }
    myfile.close();
  }
 else {
   cout << "Unable to open file"<< endl;
 }*/

void printArray(Heap &heap);
void addToHeap(Heap &heap, char *list);

int main(){
  cout << "Welcome to Heap!" << endl;
  cout << "Would you like to input your own numbers or a file? (input, file, or quit)" << endl;
  Heap heap;
  bool running = true;
  while (running == true){
    char input[10];
    cin.get(input, 10);
    cin.ignore();
    if (!strcmp(input, "input")){//if the user writes input, allow them to manually enter numbers seperated with spaces
      cout << "Please enter your desired array of quality numbers (please seperate each number by spaces)" << endl;
      char list[100];
      cin.get(list, 100);
      cin.ignore();
      addToHeap(heap, list);
    }
    else if (!strcmp(input, "file")){//read in a .txt file located the directory
      char fileInput[20];//using touch "file name"
      cout << "Enter your file name por favor" << endl;
      cin.get(fileInput, 20);
      cin.ignore();
      ifstream stream(fileInput);//uses the fstream library
      if(stream.is_open()){
	char list[1000];
	stream.getline(list, 1000);
	stream.close();
	addToHeap(heap, list);
      }
      else{
	cout << "Oh no! Your file created a virus!" << endl;//no it does not actually create a virus -_-
	cout << "Lol jk. It didn't work for some reason tho. Maybe try again" << endl;
	running = false;
	break;//quits the program if it doesn't correctly write the file
      }
    }
    else if (!strcmp(input, "quit")){//quits the program
      running = false;
      break;
    }
    else {//if the command doesn't match up with anything
      cout << "Invalid command. Try again por favor" << endl;
    }
    cout << "Would you like to print out your numbers in descending order?" << endl;
    cout << "Or would you like to print out the tree? (order, tree, or quit)" << endl;
    cin.get(input, 10);//read in the next input
    cin.ignore();
    if (!strcmp(input, "order")){//prints the array in descending order seperated by spaces
      printArray(heap);
    }
    else if (!strcmp(input, "tree")){//print out the beautiful binary tree
      heap.print();
    }
    else if (!strcmp(input, "quit")){//quit the program
      running = false;
      break;
    }
    else {//if the command doesn't match up with anything
      cout << "Invalid command. Try again por favor" << endl;
    }
    cout << "\nWould you like to configure a new heap? (yes or no)" << endl;
    cin.get(input, 10);
    cin.ignore();
    if (!strcmp(input, "yes")){//if you want to make a new heap, then it restarts
      cout << "Would you like to input your own numbers or a file? (input, file, or quit)" << endl;
    }
    else{//anything else will quit the program automatically
      running = false;
      break;
    }
  }
}

void printArray(Heap &heap){//print out the array by checking for numbers and adding spaces between each node
  cout << heap.pop();
  while(!heap.checkHeap()){
    cout << " " << heap.pop();
  }
}

void addToHeap(Heap &heap, char *list){//organizes the heap
  int index = 0;
  while(list[index]){
    if(isdigit(list[index])){
      int key = list[index] - '0';
      while(isdigit(list[++index])){
	key = 10*key + (list[index] - '0');
      }
      heap.insert(key);
    }
    else{
      index++;
    }
  }
}
