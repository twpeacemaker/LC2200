#include <iostream>

using namespace std;

int main () {

  char * Name = new char[9];

  char ch = 'a';
  for (int i = 0; i < 8; i++) {
    Name[i] = ch;
    ch++;
  }
  Name[8] = '\0';

  int * word = (int *) Name;

  cout << hex << *word << dec << endl;

  word += 1;

  cout << hex << *word << dec << endl;

  cout << "*" << Name << "*" << endl;

  Name = Name + 1;

  cout << "*" << Name << "*" << endl;

  return (0);
}
