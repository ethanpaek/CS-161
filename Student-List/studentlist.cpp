/*Ethan Paek, October 6th, 2016, This is Student List - a code to add, print, and delete 
students from a literal list. It utilizes structs, pointers, and vectors.*/
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

struct Student {//main struct for the individual student
  char* firstname;
  char* lastname;
  float gpa;
  int id;
};

void printList(vector<Student*>* list);
void addStudent(vector<Student*>* list);
void deleteStudent(vector<Student*>* list);

int main(){
  vector<Student*> list;
  bool run = true;
  char input[20];
  cout << "Please enter a command." << endl;
  cout << "Type in: PRINT, ADD, DELETE, or QUIT" << endl;
  while (run == true) {
    cin.get(input, 20);
    cin.ignore();
    if (!strcmp(input,"PRINT")){//when you type "PRINT"
      printList(& list);
    }
    else if (!strcmp(input,"ADD")){//when you type "ADD"
      addStudent(& list);
    }
    else if (!strcmp(input,"DELETE")){//when you type "DELETE"
      deleteStudent(& list);
    }
    else if (!strcmp(input,"QUIT")){//when you type "QUIT"
      run = false;
    }
    else {//if it's not one of the four commands
      cout << "Invalid command. Try again por favor. Gracias." << endl;
    }
  }
}

void printList(vector<Student*>* list){//print out the student list
  for (vector<Student*>::iterator it = list->begin(); it != list->end(); it++){
    cout << "Name: " << (*it)->firstname << " " << (*it)->lastname << " ID: " << (*it)->id << " GPA: " << setprecision(2) << fixed << (*it)->gpa << endl;
  }
   cout << "Type in: PRINT, ADD, DELETE, or QUIT" << endl;
}

void addStudent(vector<Student*>* list){//add a student
  Student* student = new Student;
  int newid;
  char newfirstname[50];
  char newlastname[50];
  float newgpa;
  cout << "Enter the student's first name." << endl;
  cin.get(newfirstname, 50);
  cin.ignore();
  cout << "Enter the student's last name." << endl;
  cin.get(newlastname, 50);
  cin.ignore();
  cout << "Enter the student's ID number." << endl;
  cin >> newid;
  cout << "Enter the student's accumlative GPA." << endl;
  cin >> newgpa;
  student->firstname = strdup(newfirstname);
  student->lastname = strdup(newlastname);
  student->id = newid;
  student->gpa = newgpa;
  cin.ignore();
  cout << "The student is now added! You deserve a cookie." << endl;
  cout << "Name: " << student->firstname << " " << student->lastname << " ID: " << student->id << " GPA: " << setprecision(2) << fixed << student->gpa << endl;
  list->push_back(student);
  cout << "Type in: PRINT, ADD, DELETE, or QUIT" << endl;
}

void deleteStudent(vector<Student*>* list){//delete a student
  bool deleteee = false;
  int deleteID;
  cout << "Please enter the ID of the student you'd like to remove." << endl;
  cin >> deleteID;
  cin.ignore();
  for(vector<Student*>::iterator it = list->begin(); it != list-> end(); it++){//look through list and anyone with matching ID
    if((*it)->id == deleteID) {
      delete (*it)->firstname;
      delete (*it)->lastname;
      list->erase(it);
      delete *it;
      it = list->end();
      it--;
      cout << "Congratulations! You have successfully deleted the following student!" << endl;
      deleteee = true;
    }
  }
  if (deleteee == false) {//if ID does not exist
    cout << "ID does not exist. Try again por favor. Gracias." << endl;
  }
  cout << "Type in: PRINT, ADD, DELETE, or QUIT" << endl;
}
