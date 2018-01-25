
#include "Simulator.h"
#include <iostream>
using namespace std;
// Author: Thomas Peacemaker
// Pre : argc is the number of command line arguements passed
//       argv is the command line arguements passed
// Post:
int main(int argc, char * argv[])
{
  Simulator s;

  int line = 0x01200000;
  s.executeLine(line);
}
