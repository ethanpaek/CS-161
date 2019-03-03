//Ethan Paek, September 21st, 2016, This is a simulation of TicTacToe with C++
#include <iostream>
#include <cstring>
using namespace std;

void printBoard(char (*board)[3]) {//prints out the two-dimensional array (or grid)
  cout << "\ta\tb\tc" << endl;
  cout << "1\t" << board[0][0] << "\t" << board[1][0] << "\t" << board[2][0] <<endl;
  cout << "2\t" << board[0][1] << "\t" << board[1][1] << "\t" << board[2][1] <<endl;
  cout << "3\t" << board[0][2] << "\t" << board[1][2] << "\t" << board[2][2] <<endl;
}

bool checkWin(char (*board)[3], char player){//checks if there's a win
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player){
    return true;
  }
  if (board[0][0] == player && board[0][1] == player && board[0][2] == player){
    return true;
  }
  if (board[0][0] == player && board[1][0] == player && board[2][0] == player){
    return true;
  }
  if (board[0][1] == player && board[1][1] == player && board[2][1] == player){
    return true;
  }
  if (board[0][2] == player && board[1][2] == player && board[2][2] == player){
    return true;
  }
  if (board[1][0] == player && board[1][1] == player && board[1][2] == player){
    return true;
  }
  if (board[2][0] == player && board[2][1] == player && board[2][2] == player){
    return true;
  }
  if (board[2][0] == player && board[1][1] == player && board[0][2] == player){
    return true;
  }
  return false;
}

bool checkTie(char (*board)[3]) {//checks if there'a tie
  bool tie = true;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (board[i][j] == ' ') {
       tie = false;
      }
    }
  }
  return tie;
}

void resetBoard(char (*board)[3], char & turn){ //makes each space in the grid blank
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
  }
  turn = 'O';
}

int main(){
  char board[3][3];
  int Xwins = 0;
  int Owins = 0;
  bool play = true;
  char turn = 'X';
  char input[6];
  cout << "Welcome to the tactical game of TicTacToe!" << endl;
  cout << "X will always go first!" << endl;
  cout << "Enter a coordinate to place your piece. (Ex: a2)" << endl;

  while(play == true) {
    resetBoard(board, turn);
    printBoard(board);
    while(!(checkWin(board,turn) || checkTie(board))){
      if (turn == 'X') {
	turn = 'O';
      }
      else {
	turn = 'X';
      }
      bool move = false;
      while (move == false){
	cin >> input;
	if (strlen(input) != 2){//whether or not if the player entered a coordinate
	  cout << "Enter a coordinate to place your piece. (Ex: a2)" << endl;
	}
	else if (input[0] != 'a' && input[0] != 'b' && input[0] != 'c'){
	  cout << "The first character needs to be a, b, or c." << endl;
	}
	else if (input[1] != '1' && input[1] != '2' && input[1] != '3'){
	  cout << "The second character needs to be 1, 2, or 3." << endl;
	}
	else if (board[input[0]-'a'][input[1]-'1'] == ' '){
	  board[input[0]-'a'][input[1]-'1'] = turn;
	  move = true;
	  printBoard(board);
	}
	else{
	  cout << "That space is taken. Nice try you snake." << endl; 
	}
      }
    }
    if (checkWin(board,turn)){//constantly checks for a tie or win
      if (turn == 'X') {
        Xwins++;
      }
      else {
        Owins++;
      }
      cout << turn << " Wins! You deserve a cookie." << endl;
      cout << "X now has " << Xwins << " wins." << endl;
      cout << "O now has " << Owins << " wins." <<  endl;
      cout << "Do you want to play again? (y/n)" << endl;
      cin >> input;
    }    
    else if (checkTie(board)){
      cout << "The game ended in a tie. Give each other a big hug." << endl;
      cout << "X now has " << Xwins << " wins." << endl;
      cout << "O now has " << Owins << " wins." <<  endl;
      cout << "Do you want to play again? (y/n)" << endl;
      cin >> input;
    }
    if(strcmp(input,"y")){//if the player says yes to playing again
      play = false;
    }
  }
}
