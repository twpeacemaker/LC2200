#include "Freemem.h"
#include <iostream>
#include "constants.h"
using namespace std;

// Default Constructor
// Pre :
// Post:
Freemem::Freemem() {

}

// Pre : @param uint temp_start, the start of Freemem
//       @param uint temp_end,  the end of the Freemem
// Post: initlizes the Freemem class
Freemem::Freemem(uint temp_start, uint temp_end) {
     start = temp_start;
     end   = temp_end;
}

//PRE:
//POST: @returns uint, the start of the Freemem
uint Freemem::getStart() const {
     return start;
}

//PRE: uint temp_start, value to set to start
//POST: start = temp_start
void Freemem::setStart(uint temp_start){
     start = temp_start;
}

//PRE:
//POST:@ return uint end of Freemem
uint Freemem::getEnd() const {
     return end;
}

//PRE: takes the as uint value of what you want to set
//     end to
//POST: makes end = new_end
void Freemem::setEnd(uint temp_end) {
     end = temp_end;
}

//PRE:
//POST: @returns, the size of the Freemem object
uint Freemem::getSize() {
     return( (end - start) / BYTES_IN_WORD);
}


Freemem::~Freemem() {

}
