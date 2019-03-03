//Ethan Paek; March 10th, 2017; Program creates an expression tree internally. It will then print out the expression in infix, prefix, or postfix, depending on what the user wants.
#include <iostream>
#include <cstring>
#include "Stack.h"
#include "Strings.h"

using namespace std;

struct BinaryNode{
  char* token;
  BinaryNode *left;
  BinaryNode *right;
};

//the reason for multiple prec and checkOperator methods is because we have to dereference the pointers
int prec(char operation);
int prec(char* operation);
int prec(BinaryNode* newNode);
bool checkOperator(char token);
bool checkOperator(char *token);
bool checkOperator(BinaryNode* newNode);
bool checkLeft(char operation);
char* getOutput(char *infix);
void Infix(BinaryNode* root);
void Prefix(BinaryNode* root);
void Postfix(BinaryNode* root);
void deleteTree(BinaryNode* root);
BinaryNode* Tree(StringStack &calculation);

int main(){
  cout << "Welcome to the Expression Tree!" << endl;
  cout << "Please enter your expression in infix notation" << endl;
  bool running = true;
  while (running == true){
    char input[100];
    cin.get(input, 100);
    cin.ignore();
    if (!strcmp(input, "quit")){//quitting the program
      running = false;
    }
    char* postfix = getOutput(input);
    StringStack stack;
    int i = 0;
    while(postfix[i]){//basically shunting yard
      if(postfix[i] == ' '){//if it's a space, add it and continue
	i++;
	continue;
      }
      else if(isdigit(postfix[i])){//if it's a digit, match it with the output and push it to the stack
	char key[10];
	int j = 0;
	while(isdigit(postfix[i])){
	  key[j++] = postfix[i++];
	}
	key[j++] = '\0';
	stack.push(key);
      }
      else{//should only leave the operators left...
	char operation[2] = {postfix[i++], '\0'};
	stack.push(operation);
      }
    }
    delete[] postfix;//preserve the memory allocated
    cout << "Would you like to print out an expression with infix, prefix, or postfix? (infix, prefix, postfix, or quit)" << endl;
    BinaryNode* leaf = Tree(stack);
    cin.get(input, 100);
    cin.ignore();
    /*for(int i = 0; input[i]; i++){
      input[i] = tolower(input[i]);
      }*/
    if (!strcmp(input, "infix")){//when you type infix, run the infix method
      Infix(leaf);
      cout << endl;
      running = false;
    }
    else if (!strcmp(input, "prefix")){//when you type in prefix, run the prefix method
      Prefix(leaf);
      cout << endl;
      running = false;
    }
    else if (!strcmp(input, "postfix")){//when you type in postfix, run the postfix method
      Postfix(leaf);
      cout << endl;
      running = false;
    }
    else if (!strcmp(input, "quit")){//quitting the program
      running = false;
    }
    else {//if none of the commands match up
      cout << "Invalid command. Try again por favor" << endl;
    }
    deleteTree(leaf);
  }
}

void deleteTree(BinaryNode* root){//go through all of the branches until tree is fully deleted
  if(root != 0){
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

char* getOutput(char *infix){//implements the SYA (Shunting Yard Algorithm)
  Stack stack;
  char* postfix = new char[((strlen(infix) + 1)*3)];
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
  while(stack.peek()){//gotta free the pointer
    postfix[indexOutput++] = stack.pop();
    postfix[indexOutput++] = ' ';
  }
  postfix[indexOutput-1] = 0;
  return postfix;
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

int prec(char* token){
  return prec(*token);
}

int prec(BinaryNode* newNode){
  return prec(newNode->token);
}

bool checkOperator(char token){//checks for the five operators in equation
  if(token == '+' || token == '-' || token == '*' || token == '/' || token == '^'){
    return true;
  }
  else{
    return false;
  }
}

bool checkOperator(BinaryNode* newNode){
  return checkOperator(newNode->token);
}

bool checkOperator(char* token){
  return checkOperator(*token);
}

bool checkLeft(char operation){//checks for the karat (left-associative)
  return operation != '^';
}

void Infix(BinaryNode* root){//print the expression in infix
  if(checkOperator(root->token)){
    Infix(root->left);
    cout << root->token << ' ';
    Infix(root->right);
  }
  else{
    cout << root->token << ' ';
  }
}

void Prefix(BinaryNode* root){//print the expression in prefix 
  if(checkOperator(root->token)){
    cout << root->token << ' ';
    Prefix(root->left);
    Prefix(root->right);
  }
  else{
    cout << root->token << ' ';
  }
}

void Postfix(BinaryNode* root){//print the expression in postfix
  if(checkOperator(root->token)){
    Postfix(root->left);
    Postfix(root->right);
    cout << root->token << ' ';
  }
  else{
    cout << root->token << ' ';
  }
}

 BinaryNode* Tree(StringStack &calculation){//method uses recursion by looking at pointer of the root and constructs branches until tree is fully aligned
   if(checkOperator(calculation.peek())){
     BinaryNode* current = new BinaryNode();
     current->token = calculation.pop();
     current->right = Tree(calculation);
     current->left = Tree(calculation);
     return current;
   }
   else{
     BinaryNode* current = new BinaryNode();
     current->token = calculation.pop();
     return current;
   }
 }

//5 + ((1 + 2) * 4) - 3 should turn into -> 5 1 2 + 4 * + 3 −

/*example: infix should look something like this: 8 * 3 + 3
     +
  *    3   
8  3
*/
