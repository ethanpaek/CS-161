#include <iostream>
#include <cstring>
#include <cmath>
#include "RBT.hpp"

using namespace std;

RBT::RBT(){
  root = new Node();
}

RBT::~RBT(){
  root->deleteSubtrees();
  delete root;
}

bool RBT::checkTree(){
  return root->isZero();
}

void RBT::insertion(int key){
  cases(insertInitial(root, key));
}

bool RBT::deletion(int key){
  Node* toDelete = find(root, key);
  if(toDelete == 0){//Node not found
    return false;
  }
  if(!toDelete->left->isZero() && !toDelete->right->isZero()){
    //If the node has two non-leaf children, copy its successor's value
    //onto it, then remove the successor.
    Node* successor = toDelete->right;//can't just delete the actual node like a linkedlist
    while(!successor->left->isZero()){
      successor = successor->left;
    }
    toDelete->token = successor->token;
    toDelete = successor;
  }
  deleteNode(toDelete);//delete the node now
  return true;
}

void RBT::deleteNode(Node* toDelete){//when a node has at most one non-leaf node
  if(toDelete->isRed()){
    //Can only occur if toDelete has two leaf nodes.
    toDelete->makeZero();
    return;
  }
  Node* child = toDelete->nonZeroChild();
  if(child->isRed()){//toRemove black, child red.
    replaceParent(child);
    child->paintBlack();
    return;
  }
  //Here toRemove is black with two leaves.
  toDelete->makeZero();
  rebalance(toDelete);
}

bool RBT::findNode(int key){
  return find(root, key) != 0;
}

void RBT::replaceParent(Node* child){
  Node* parent = child->parent;
  Node** childPtr = parentPtrTo(child);
  child->parent = child->grandparent();//after deletion, child's parent will be the grandparent
  (*parentPtrTo(parent)) = child;//parent's pointer is now the child's
  *childPtr = 0;
  parent->deleteSubtrees();
  delete parent;
}

void RBT::rebalance(Node* node){
  if(node->parent == NULL){//node is the root
    return;
  }
  Node* sibling = node->sibling();
  if(sibling->isRed()){//Then node's parent is black
    //Reverse colors of parent and sibling.
    node->parent->paintRed();
    sibling->paintBlack();
    //Rotate sibling into parent's place.
    if(node->isLeftChild()){
      leftRotation(sibling);
    }
    else{
      rightRotation(sibling);
    }
  }
  sibling = node->sibling();
  if(node->parent->black && sibling->black && sibling->left->black && sibling->right->black){
    sibling->paintRed();
    rebalance(node->parent);
    return;
  }
  if(node->parent->isRed() && sibling->black && sibling->left->black && sibling->right->black){
    sibling->paintRed();
    node->parent->paintBlack();
    return;
  }
  //sibling must be black.
  if(node->isLeftChild() && sibling->right->black){//Then sibling->left is red since sibling's both children aren't black
    //Exchange colors of sibling and its left child, then rotate right through sibling.
    sibling->left->paintBlack();
    sibling->paintRed();
    rightRotation(sibling->left);
  }
  else if(node->isRightChild() && sibling->left->black){//Then similarly, sibling->right is red.
    sibling->right->paintBlack();
    sibling->paintRed();
    leftRotation(sibling->right);
  }
  sibling = node->sibling();
  //Exchange colors of sibling and parent (parent can be either color but sibling is black):
  //P.S. this case sucks
  sibling->black = node->parent->black;
  node->parent->paintBlack();
  if(node->isLeftChild()){
    sibling->right->paintBlack();
    leftRotation(sibling);
  }
  else{//node is right child and sibling->left is red
    sibling->left->paintBlack();
    rightRotation(sibling);
  }
}

void RBT::print(){
  int nodeIndex = returnNumLevels(root, 0);
  int nodes[(int)(pow(2, nodeIndex)) - 1];//same as heap but with an array
  int* arrayPtr = nodes;
  memset(nodes, 0, sizeof(nodes));//allocate the memory
  populateArray(arrayPtr, 0, root);
  int index = 0;
  for(int l = 1; l <= nodeIndex; l++){//same as heap (from that Wiki page)
    for(int i = 0; i < pow(2, nodeIndex-l)-1; i++){//watch for spaces
      cout << ' ';
    }
    for(int n = 0; n < pow(2, l-1); n++){//the actual nodes (if there are any)
      if(nodes[index] > 0){
	cout << nodes[index] << "black";
      }
      else if(nodes[index] < 0){
	cout << -nodes[index] << "red";//reds are complete opposite of black which is why it's the negative nodes
      }
      else{
	cout << ' ';
      }
      index++;
      for(int i = 0; i < pow(2, nodeIndex - l+1) - 1; i++){//other spaces
	cout << ' ';
      }
    }
    cout << endl;
  }
}

