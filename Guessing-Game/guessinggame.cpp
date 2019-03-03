//Guessing Game, Ethan Paek, September 13th, 2016. This is a Guessing Game.
#include <iostream>
#include <time.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(){
  srand(time(NULL));
  int randomNum = rand() %101;
  int count = 0;
  int guess = -1;
  bool play = true;
  char input[3];
  cout << "Welcome to the Guessing Game!" << endl;
  cout << "Guess a number between 0 and 100." << endl;
  while (play == true){
    cin >> guess;
    count++;
    if (guess < randomNum){ //if guess is too low
      cout << "Your guess was too low!" << endl;
    }
    else if (guess > randomNum){ //if the number is too high
      cout << "Your guess was too high!" << endl;
    }
    else { //if the number is correct
      cout << "You guessed the correct number! You deserve a cookie." << endl;
      cout << "It took you:" << count << " tries." << endl;
      cout << "Do you want to play again?(y/n)" << endl;
      cin >> input;
      if (strcmp(input,"y")){ //ask to play again
	play = false;
      }   
      else {
	randomNum = rand() %101;
        guess = -1;
	count = 0;
        cout << "Welcome to the Guessing Game!" << endl;
        cout << "Guess a number between 0 and 100." << endl;
      }   
    }
  }
  return 0;
}
