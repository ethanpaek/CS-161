//Ethan Paek, May 26th, 2017; this is a program to create a graph with breadth first search
#include <iostream>
#include <cstring>
#include "GraphCreator.hpp"

using namespace std;

int main(){
  cout << "Welcome to the Graph Creator!" << endl;
  cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
  bool running = true;
  Graph graph;
  while (running == true){
    char input[25];
    cin.get(input, 25);
    cin.ignore();
    if(!strcmp(input, "addnode")){//adding a node
      char name[25];
      cout << "Enter your node name por favor." << endl;
      cin.get(name, 25);
      cin.ignore();
      if(graph.addNode(name)){//if the node is successfully added, great!
	cout << "Node successfully added! You deserve a cookie." << endl;
      }
      else{//if the node already exists, do not add it
	cout << "That node already exists fam. Try again." << endl;
      }
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "addedge")){//adding an edge to connect between two nodes
      char node1[25];
      char node2[25];
      int weight;
      cout << "Enter the name of your first node por favor." << endl;
      cin.get(node1, 25);
      cin.ignore();
      cout << "Enter the name of your second node por favor." << endl;
      cin.get(node2, 25);
      cin.ignore();
      cout << "Now enter your weight for the edge por favor." << endl;
      cin >> weight;
      cin.ignore();
      if(graph.addEdge(node1, node2, weight)){//if the edge is successfully added, great!
	cout << "Edge successfully added. You deserve a back massage." << endl;
      }
      else{//if the edge or node(s) doesn't exist, don't do anything
	cout << "Yo that edge or node(s) couldn't be found. Lo siento." << endl;
      }
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "deletenode")){//delete a node and any vertex that is connected to it
      char deletenode[25];
      cout << "Enter the name of the node you would like to delete por favor." << endl;
      cin.get(deletenode, 25);
      cin.ignore();
      if(graph.deleteNode(deletenode)){//if it successfully deletes
	cout << "Node successfully deleted. You deserve a pat on the back." << endl;
      }
      else{//if the node does not exist, don't do anything
	cout << "Yo that node doesn't exist fam. Lo siento. Try again." << endl;
      }
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "deleteedge")){//delete an edge between two nodes
      char deletenode1[25];
      char deletenode2[25];
      cout << "Enter the name of your first node por favor" << endl;
      cin.get(deletenode1, 25);
      cin.ignore();
      cout << "Enter the name of your second node por favor" << endl;
      cin.get(deletenode2, 25);
      cin.ignore();
      if(graph.deleteEdge(deletenode1, deletenode2)){//if it succesfully deletes
	cout << "Edge successfully deleted. You deserve a back rub." << endl;
      }
      else{//if the edge doesn't exist, don't do anything
	cout << "Yo that edge doesn't exist fam. Lo siento. Try again." << endl;
      }
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "printmatrix")){//prints out the adjacency matrix
      graph.print();
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "findpath")){//find the shortest path between two nodes according to the weight
      char node1[25];
      char node2[25];
      cout << "Enter your first node por favor." << endl;
      cin.get(node1, 25);
      cin.ignore();
      cout << "Enter your second node por favor." << endl;
      cin.get(node2, 25);
      cin.ignore();
      graph.printPath(node1, node2);
      cout << "Please enter a command: 'addnode', 'addedge', 'deletenode', 'deleteedge', 'printmatrix', 'findpath', 'quit'" << endl;
    }
    else if(!strcmp(input, "quit")){//quit the program
	running = false;
    }
    else {
      cout << "Invalid command. Try again por favor." << endl;
    }
  }
}
