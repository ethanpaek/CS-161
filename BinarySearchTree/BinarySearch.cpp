#include <iostream>
#include <cstring>
#include <cmath>
#include "BinarySearch.h"

using namespace std;

BinarySearch::BinarySearch(){
  header = NULL;
}

BinarySearch::~BinarySearch(){
  delete header;
}

void BinarySearch::print(){//pretty much the heap alogrithm
  int numLevels = returnNumLevels(header, 0);
  int nodeNum[(int)(pow(2, numLevels)) - 1];
  int* arrayPointer = nodeNum;
  memset(nodeNum, 0, sizeof(nodeNum));//allocate the memory
  populateArray(arrayPointer, 0, header);
  int index = 0;
  for(int l = 1; l <= numLevels; l++){//outputting the initial spaces
    for(int i = 0; i < pow(2, numLevels-l)-1; i++){
      cout << ' ';
    }
    for(int n = 0; n < pow(2, l-1); n++){//outputting the nodes
      if(nodeNum[index] != 0){
	cout << nodeNum[index];
      }
      else{//outputting the spaces
	cout << ' ';
      }
      index++;//move to the next level
      for(int i=0; i < pow(2, numLevels - l + 1) - 1; i++){//other spaces
	cout << ' ';
      }
    }
    cout << endl;
  }
}

void BinarySearch::insert(int key){
  if(header == NULL){
    header = new Node(key);
    return;
  }
  insertPrivate(header, key);
}

bool BinarySearch::checkTree(){
  return header == NULL;
}

bool BinarySearch::deletion(int key){
  Node** current = find(header, key);
  if(current == NULL){//if there is no corresponding node
    return false;
  }
  else{
    deleteNode(current);
    return true;
  }
}

void BinarySearch::deleteNode(Node** current){
  if((*current)->left == NULL && (*current)->right == NULL){//if you reach a leaf
    delete *current;//delete that node and make it null/0
    *current = 0;
  }
  else if((*current)->left != 0 && (*current)->right != 0){//node with two branches
    Node** larger = &((*current)->right);//larger node by following the right branch
    while((*larger)->left != 0){
      larger = &((*larger)->left);
    }
    (*current)->token = (*larger)->token;
    deleteNode(larger);
  }
  else{//node with only one branch
    Node* child = (*current)->left == 0 ? (*current)->right : (*current)->left;//if left branch is null, point to the right branch. Otherwise, continue down the left one
    delete *current;
    *current = child;
  }
}

Node** BinarySearch::find(Node *& node, int key){//basically goes through the whole tree to find the desired value
  if(node == NULL){
    return 0;
  }
  else if(node->token == key){
    Node** pointer = &node;
    return pointer;
  }
  else if(node->token < key){
    return find(node->right, key);
  }
  else{
    return find(node->left, key);
  }
}

int BinarySearch::returnNumLevels(Node* root, int index = 0){//also from heap algorithm
  if(root == NULL){
    return index;
  }
  return max(returnNumLevels(root->left, index + 1), returnNumLevels(root->right, index + 1));//returns the largest index possible
}

void BinarySearch::populateArray(int *& array, int index, Node* node){
  if(node == NULL){//if the header is null
    return;
  }
  array[index] = node->token;
  populateArray(array, index*2+1, node->left);
  populateArray(array, index*2+2, node->right);
}

void BinarySearch::insertPrivate(Node *& parent, int key){
  if(parent == 0){//make a new node for the inserted value
    parent = new Node(key);
    return;
  }
  else if(key < parent->token){//if the inserted value is less than a parent node, move it down a left branch
    insertPrivate(parent->left, key);
  }
  else{//otherwise, it is bigger than the parent so move it down a right branch
    insertPrivate(parent->right, key);
  }
}
