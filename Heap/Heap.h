//similar to stack, organizes the nodes on the heap using a one-dimensional array
#ifndef HEAP_H
#define HEAP_H
#include <iostream>

class Heap{
 public:
  Heap();//constructor
  ~Heap();//deconstructor
  void insert(int insertKey);//inserts integer to the heap
  int pop();//print out numbers in descending order starting from the root
  int peek();//return the nodes
  void print();//prints out the array allocated on the heap
  bool checkHeap();//check if Heap is empty
 private:
  int nodeCount;//counts the nodes in the array
  int arraySize;//size of the actual array
  int *data;//nodes (basically)
  void bubbleUp(int i);//same thing with bubbleDown() but switches node with parent instead
  void bubbleDown(int i);//if the node is violating the min heap rule, meaning it is not smaller than both its children, switch it with its minimum child node. Continue doing this recursively until the node is no longer violating the heap rule.
};

#endif

//The left child of node in index i is: 2*i+1
//The right child of node in index i is: 2*i+2
//The parent of the node in index i is: (int)((i-1)/2)
