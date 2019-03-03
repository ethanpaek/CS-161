#ifndef INSERTION_H
#define INSERTION_H

#include <iostream>

struct Node{
  int token;
  Node* left;
  Node* right;
  Node* parent;
  bool black;
  Node(int newToken, bool newBlack = false) : left(0), right(0), parent(0){//constructor
    token = newToken;
    black = newBlack;
  }
  Node() : left(0), right(0), parent(0){//constructor for NULL nodes
    token = 0;
    black = true;
  }
  bool isZero(){//check for zero or NULL characters
    return left == 0 && right == 0;
  }
  bool isRed(){//it ain't black so it's red
    return !black;
  }
  void paintBlack(){//it's black
    black = true;
  }
  void paintRed(){//it's red
    black = false;
  }
  void addZeroLeafs(){//adding leafs for NULL nodes
    setLeft(new Node());
    setRight(new Node());
  }
  Node* uncle(){//returning a child's uncle
    Node* gparent = grandparent();
    if(gparent == NULL){//if the grandparent is NULL, then don't do anything
      return 0;
    }
    return gparent->left == parent ? gparent->right : gparent->left;
  }
  Node* grandparent(){//returning a child node's grandparent
    return parent == 0 ? 0 : parent->parent;
  }
  void setLeft(Node* node){//setting the left node
    left = node;
    if(node != NULL){
      node->parent = this;
    }
  }
  void setRight(Node* node){//setting the right node
    right = node;
    if(node != NULL){
      node->parent = this;
    }
  }
  bool isLeftChild(){//checking for left child
    return parent->left == this;
  }
  bool isRightChild(){//checking for right child
    return parent->right == this;
  }
  void deleteSubtrees(){//simply deleting the subtrees, if prompted
    if(left != 0){
      left->deleteSubtrees();
    }
    if(right != 0){
      right->deleteSubtrees();
    }
    delete left;
    delete right;
  }
  ~Node(){}
};

class RBT{
public:
  RBT();//constructor
  ~RBT();//deconstructor
  void insertion(int key);//inserting a number to the tree
  //bool deletion(int key); //for the next part of the project (eek)
  bool checkTree();//check if there's something in the tree
  void print();//print out the tree
private:
  Node* root;
  Node* insertInitial(Node * node, int key);//initial root
  void cases(Node* inserted);//the five cases for a RBT
  int returnNumLevels(Node* root, int level);//the "level" of the tree (root is 1st, its children is 2nd level, etc.)
  void populateArray(int *& array, int index, Node* node);//sets up nodes in an array
  //void deleteNode(Node** deleteNode);
  void leftRotation(Node* initialChild);//rotating left
  void rightRotation(Node* initialChild);//rotating right
  Node** parentPtrTo(Node* child);//private pointer to the child so that we can identify where the parent is
  //Node** find(Node *& node, int key);//find a number that coordinates with a node in the tree
};

#endif
