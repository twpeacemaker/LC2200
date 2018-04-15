#include "FileSystem.h"
#include "constants.h"
#include "Exception.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_classes/MyString.h"
#include <iostream>
#include <fstream>
using namespace std;



// Constructor
// Pre : @param uint filesyssize, is the size of the current file system
// Post:
FileSystem::FileSystem(uint filesyssize) {
	if(!fileExists(FILE_SYSTEM_NAME)) {
    makeFile();
    disk = new fstream (FILE_SYSTEM_NAME, ios::in | ios::out);
    format(filesyssize);
  }
}

//PRE: @param uint filesyssize is the size of the current file system
//POST:
void FileSystem::format(uint filesyssize) {
  uint number_of_bytes_in_file = BYTES_IN_WORD * NUM_LINES_IN_INODE * (filesyssize + 1);
  for(int i = 0; number_of_bytes_in_file > i; i++) {
    disk->put((char)0);
  }
  makeSuperNode(filesyssize);
  //ASSERT: init the / at the location 1
  makeDirectory((char *)"/",0,0,0,1);
  makeFreeInode(uint prev_inode, uint next_inode, uint inode_num);
}

//PRE:
//POST: makes the file
void FileSystem::makeFile() {
  disk = new fstream (FILE_SYSTEM_NAME, ios::out);
  disk->close();
}

//PRE:  uint prev_free_inode,
//      uint next_free_inode,
//      uint inode_num,
//POST:
void makeFreeInode(uint prev_free_inode, uint next_free_inode, uint inode_num) {
  insertInodeType(FREEINODE_ID, inode_num);
  insertPrevInode(prev_free_inode, inode_num);
  insertNextInode(next_free_inode, inode_num);
}

//PRE:  char * name, the name of the directory
//      uint addr_of_parent, the address of the parent node
//      uint prev_sib, the address of the previous sibling
//      uint next_sib, the address of the next sibling
//      uint inode_num, the inode number to insert into
//POST: creates the directory with the given information, initlizes everyting
//      to the value 0
void FileSystem::makeDirectory(char * name, uint addr_of_parent, uint prev_sib, uint next_sib, uint inode_num) {
  insertInodeType(DIRECTORY_ID, inode_num);
  insertName(name, inode_num);
  insertParentInodeNum(addr_of_parent, inode_num);
  insertPrevSibInode(prev_sib, inode_num);
  insertNextSibInode(prev_sib, inode_num);
}

//PRE: uint value, the value to be inserted
//     uint inode_num, the address of the inode to be edited
//POST:
void FileSystem::insertNumberOfChildren(uint value, uint inode_num) {
  uint word = getWord(inode_num, DIR_NUM_PARENT_LINE);
  word = insertNum(word, value, 2, 3);
  insertWord(word, inode_num, DIR_NUM_CHILD_LINE);
}

//PRE:  uint value, the value to insert
//      uint inode_num, the inode to insert to
//POST: the value of the parent node will be inserted to the inode specifed
void FileSystem::insertParentInodeNum(uint value, uint inode_num) {
  uint word = getWord(inode_num, DIR_NUM_PARENT_LINE);
  word = insertNum(word, value, 0, 1);
  insertWord(word, inode_num, DIR_NUM_PARENT_LINE);
}

//PRE:  uint value, the value to insert
//      uint inode_num, the inode to insert to
//POST: inserts the value of the first child inode
void FileSystem::insertFirstChildInodeNum(uint value, uint inode_num) {
  uint word = getWord(inode_num, DIR_NUM_CHILD_LINE);
  word = insertNum(word, value, 2, 3);
  insertWord(word, inode_num, DIR_NUM_CHILD_LINE);
}

//PRE:  uint value, the value to insert
//      uint inode_num, the inode to insert to
//POST: inserts the value of the prev node
void FileSystem::insertPrevInode(uint value, uint inode_num) {
  uint word = getWord(inode_num, NUM_PREV_INODE_LINE);
  word = insertNum(word, value, 0, 1);
  insertWord(word, inode_num, NUM_PREV_INODE_LINE);
}

//PRE:  uint value, the value to insert
//      uint inode_num, the inode to insert to
//POST: inserts the value of the previous node
void FileSystem::insertNextInode(uint value, uint inode_num) {
  uint word = getWord(inode_num, NUM_NEXT_INODE_LINE);
  word = insertNum(word, value, 2, 3);
  insertWord(word, inode_num, NUM_NEXT_INODE_LINE);
}



