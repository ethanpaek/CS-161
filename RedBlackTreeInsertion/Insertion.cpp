#include <iostream>
#include <cstring>
#include <cmath>
#include "Insertion.hpp"

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
