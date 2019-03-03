//Ethan Paek, February 14th, 2017; this is a RPN calculator with the shunting yard algorithm
#include <iostream>
#include <cstring>
#include "stack.h"

using namespace std;

int prec(char operation);
bool checkOperator(char token);
bool checkLeft(char operation);
char* getOutput(char *infix);

int main(){
  cout << "Welcome to the RPN calculator!" << endl;
  cout << "Would you like to calculate an equation? (yes or no)" << endl;
  bool running = true;
  while (running == true){
    char input[5];
    cin.get(input, 5);
    cin.ignore();
    if (!strcmp(input, "yes")){
      cout << "Type in your mathematical expression por favor" << endl;
      char equation[50];
      cin.get(equation, 50);
      cin.ignore();
      char* shunt = getOutput(equation);
      cout << "Postfix Notation: " << shunt << endl;
      delete[] shunt;
      running = false;
    }
    else if (!strcmp(input, "no")){
      running = false;
    }
    else {
      cout << "Invalid command. Try again por favor" << endl;
    }
  }
}

char* getOutput(char *infix){//implements the SYA (Shunting Yard Algorithm)
  Stack stack;
  char* postfix = new char[strlen(infix) + 1];
  int indexInput = 0; 
  int indexOutput = 0;
  while(infix[indexInput]){
    if(infix[indexInput] == ' '){//if there's a space, move on
      indexInput++;
      continue;
    }
    if(isdigit(infix[indexInput])){//check if it's a digit
      while(isdigit(infix[indexInput])){
	postfix[indexOutput++] = infix[indexInput++];
      }
      postfix[indexOutput++] = ' ';
    }
    else if(checkOperator(infix[indexInput])){//check if it's an operator
      while(checkOperator(stack.peek()) && ((checkLeft(infix[indexInput]) &&  prec(infix[indexInput]) <= prec(stack.peek()))|| (!checkLeft(infix[indexInput]) && prec(infix[indexInput]) < prec(stack.peek())))){//this is all checks for precedence and left-association
	postfix[indexOutput++] = stack.pop();
	postfix[indexOutput++] = ' ';
      }
      stack.push(infix[indexInput++]);//push to the output
    }
    else if(infix[indexInput] == '('){//check if it's a left parenthesis
      stack.push(infix[indexInput++]);
    }
    else if(infix[indexInput] == ')'){//check if it's a right parenthesis
      while(stack.peek() != '('){//this will only work if there was a left parenthesis first
	postfix[indexOutput++] = stack.pop();
	postfix[indexOutput++] = ' ';
	if(stack.peek() == 0){//if there was no left parenthesis
	  cout << "Smh you're missing a left parenthesis" << endl;
	  break;
	}
      }
      stack.pop();
      indexInput++;
    }
  }
  while(stack.peek()){
    postfix[indexOutput++] = stack.pop();
    postfix[indexOutput++] = ' ';
  }
  postfix[indexOutput-1] = 0;
  return postfix;//the result of the shunting yard algorithm! :D
}

int prec(char operation){//sets precedence for the operations
  int precedence[256] = {};
  precedence ['+'] = 1;
  precedence ['-'] = 1;
  precedence ['*'] = 2;
  precedence ['/'] = 2;
  precedence ['^'] = 3;
  return precedence[operation];
}

bool checkOperator(char token){//checks for the five operators in equation
  if(token == '+' || token == '-' || token == '*' || token == '/' || token == '^'){
    return true;
  }
  else{
    return false;
  }
}

bool checkLeft(char operation){//checks for the karat (left-associative)
  return operation != '^';
}

//5 + ((1 + 2) * 4) - 3 should turn into -> 5 1 2 + 4 * + 3 −
