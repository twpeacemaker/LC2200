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

    //PRE: @param uint filesyssize is the size of the current file system
    //POST:
    void format(uint filesyssize);

    //PRE:
    //POST: makes the file
    void makeFile();

    //PRE: @param const char * filename, the name of the file
    //POST:
    bool fileExists(const char * filename);

    //PRE:
    //POST:
    void makeSuperNode(uint filesyssize);

    //PRE:  uint word, the word to be inserted
    //      uint inode_num, the number inode you want to insert to
    //      uint word_num, the word you want to insert to
    //POST: writes the word to the disk file
    void insertWord(uint word, uint inode_num, uint word_num);

    //PRE:  uint inode_num, the number inode you want to insert to
    //      uint word_num, the word you want to insert to
    //POST: gets the word at the location specifed
    uint getWord(uint inode_num, uint word_num);

    //PRE:  uint byte_num, the byte_num to set the cursor to
    //      uint inode_num, the number inode to set the cursor to
    //      uint word_num, the word to set the cursor to
    //POST: sets the location of the file cursor
    void setDiskLocation(uint inode_num, uint word_num, uint byte_num);

    //PRE:  char * name, the name of the directory
    //      uint addr_of_parent, the address of the parent node
    //      uint prev_sib, the address of the previous sibling
    //      uint next_sib, the address of the next sibling
    //      uint inode_num, the inode number to insert into
    //POST: creates the directory with the given information, initlizes everyting
    //      to the value 0
    void makeDirectory(char * name, uint addr_of_parent, uint prev_sib,
                       uint next_sib, uint inode_num);

    //PRE:  uint type, type of inode, type < 4
    //POST: writes the file type to disk
    void insertInodeType(uint type, uint inode_num);

    //PRE: char * name, the name to be inserted
    //     uint inode_num, the inode number to insert the name to
    //     the inode must be a type that has a name
    //POST:inserts the name from bites 2- 21 in the program file
    void insertName(char * name, uint inode_num);

    //PRE: uint value, the value to be inserted
    //     uint inode_num, the address of the inode to be edited
    //POST:
    void insertNumberOfChildren(uint value, uint inode_num);

    //PRE:  uint value, the value to insert
    //      uint inode_num, the inode to insert to
    //POST: the value of the parent node will be inserted to the inode specifed
    void insertParentInodeNum(uint value, uint inode_num);


    //PRE:  uint value, the value to insert
    //      uint inode_num, the inode to insert to
    //POST: inserts the value of the first child inode
    void insertFirstChildInodeNum(uint value, uint inode_num);

    //PRE:  uint value, the value to insert
    //      uint inode_num, the inode to insert to
    //POST: inserts the value of the prev node
    void insertPrevInode(uint value, uint inode_num);

    //PRE:  uint value, the value to insert
    //      uint inode_num, the inode to insert to
    //POST: inserts the value of the previous node
    void insertNextInode(uint value, uint inode_num);


    // Pre :
    // Post:
    ~FileSystem();
};

#endif