Node* RBT::insertInitial(Node * child, int key){//first node is colored red
  //Assigns parent and child pointers. Returns pointer to inserted node.
  if(child->isZero()){
    child->token = key;
    child->paintRed();
    child->addZeroLeafs();
    return child;
  }
  if(key < child->token){
    return insertInitial(child->left, key);
  }
  else{
    return insertInitial(child->right, key);
  }
}

void RBT::cases(Node * inserted){//cases primarily follows the uncle and parent to determine the color and to accurately update the tree
  if(inserted->parent == 0){//root must be black
    inserted->paintBlack();
    return;
  }
  else if(inserted->parent->black){//if the parent is black, then don't do anything
    return;
  }
  else if(inserted->uncle()->isRed()){//if the inserted's parent and uncle are red
    inserted->parent->paintBlack();
    inserted->uncle()->paintBlack();
    inserted->grandparent()->paintRed();
    cases(inserted->grandparent());
    return;
  }
  if(inserted->isRightChild() && inserted->parent->isLeftChild()){
    /*Parent = red, uncle = black. Inserted is right child of parent,
    parent is left child of grandparent.
    Left rotation: move the inserted node into its parent's position:
               grandparent
        parent
               inserted
    
    */
    leftRotation(inserted);
    inserted = inserted->left;
  }
  else if(inserted->isLeftChild() && inserted->parent->isRightChild()){
    /*if the inserted is a left child and the parent is a right child to the grandparent
      Right rotation: move the inserted node into its parent's position
         grandparent
                  parent
          inserted
    */
    rightRotation(inserted);
    inserted = inserted->right;
  }//repaint and update the tree with rotations:
  inserted->grandparent()->paintRed();
  inserted->parent->paintBlack();
  if(inserted->isLeftChild()){//if it's a left child
    rightRotation(inserted->parent);
  }
  else{//if it's a right child
    leftRotation(inserted->parent);
  }
}

int RBT::returnNumLevels(Node* root, int level = 0){
  if(root == NULL){
    return level;
  }
  return max(returnNumLevels(root->left, level + 1), returnNumLevels(root->right, level + 1));
}

void RBT::populateArray(int *& array, int index, Node* node){
  if(node == NULL){
    return;
  }
  array[index] = node->black ? node->token : -node->token;//will return either a red or black node with their respective token value
  populateArray(array, index*2+1, node->left);//these will define the node's position
  populateArray(array, index*2+2, node->right);
}

void RBT::leftRotation(Node* initialChild){
  Node* initialParent = initialChild->parent;
  *parentPtrTo(initialParent) = initialChild;//referring the parent's pointer to the intial parent to preserve its value
  initialChild->parent = initialChild->grandparent();
  initialParent->setRight(initialChild->left);
  initialChild->setLeft(initialParent);
}

void RBT::rightRotation(Node* initialChild){
  Node* initialParent = initialChild->parent;
  *parentPtrTo(initialParent) = initialChild;
  initialChild->parent = initialChild->grandparent();
  initialParent->setLeft(initialChild->right);
  initialChild->setRight(initialParent);
}

Node** RBT::parentPtrTo(Node* child){
  Node** parentPtr;
  if(child->parent == NULL){//if there's no parent, then it's the root
    parentPtr = &root;
  }
  else if(child == child->parent->left){//parent is on the left
    parentPtr = &(child->parent->left);
  }
  else{
    parentPtr = &(child->parent->right);//parent is on the right
  }
  return parentPtr;
}

Node* RBT::find(Node * currentRoot, int key){
  if(currentRoot->isZero()){//Return null if no such node
    return 0;
  }
  if(currentRoot->token == key){
    return currentRoot;
  }
  else if(key > currentRoot->token){
    return find(currentRoot->right, key);
  }
  else{
    return find(currentRoot->left, key);
  }
}
