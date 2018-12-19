#ifndef INCLUDED_FileSystem
#define INCLUDED_FileSystem

#include "FileSystem.h"
#include "constants.h"
#include "Exception.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"
#include "useful_classes/MyString.h"
#include <iostream>
#include <fstream>
using namespace std;

class FileSystem {

  // Class Invariant (CI):

  private:
  fstream * disk;
  uint present_directory;



  //======================================
  // File Init
  //======================================

  //PRE:
  //POST: makes the file
  void makeFile();

  //PRE: @param const char * filename, the name of the file
  //POST:
  bool fileExists(const char * filename);


  //======================================
  // Super Node Methods
  //======================================

  //PRE:
  //POST:
  void makeSuperNode(uint filesyssize);

  //PRE: takes not params
  //POST: returns the address if the first inode specifed in the supernode
  uint getFirstFreeInode();

  //PRE: takes not params
  //POST: returns the address if the first inode specifed in the supernode
  uint setFirstFreeInode(uint value);

  //PRE: takes not params
  //POST: returns the address of the last inode specifed in the supernode
  uint getLastFreeInode();

  //PRE:  takes no parameters
  //POST: returns the number of free inodes
  uint getNumberFreeNodes();

  //PRE:  takes no parameters
  //POST: sets the number of free nodes in the supernode
  void setNumberFreeNodes(uint value);

  //PRE:  takes no parameters
  //POST: returns the total number of nodes
  uint getTotalNumberNodes();

  //======================================
  // Directory Methods
  //======================================

  //PRE:  MyString path, given a
  //POST: determins if the path is absolut or relitive and returns the correct
  //			beginning directory
  uint getStartDirectory(MyString path);

  //PRE:  char * name, the name of the directory
  //      uint addr_of_parent, the address of the parent node
  //      uint prev_sib, the address of the previous sibling
  //      uint next_sib, the address of the next sibling
  //      uint inode_num, the inode number to insert into
  //POST: creates the directory with the given information, initlizes everyting
  //      to the value 0
  void makeDirectory(char * name, uint addr_of_parent, uint prev_sib, uint next_sib, uint inode_num);

  //PRE:  uint value, the value to insert
  //      uint inode_num, the inode to insert to
  //POST: the value of the parent node will be inserted to the inode specifed
  void insertParentInodeNum(uint value, uint inode_num);

  //PRE:  uint value, the value to insert
  //      uint inode_num, the inode to insert to
  //POST: inserts the value of the first child inode
  void insertFirstChildInodeNum(uint value, uint inode_num);

  //PRE: uint value, the value to be inserted
  //     uint inode_num, the address of the inode to be edited
  //POST:
  void insertNumberOfChildren(uint value, uint inode_num);

  //PRE: char * name, the name to be inserted
  //     uint inode_num, the inode number to insert the name to
  //     the inode must be a type that has a name
  //POST:inserts the name from bites 2- 21 in the program file
  void insertName(char * name, uint inode_num);


  //======================================
  // Free Inode Methods
  //======================================

  //PRE : uint filesyssize, is the size of the current file system
  //POST: creates the init free inodes for the disk
  void initFreeNodes(uint filesyssize);

  //PRE:  uint prev_free_inode, the previous free inode address
  //      uint next_free_inode, the next free inode address
  //      uint inode_num, the address of the inode to be added
  //POST: creates a inode with the given values at the given inode_num
  void makeFreeInode(uint prev_free_inode, uint next_free_inode,
              uint inode_num);


  //=====================================
  // General Inode Function
  //=====================================

  //PRE: uint inode_num, the inode address
  //POST: returns the value of the previous inode
  uint getPrevInode(uint inode_num);

  //PRE:  uint value, the value to insert
  //      uint inode_num, the inode to insert to
  //POST: inserts the value of the prev node
  void insertPrevInode(uint value, uint inode_num);

  //PRE: uint inode_num, the inode address
  //POST: returns the value of the next inode
  uint getNextInode(uint inode_num);

  //PRE:  uint value, the value to insert
  //      uint inode_num, the inode to insert to
  //POST: inserts the value of the previous node
  void insertNextInode(uint value, uint inode_num);

  //PRE:  uint type, type of inode, type < 4
  //POST: writes the file type to disk
  void insertInodeType(uint type, uint inode_num);

  //======================================
  // Other
  //======================================

  //PRE:  uint byte_num, the byte_num to set the cursor to
  //      uint inode_num, the number inode to set the cursor to
  //      uint word_num, the word to set the cursor to
  //POST: sets the location of the file cursor
  void setDiskLocation(uint inode_num, uint word_num, uint byte_num);

  //PRE:  uint word, the word to be inserted
  //      uint inode_num, the number inode you want to insert to
  //      uint word_num, the word you want to insert to
  //POST: writes the word to the disk file
  void insertWord(uint word, uint inode_num, uint word_num);

  //PRE:  uint inode_num, the number inode you want to insert to
  //      uint word_num, the word you want to insert to
  //POST: gets the word at the location specifed
  uint getWord(uint inode_num, uint word_num);

  //PRE: @param char * input, takes the input from the terminal
  //     @param uint & lower_bound, is the lower requested by user
  //     @param uint & upper_bound, is the upper requested by user
  //POST:changes the upper and lower bound to correspond with the input request
  //throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
  void getUpperLowerBound(char * input, uint & lower_bound, uint & upper_bound);

  //PRE: @param int index, takes the index of memory, index > 0 < size
  //POST: @return char* creates a string that represents the proper string
  //      to be printed as one column to the terminal ie 0: 0x00000000 0
  char * getDisplayInode(int index);

  //PRE:  char * input, the input from the terminal
  //POST: gets the path from the input given
  char * extractPath(char * input);

  //PRE: LList<MyString> tokens, the tokens to the path of the file
  //		 uint start, where to start to look for the path
  //POST: returns the inode of the destination
  uint findLocation(LList<MyString> tokens, uint start);


public:


  // Constructor
  // Pre : uint filesyssize, is the size of the current file system
  // Post:
  FileSystem(uint filesyssize);

  //PRE: @param uint filesyssize is the size of the current file system
  //POST:
  void format(uint filesyssize);

  //PRE:  char * input, takes the input from the terminal that should be no
  //      more than three tokens and no less than 1
  //POST: returns the content in the range specifted by the input
  char * displayInode(char * input);

  //PRE:  char * input, takes the input from the terminal
  //POST: tokenp[1] should be the path to the directory that
  //      they wish to make
  void mkdir(char * input);

  // Pre :
  // Post:
  ~FileSystem();
  };

#endif
