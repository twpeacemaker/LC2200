#ifndef INCLUDED_EXCEPTION
#define INCLUDED_EXCEPTION

#include <iostream>
using namespace std;

class Exception {
 private:
  char * msg;

 public:
  // PRE: message is defined.
  // POST: message is the error message stored in thsi exception object. 
  Exception (char * message) {
    msg = message;
  };

  // PRE: This object is defined and has an error message.
  // POST: The exception is handled, i.e., the error message is printed. 
  void handle() {
    cout << msg << endl;
  };
  
};

#endif
