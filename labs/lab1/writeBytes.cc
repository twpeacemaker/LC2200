#include <iostream>

using namespace std;

#define BYTEMASK 0xff
#define BYTESIZE 8

int main () {
  int num = 0x6162;
  char ch = (num & BYTEMASK);
  cout.put(ch);
  num = num >> BYTESIZE;
  ch = (num & BYTEMASK);
  cout.put (ch);
  return (0);
}
