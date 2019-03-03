#include <iostream>
#include "HashTable.hpp"

using namespace std;

HashTable::HashTable(){//allocate everything!
  size = 100;
  list = new Node*[100];
}

HashTable::~HashTable(){//deallocate everything!
  for(int i = 0; i < size; i++){
    Node* current = list[i];
    while(current){
      Node* temp = current;
      current = current->next;
      delete temp->data;
      delete temp;
    }
  }
  delete[] list;
}

int HashTable::hash(int id){
  return id % size;//returns the index value
}

void HashTable::getStudentInfo(Student* student){
  addStudent(student->firstname, student->lastname, student->id, student->gpa);
  delete student;
}

Student* HashTable::getStudent(int id){
  Node* current = list[hash(id)];
  while(true){
    if(current == NULL){//if there's no students, do nothing
      return 0;
    }
    else if (current->data->id == id){//if the student exists, return his/her data
      return current->data;
    }
    else{//keep going through the list if you can't find the id
      current = current->next;
    }
  }
}

void HashTable::print(){
  for(int i = 0; i < size; i++){//print out the hash table!
    Node* current = list[i];
    while(current != NULL){
      current->data->print();
      current = current->next;
    }
  }
}

void HashTable::addStudent(char* firstname, char* lastname, int id, float gpa){
  Node** current = &list[hash(id)];
  int count = 0;
  while(*current != NULL){//counting the collisions
    current = &(*current)->next;
    count++;
  }
  if(count > 2){//if it's three or more collisions, double the array size and move students into a new hash table
    size *= 2;
    Node** oldlist = list;
    list = new Node*[size];
    for(int i = 0; i < size/2; i++){
      Node* current = oldlist[i];
      while(current){
	getStudentInfo(current->data);
	Node* temp = current;
	current = current->next;
	delete temp;
      }
    }
    delete[] oldlist;
    addStudent(firstname, lastname, id, gpa);
  }
  else{
    *current = new Node(new Student(firstname, lastname, id, gpa));
  }
}

bool HashTable::deleteStudent(int id){
  Node** current = &list[hash(id)];
  while(*current != NULL){
    if((*current)->data->id == id){//if the input id is equal to a student's id, delete it
	Node* temp = *current;
	*current = (*current)->next;
	delete temp->data;
	delete temp;
	return true;
      }
      else{
	current = &((*current)->next);
      }
    }
    return false;
}

