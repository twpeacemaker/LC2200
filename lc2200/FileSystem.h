#ifndef INCLUDED_FileSystem
#define INCLUDED_FileSystem

#include "constants.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
using namespace std;

class FileSystem {

  // Class Invariant (CI):

  private:
    fstream * disk;
  public:


    // Constructor
    // Pre : uint filesyssize, is the size of the current file system
    // Post:
    FileSystem(uint filesyssize);


    // Pre :
    // Post:
    ~FileSystemory();
};

#endif
