/*Ethan Paek, September 19th, 2016 This is a program to check for a Palindrome. 
A Palindrome is a sentence/phrase that reads the same front and back. (Ex: taco cat)*/
#include <iostream>
#include <string.h>

using namespace std;

int main(){
  char input[81];
  char output[81];
  int j = 0;
  bool Palindrome = true;
  cout << "Welcome to Palindrome!" << endl;
  cout << "Please enter a fabulous sentence." << endl;
  cin.get(input, 81);
  for (int i = 0; i < 81; i++){/*takes out uppercase letters, 
				 punctuation, numbers, and spaces*/
    if (isalpha(input[i])){
      output[j] = tolower(input[i]);
      j++;
    }
    if (input[i+1] == '\0'){
      i=82;
      output[j] = '\0';
    }
  }
  for (int i = 0; i < j; i++){//checks if it's a Palindrome
    if (output[i] != output[j-1-i]){
      Palindrome = false;
    }
  }
  if (Palindrome == true){//if it's a Palindrome
    cout << "Palidrome. Yayyyyyy give yourself a pat on the back." << endl;
  }
  else {//if it isn't Palindrome
    cout << "Not a Palindrome. Nooooooo" << endl;
  }
  return 0;
}
