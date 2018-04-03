#include <iostream>
#include "constants.h"
#include "PageInfo.h"
using namespace std;


// Default Constructor
// Pre :
// Post:
PageInfo::PageInfo() {

}

//===============================
// Getters
//===============================

//PRE:
//POST: returns the value of PID;
uint PageInfo::getPID() {
  return PID;
}

//PRE:
//POST: returns the value of physical_page_number
uint PageInfo::getVirtualPage() {
  return virtual_page;
}

//PRE:
//POST: returns the value of dirty;
bool PageInfo::getDirty() {
  return dirty;
}


//PRE:
//POST: returns the value of page_type;
bool PageInfo::getStack() {
  return stack;
}

//PRE:
//POST: returns the value of physical_page_number
uint PageInfo::getPhysicalPage() {
 return physical_page;
}

//===============================
// Setters
//===============================

//PRE:uint value
//POST: PID = value;
void PageInfo::setPID(uint value) {
  PID = value;
}

//PRE: uint value
//POST: virtual_page = value
void PageInfo::setVirtualPage(uint value) {
  virtual_page = value;
}

//PRE: bool value
//POST: dirty = value
void PageInfo::setDirty(bool value) {
  dirty = value;
}


//PRE: bool value
//POST: stack = value
void PageInfo::setStack(bool value) {
  stack = value;
}

//PRE: uint value
//POST: physical_page = value
void PageInfo::setPhysicalPage(uint value) {
  physical_page = value;
}

PageInfo::~PageInfo() {

}
