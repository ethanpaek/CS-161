//adding, printing, and deleting nodes from the tree
#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

struct Node{
  int token;
  Node *left;
  Node *right;
Node(int newValue) : left(0), right(0){
  token = newValue;
}
};

class BinarySearch{
  public:
  BinarySearch();//constructor
  ~BinarySearch();//deconstructor
  void print();//print out the tree
  void insert(int key);//insert a node into the tree
  bool checkTree();//check if there's something in the tree
  bool deletion(int key);//remove a node from the tree and reorganize it
  private:
  Node* header;//node header
  void insertPrivate(Node* &parent, int key);//inserting a node for private method
  int returnNumLevels(Node* root, int index);//the "level" of the tree (root is 1st, its children is 2nd level, etc.)
  void populateArray(int *& array, int index, Node* node);//sets up nodes in an array
  Node** find(Node *& node, int key);//find a number that coordinates with a node in the tree
  void deleteNode(Node** current);//removing the node
};

#endif
