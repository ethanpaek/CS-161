#include "stack.h"

using namespace std;

Stack::Stack(){//constructor
  header = NULL;
}

Stack::~Stack(){//deconstructor
  delete header;
}

void Stack::push(char token){//push the input token to output
  Node* current = new Node();
  current->next = header;
  current->token = token;
  header = current;
}

char Stack::pop(){//pop off the token on output and place it on the stack
  if(header != NULL){
    char temp = header->token;
    Node* top = header;
    header = header->next;
    delete top;
    return temp;
  }
}

char Stack::peek(){//simply look at the top token of the stack but don't do anything with it
  return header == NULL ? '\0' : header->token;//if the header is NULL, return a NULL character, else point the header towards the token
}
