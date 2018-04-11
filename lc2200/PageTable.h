#ifndef INCLUDED_PageTable
#define INCLUDED_PageTable

//NOTE: this is not included to the simulator, still in DEV

#include <iostream>
using namespace std;
#include "LList.h"
#include "PageInfo.h"

class PageTable {

  // Class Invariant (CI):

private:
  uint physical_page_size;
  LList<*PageInfo> page_table;
  LList<int> free_pages;
public:

  //PRE:
  //POST:
  PageTable(uint given_size);

  //PRE:
  //POST:
  ~PageTable();


};
#endif
