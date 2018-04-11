#ifndef INCLUDED_Page
#define INCLUDED_Page

#include <iostream>
#include "constants.h"
using namespace std;


class PageInfo {
private:
  uint PID;
  uint virtual_page;
  bool dirty;
  bool stack;
  uint physical_page;
public:

  // Class Invariant (CI):

  // Default Constructor
  // Pre :
  // Post:
  PageInfo();

  //===============================
  // Getters
  //===============================

  //PRE:
  //POST: returns the value of PID;
  uint getPID();

  //PRE:
  //POST: returns the value of physical_page_number
  uint getVirtualPage();

  //PRE:
  //POST: returns the value of dirty;
  bool getDirty();


  //PRE:
  //POST: returns the value of page_type;
  bool getStack();

  //PRE:
  //POST: returns the value of physical_page_number
  uint getPhysicalPage();

  //===============================
  // Setters
  //===============================

  //PRE:uint value
  //POST: PID = value;
  void setPID(uint value);

  //PRE: uint value
  //POST: virtual_page = value
  void setVirtualPage(uint value);

  //PRE: bool value
  //POST: dirty = value
  bool setDirty(bool value);


  //PRE: bool value
  //POST: stack = value
  bool setStack(bool value);

  //PRE: uint value
  //POST: physical_page = value
  uint setPhysicalPage(uint value);

  ~PageInfo();
};
#endif
