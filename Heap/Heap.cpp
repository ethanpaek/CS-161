#include <iostream>
#include <cmath>
#include "Heap.h"

using namespace std;

Heap::Heap(){
  nodeCount = 0;
  arraySize = 128;//for all the standard ASCII characters
  data = new int[arraySize];
  /*for(int i = 0; i < arraySize; i++){
    data[i] = 0;//set each node to 0
    }*/
}

Heap::~Heap(){
  delete[] data;
}

void Heap::insert(int insertKey){
  if(nodeCount < arraySize){//gotta match up the array size with the number of nodes
    data[nodeCount] = insertKey;
    bubbleUp(nodeCount);
    nodeCount++;
  }
  else{//will make array bigger if node count is bigger than array size
    int* newNodes = new int[2*arraySize];
    for(int i = 0; i < arraySize; i++){//sets all of the new nodes equal to the previous ones
      newNodes[i] = data[i];
    }
    for(int i = arraySize; i < 2*arraySize; i++){//expand the array to empty nodes
      newNodes[i] = 0;
    }
    int *temp = data;
    data = newNodes;
    delete[] temp;
    arraySize *= 2;
    insert(insertKey);//recursion until array size matches up
  }
}

int Heap::peek(){
  return data[0];
}

int Heap::pop(){
  int temp = data[0];
  data[0] = data[nodeCount-1];//keep the children aligned correctly if you remove the root
  data[nodeCount-1] = 0;
  nodeCount--;
  bubbleDown(0);
  return temp;
}

void Heap::print(){//Up to twice logarithmic in the distance between first and last
  int nodeIndex = ceil(log2(nodeCount + 1));//define the "level" of the nodes; ceil rounds digits up to nearest integer
  int index = 0;
  for(int i = 1; i <= nodeIndex; i++){
    for(int j = 0; j < pow(2, nodeIndex-i)-1; j++){//watch for spaces
      cout << ' ';
    }
    for(int n = 0; n < pow(2, i-1); n++){//the actual nodes (if there are any)
      if(data[index] != 0){
	cout << data[index++];
      }
      else{
	break;
      }
      for(int k = 0; k < pow(2, nodeIndex - i + 1) - 1; k++){//other spaces
	cout << ' ';
      }
    }
    cout << endl;
  }
}

bool Heap::checkHeap(){
  return data[0] == 0;
}

void Heap::bubbleUp(int i){
  int parent = i%2 == 1 ? (i-1)/2 : (i-2)/2;//defines the parent
  if(data[i] > data[parent]){
    int temp = data[parent];
    data[parent] = data[i];
    data[i] = temp;
    bubbleUp(parent);
  }
}

void Heap::bubbleDown(int i){
  if(data[i] < data[2*i+1] || data[i] < data[2*i+2]){
    int index = data[2*i+1] > data[2*i + 2] ? 2*i+1 : 2*i + 2;//defines which node it is
    int temp = data[i];
    data[i] = data[index];
    data[index] = temp;
    bubbleDown(index);
  }
}
