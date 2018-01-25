#include <iostream>
#include <stdio.h>

using namespace std;

int main () {
  unsigned char ch;
  bool done = false;
  while (!done) {
    ch = cin.get();
    if (!cin.eof()) {
      printf ("%#x ", (unsigned int)ch);
    }
    else
      done = true;
  }
  cout << endl;
  return (0);
}