//PRE: char * name, the name to be inserted
//     uint inode_num, the inode number to insert the name to
//     the inode must be a type that has a name
//POST:inserts the name from bites 2- 21 in the program file
void FileSystem::insertName(char * name, uint inode_num) {
  setDiskLocation(inode_num, 0, 1);
  MyString str = name;
  uint str_size = str.getCurrentSize();
  uint str_index = 0;
  for (int i = 0; MAX_NAME_SIZE > i; i++) {
    char c; //the character to be inserted
    if(str_size > str_index) {
      c = str.requestindex(str_index);
      str_index++;
    } else {
      c = 0x00;
    }
    printf("Byte: %#08x \n" , c);
    disk->put(c);
  }
}

//PRE:  uint type, type of inode, type < 4
//POST: writes the file type to disk
void FileSystem::insertInodeType(uint type, uint inode_num) {
  setDiskLocation(inode_num, 0, 0);
  if(NUMBER_OF_INODE_TYPES > type) {
    disk->put((char)type);
  } else {
    throw(Exception((char *)"ERROR: UNKNOWN TYPE"));
  }
}

//PRE:  uint filesyssize, the size of the file system
//POST: writes and initlized super node
void FileSystem::makeSuperNode(uint filesyssize) {
    uint line = 0x00000000;
    //ASSERT: Bytes 0 and 1 (as a 16 bit value): number of free inodes
    //        So filesyssize - '/')
    uint num_free_inodes = filesyssize - 1;
    line = insertNum(line, filesyssize, 0, 1);
    line = insertNum(line, num_free_inodes, 2, 3);
    insertWord(line, 0, 0);

    //ASSERT: Bytes 0 and 1(as a 16 bit value):inode addr. of first free inode.
    //        Bytes 2 and 3 (as a 16 bit value): inode addr. of last free inode.
    //ASSERT: supernode location + '/'
    line = 0x00000000;
    uint first_free = 2;
    uint last_free = filesyssize - 1;
    line = insertNum(line, first_free, 0, 1);
    line = insertNum(line, last_free , 2, 3);
    insertWord(line, 0, 1);
    line = 0x00000000;
    //ASSERT: NUM_LINES_IN_INODE - (supernode + '/')
    for (int i = 2; NUM_LINES_IN_INODE > i; i++) {
      insertWord(line, 0, i);
    }
}

//PRE:  uint word, the word to be inserted
//      uint inode_num, the number inode you want to insert to
//      uint word_num, the word you want to insert to
//POST: writes the word to the disk file
void FileSystem::insertWord(uint word, uint inode_num, uint word_num) {
    setDiskLocation(inode_num, word_num, 0);
    for(int i = BYTES_IN_WORD - 1; i >= 0; i--) {
      uint byte_to_insert = getByte(word, i);
      //printf("Byte: (%c)%#08x \n" ,byte_to_insert, byte_to_insert);
      //here
      disk->put((char)byte_to_insert);
    }
}

//PRE:  uint inode_num, the number inode you want to insert to
//      uint word_num, the word you want to insert to
//POST: gets the word at the location specifed
uint FileSystem::getWord(uint inode_num, uint word_num) {
  setDiskLocation(inode_num, word_num, 0);
  char ch;
  uint word = 0;
  //to build the word
  for (int byte_num = 0; byte_num < BYTES_IN_WORD; byte_num++) { //x00112233
    //to add the char in the correct place
    disk->get(ch);
    uint byte = getBits((uint)ch, 7, 0);
    word = insertByte (word, byte, byte_num);
  }
  return word;

}
//PRE:  uint byte_num, the byte_num to set the cursor to
//      uint inode_num, the number inode to set the cursor to
//      uint word_num, the word to set the cursor to
//POST: sets the location of the file cursor
void FileSystem::setDiskLocation(uint inode_num, uint word_num, uint byte_num) {
  uint position = (inode_num * NUM_LINES_IN_INODE * BYTES_IN_WORD) +
                  (word_num * BYTES_IN_WORD) +
                  (byte_num);
  disk->seekp(position, ios::beg);
}

//PRE:  @param const char * filename, the name of the file
//POST: @return, returns weather the file exists
bool FileSystem::fileExists(const char * filename) {
  bool return_value = true;
  ifstream inFile(filename);
  if(!inFile) {
    return_value = false;
  }
  inFile.close();
  return return_value;
}


// Pre :
// Post:
FileSystem::~FileSystem() {
  disk->close();
}
