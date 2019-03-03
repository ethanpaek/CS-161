#include <iostream>
#include <cstring>
#include "Strings.h"

StringStack::StringStack(){
  header = NULL;
}

StringStack::~StringStack(){
  delete header;
}

char* StringStack::pop(){
  if(header != NULL){
    char* current = new char[50];
    strcpy(current, header->token);
    StringNode* newNode = header;
    header = header->next;
    delete newNode;
    return current;//return the current node
  }
}

void StringStack::push(char* token){
  StringNode* newNode = new StringNode();
  newNode->next = header;
  strcpy(newNode->token, token);
  header = newNode;//give the corresponding token a node
}

char* StringStack::peek(){//if it's NULL, have it stay that way; if not, then it's gotta be a token
  return header == NULL ? NULL : header->token;
}
