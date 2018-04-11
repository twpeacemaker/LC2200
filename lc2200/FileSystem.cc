

#include "constants.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
using namespace std;



// Constructor
// Pre : @param uint filesyssize, is the size of the current file system
// Post:
FileSystem::FileSystem(uint filesyssize) {
  fstream inFile("Disk");
	if(inFile == NULL) {
    cout << "make new" << endl;
    formate(filesyssize);
  }


}

//PRE: @param uint filesyssize is the size of the current file system
//POST:
FileSystem::formate(uint filesyssize) {

}


// Pre :
// Post:
FileSystem::~FileSystemory() {

}
