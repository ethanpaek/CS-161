#include "GraphCreator.hpp"
#include <iostream>
#include <cstring>

//stanford.io/2qNRb0T <-- super helpful website btw (thanks Stanford nerds!)
//bit.ly/2rinab8 <-- helpful for dijkstra's algorithm

using namespace std;

int checkCopy(vector<char*> &copy, const char* name);//checks for node copies
char* heapCopy(char* str);
void edgeCopy(vector<char*> &location, vector<char*> &origin);

Graph::Graph():infinity(numeric_limits<int>::max()){}//setting infinity to its limit

Graph::~Graph(){
    for(int i = 0; i < names.size(); i++){
        delete[] names[i];
        names[i] = 0;
    }
    for(int i = 0; i < matrix.size(); i++){
        delete matrix[i];
        matrix[i] = 0;
    }
}

bool Graph::addNode(const char* name){
  if(checkCopy(names, name) != -1){//if they're the same name, don't add it (using -1 to check since that is what all nodes are initialized to)
    return false;
  }
  names.push_back(strcpy(new char[strlen(name)+1], name));//adds the new node to graph
  for(int i = 0; i < matrix.size(); i++){//expanding the matrix
    matrix[i]->push_back(-1);
  }
  matrix.push_back(new vector<int>);//begin checking for vertex's edges
  for (int i = 0; i < matrix.size(); i++){//shouldn't have any edges... yet (sets them to zero)
    matrix[matrix.size()-1]->push_back(-1);
  }
  return true;
}

bool Graph::addEdge(const char* node1, const char* node2, int weight){
  int vertex1 = checkCopy(names, node1);
  int vertex2 = checkCopy(names, node2);
  if (vertex1 == -1 || vertex2 == -1){//if either node does not exist
    return false;
  }
  (*matrix[vertex1])[vertex2] = weight;
  return true;
}

bool Graph::deleteNode(char* name){
  int vertex = checkCopy(names, name);
  if(vertex == -1){//if it doesn't exist
    return false;
  }
  delete[] names[vertex];
  names.erase(names.begin() + vertex);
  for(int i = 0; i < matrix.size(); i++){//get rid of any attached edges fam
    matrix[i]->erase(matrix[i]->begin() + vertex);
  }
  delete matrix[vertex];//gotta take out the node's matrix row too
  matrix.erase(matrix.begin() + vertex);
  return true;
}

bool Graph::deleteEdge(char* node1, char* node2){
  int vertex1 = checkCopy(names, node1);
  int vertex2 = checkCopy(names, node2);
  if(vertex1 == -1 || vertex2 == -1 || (*matrix[vertex1])[vertex2] == -1){//if a node or the weight exists, it's false
    return false;
  }
  (*matrix[vertex1])[vertex2] = -1;//bye bye edge!
  return true;
}

int checkCopy(vector<char*> &copy, const char* index){
  for(int i = 0; i < copy.size(); i++){
    if(strcmp(copy[i], index) == 0){
      return i;
    }
  }
  return -1;
}

char* heapCopy(char* str){
  return strcpy(new char[strlen(str)+1], str);
}

void edgeCopy(vector<char*> &location, vector<char*> &origin){
  for(int i = 0; i < location.size(); i++){
    delete[] location[i];
  }
  location.clear();
  for(int i = 0; i < origin.size(); i++){
    location.push_back(heapCopy(origin[i]));
  }
}

void Graph::print(){
  int maxLength = 0;
  for(int i = 0; i < names.size(); i++){//organizing the matrix through char size
    int length = strlen(names[i]);
    if(length > maxLength){
      maxLength = length;
    }
  }
  for(int i = 0; i < maxLength + 1; i++){//these two "for" functions are for the first row in the table
    cout << ' ';
  }
  for(int i = 0; i < names.size(); i++){
    cout << names[i] << ' ';
  }
  cout << endl;
  for(int i = 0; i < matrix.size(); i++){//vertical row
    cout << names[i];
    for(int l = 0; l < maxLength - strlen(names[i]) + 1; l++){
      cout << ' ';
    }
    for(int j = 0; j < names.size(); j++){
      if((*matrix[i])[j] >= 0){
	cout << (*matrix[i])[j];//weight of edges
      }
      else{
	cout << 'X';//if there is no edge
      }
      for(int h = 0; h < strlen(names[i]); h++){
	cout << ' ';
      }
    }
    cout << endl;
  }
}

pair<vector<char*>, int> Graph::travellingSalesman(const char* node1, const char* node2){
  pair<vector<char*>, int> result;
  int vertex1 = checkCopy(names, node1);
  int vertex2 = checkCopy(names, node2);
  if (vertex1 == -1 || vertex2 == -1){//if either node does not exist
    result.second = -1;
    return result;
  }
  int passby[names.size()];//gotta keep trach of nodes we visit and don't visit
  vector<pair<vector<char*>, int> > nodes;
  for(int i = 0; i < names.size(); i++){
    passby[i] = true;
    nodes.push_back(pair<vector<char*>, int>());
    nodes[nodes.size()-1].second = infinity;//if we haven't visited, assume they're an infinite distance away
  }
  //starting point has distance of 0
  passby[vertex1] = false;
  nodes[vertex1].second = 0;
  nodes[vertex1].first.push_back(heapCopy(names[vertex1]));
  int current = vertex1;
  while(true){
    for(int i = 0; i < names.size(); i++){
      if((*matrix[current])[i] != -1 && passby[i]){
	int distance = nodes[current].second + (*matrix[current])[i];
	if(distance < nodes[i].second){
	  nodes[i].second = distance;
	  edgeCopy(nodes[i].first, nodes[current].first);
	  nodes[i].first.push_back(heapCopy(names[i]));
	}
      }
    }
    passby[current] = false;
    if(passby[vertex2] == false){//gotta deallocate everything except for what's returned
      for(int i = 0; i < names.size(); i++){
	if(i != vertex2){
	  for(int j = 0; j < nodes[i].first.size(); j++){
	    delete[] (nodes[i].first)[j];
	  }
	}
      }
      return nodes[vertex2];
    }
    bool noPath = true;
    for(int i = 0; i < names.size(); i++){
      if(passby[i] && nodes[i].second != infinity){//if there is a path between two nodes
	noPath = false;
	break;
      }
    }
    if(noPath){//more deallocation
      for(int i = 0; i < names.size(); i++){
	for(int j = 0; j < nodes[i].first.size(); j++){
	  delete[] (nodes[i].first)[j];
	}
      }
      return nodes[vertex2];
    }
    int smallest = infinity;
    for(int i = 0; i < names.size(); i++){
      if(passby[i] && nodes[i].second < smallest){
	smallest = nodes[i].second;
	current = i;
      }
    }
  }
}

void Graph::printPath(const char* node1, const char* node2){
  pair<vector<char*>, int> result = travellingSalesman(node1, node2);
  if(result.second == -1){//if one of the nodes does not exist
    cout << "Couldn't find one of those nodes fam." << endl;
    return;
  }
  if(result.second == infinity){
    cout << "That path doesn't exist fam." << endl;
    return;
  }
  cout << "Path: " << result.first[0];
  delete[] result.first[0];
  for(int i = 1; i < result.first.size(); i++){
    cout << "->" << result.first[i];
    delete[] result.first[i];
  }
  cout << ";" << endl;
  cout << "Travelling Salesman result: " << result.second << endl;
}
