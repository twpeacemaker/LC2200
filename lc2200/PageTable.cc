#include <iostream>
using namespace std;
#include "useful_classes/LList.h"
#include "PageTable.h"
#include "PageInfo.h"
//#include "PCB.h"

//PRE:
//POST:
PageTable::PageTable() {

}


//PRE:  @param uint size
//POST: physical_page_size = size
void PageTable::setSize(uint size) {
  physical_page_size = size;
}

//PRE:
//POST: returns the frams that are available and not dirty
uint PageTable::framesNotDirty() {
  uint return_value = physical_page_size;
  for(int i = 0; i < page_table.getSize(); i++) {
    if(page_table.getNth(i)->getDirty() == true) {
      physical_page_size--;
    }
  }
  return return_value;
}

//PRE: uint number_of_pages set the number of free pages in the page table
//POST: creates a linked list of pages specifed as the parameter
void PageTable::setFreePages(uint number_of_pages) {
  for(int i = 0; i < number_of_pages; i++) {
    free_pages.addBack(i);
  }
}

//PRE:
//POST: returns the first free_page and removes it
uint PageTable::getFreePage() {
  uint return_value;
  if(getNumberOfFree() > 0) {
    return_value = free_pages.getFront();
    free_pages.deleteFront();
  } else {
    cout << "free page up out of the PageTable" << endl;
  }
  return return_value;
}

//PRE:
//POST: returns the number of free pages
int PageTable::getNumberOfFree() {
  return free_pages.getSize();
}

//PRE:  @param PCB * process, the process
//      @param uint virtual_page, the virtual_page of the page
//      @param uint physical_page
//      @param bool stack
//POST: @return the physical_page page of memory it found a free page
uint PageTable::insertPage(PCB * process, uint virtual_page, bool stack) {
    PageInfo * page = new PageInfo;
    page->setPID(process->getID());
    page->setVirtualPage(virtual_page);
    page->setStack(stack);
    uint physical_page = getFreePage();
    page->setPhysicalPage(physical_page);
    page_table.addBack(page);
    process->addPage(page); //needs to be added
    return physical_page;
}



//PRE:
//POST:
PageTable::~PageTable() {

}
