#ifndef INCLUDED_Freemem
#define INCLUDED_Freemem
#include "Freemem.h"
#include <iostream>
#include "constants.h"
using namespace std;


class Freemem {
private:
     uint start;
     uint end;
public:

  // Class Invariant (CI): start will be greater than zero and less than end
  // end will be more than start and less than size

  // Default Constructor
  // Pre :
  // Post:
  Freemem();

  // Pre : @param uint temp_start, the start of Freemem
  //       @param uint temp_end,  the end of the Freemem
  // Post: initlizes the Freemem class
  Freemem(uint temp_start, uint temp_end);

  //PRE:
  //POST: @returns uint, the start of the Freemem
  uint getStart() const;

  //PRE: uint temp_start, value to set to start
  //POST: start = temp_start
  void setStart(uint temp_start);

  //PRE:
  //POST:@ return uint end of Freemem
  uint getEnd() const;

  //PRE: takes the as uint value of what you want to set
  //     end to
  //POST: makes end = new_end
  void setEnd(uint temp_end);

  //PRE:
  //POST: returns the about of space that is within the free_mem
  uint getSize();


  ~Freemem();
};
#endif
