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
  if(argc <= 2){
    try{
      if(argc == 1) {
        Terminal t;
        t.start();
      } else {
        //Assert: argc == 2
        //passes the memory to terminal
        Terminal t(argv[1]);
        t.start();
      }
    } catch(Exception e){
      e.handle();
    }

  } else{
    cerr << "ERROR: Invalid input. Ex: ./Simulator {memory_size}" << endl;
  }

}
