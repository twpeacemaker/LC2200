#include "Terminal.h"
#include "Exception.h"

#include <iostream>
using namespace std;
// Author: Thomas Peacemaker
// Pre : argc is the number of command line arguements passed
//       argv is the command line arguements passed
// Post: runs till terminal is stopped
//cerr << "ERROR: Invalid input. Ex: ./Simulator {memory_size}" << endl;
int main(int argc, char * argv[])
{
  if(argc == 1) {
    try {
      Terminal t;
      t.start();
    } catch(Exception e){
      e.handle();
    }
  } else{
    cerr << "ERROR: Invalid input. Does not take parameters" << endl;
  }

}
