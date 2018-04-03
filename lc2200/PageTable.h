#ifndef INCLUDED_PageTable
#define INCLUDED_PageTable

//NOTE: this is not included to the simulator, still in DEV
#include "PCB.h"
#include <iostream>
using namespace std;

#include "useful_classes/LList.h"
#include "PageInfo.h"


class PageTable {

  // Class Invariant (CI): page_table will hold pageinfo objects, no PageInfo
  // will have the same physical_page. free_pages will reprent the pages not
  // taken and physical_page_size will be the maxium number of pages allowed
  // in the table, page size will all way be >= page_table.size

private:
  uint physical_page_size;
  LList<PageInfo*> page_table;
  LList<int> free_pages;
public:

  //PRE:
  //POST:
  PageTable();

  //PRE:
  //POST: returns the frams that are available and not dirty
  uint framesNotDirty();

  //PRE:  @param uint size
  //POST: physical_page_size = size
  void setSize(uint size);

  //PRE: uint number_of_pages set the number of free pages in the page table
  //POST: creates a linked list of pages specifed as the parameter
  void setFreePages(uint number_of_pages);

  //PRE:
  //POST: returns the first free_page and removes it
  uint getFreePage();


  //PRE:
  //POST: returns the number of free pages
  int getNumberOfFree();

  //PRE:  @param PCB * process, the process
  //      @param uint virtual_page, the virtual_page of the page
  //      @param uint physical_page
  //      @param bool stack
  //POST: @return the physical_page page of memory it found a free page
  uint insertPage(PCB * process, uint virtual_page, bool stack);

  //PRE:
  //POST:
  ~PageTable();


};
#endif
