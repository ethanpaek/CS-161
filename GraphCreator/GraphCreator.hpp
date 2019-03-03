#ifndef GRAPHCREATOR_HPP
#define GRAPHCREATOR_HPP
#include <iostream>
#include <vector>
#include <limits>
#include <utility>

using namespace std;

class Graph{
public:
  Graph();
  ~Graph();
  bool addNode(const char* name);//adds a node to the graph
  bool addEdge(const char* node1, const char* node2, int weight);//add an edge between two nodes with an input weight
  bool deleteNode(char* name);//removes a node from the graph along with any edges attached to it
  bool deleteEdge(char* node1, char* node2);//remove an edge and it's weight from the graph
  void print();//prints out the adjacency matrix
  void printPath(const char* node1, const char* node2);//prints out the travelling salesman
  void clear();
  //bool addBothEdges(const char* node1, const char* node2, int weight);
private:
  pair<vector<char*>, int> travellingSalesman(const char* node1, const char* node2);//travelling salesman that utilizes Dijksta's algorithm
  vector<vector<int>*> matrix;//the 2D adjacency matrix
  vector<char*> names;//node names
  const int infinity;//this one is pretty straight forward...
};

#endif
