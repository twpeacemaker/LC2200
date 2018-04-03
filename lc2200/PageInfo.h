#ifndef INCLUDED_PageInfo
#define INCLUDED_PageInfo

#include <iostream>
#include "constants.h"
using namespace std;

// Class Invariant (CI): each page will be linked to a process by the PID,
// virtual_page will represent the page in the file and physical_page
// will represent the page in memory. dirty will represent if the page
// has been modifie. stack will represent if the page belongs to stack



class PageInfo {
private:
  uint PID;
  uint virtual_page;
  bool dirty;
  bool stack;
  uint physical_page;
public:




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
  void setDirty(bool value);


  //PRE: bool value
  //POST: stack = value
  void setStack(bool value);

  //PRE: uint value
  //POST: physical_page = value
  void setPhysicalPage(uint value);

  ~PageInfo();
};

#endif
