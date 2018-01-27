#include "Terminal.h"
#include "Exception.h"

#include <iostream>
using namespace std;
// Author: Thomas Peacemaker
// Pre : argc is the number of command line arguements passed
//       argv is the command line arguements passed
// Post:
int main(int argc, char * argv[])
{

  if(argc <= 2){
    try{
      if(argc == 1) {
        Terminal t = Terminal();
        t.start();
      } else {
        //Assert: argc == 2
        Terminal t = Terminal(argv[1]);
        t.start();
      }
    } catch(Exception e){
      e.handle();
    }

  } else{
    cout << "ERROR: Invalid input. Ex: ./Simulator {memory_size}" << endl;;
  }


}
