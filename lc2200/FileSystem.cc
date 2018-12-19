#include "FileSystem.h"
#include "constants.h"
#include "Exception.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"
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
	present_directory = 1; //sets / to be the present_directory
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
  initFreeNodes(filesyssize);
}

//PRE:  char * input, takes the input from the terminal
//POST: tokenp[1] should be the path to the directory that
//      they wish to make
void FileSystem::mkdir(char * input) {
	MyString path = extractPath(input);
	LList<MyString> tokens = path.split('/'); //splits the string at '/'
	MyString name = tokens.getBack(); tokens.deleteBack();
	if(!name.empty()) {
		uint start_directory = getStartDirectory(path);
		uint location = findLocation(tokens, start_directory);
		// supernode
			//set the next of the free_node to be the first in the supernode
			uint free_node_address = unallocateFreeInode();
			//make check if it is also the first and last inode
			//set the number of freenodes to be freenodes - 1

		//node inserted
			//insert name
			//insert parent address
			//insert inode_num
			//edit when inserting to the parent prev_sib
			//exit when inserting to the parent next_sib

		//parent
			//insert the node into the correct location of the parent
			//Number of children++
		makeDirectory(name.getStringDeepCopy(),location,0,0,1);
	} else {
		throw(Exception((char *)"ERROR: DIRECTORY NAME IS EMPTY"));
	}
}

//PRE:  the disk must be formated
//POST: returns the location of the inode that is free and unallocates it from
//			the linked list of inodes
uint unallocateFreeInode() {
		uint free_inode;
		if(getNumberFreeNodes() == 0) {
			//ASSERT: no more room to insert a node
			throw(Exception((char *)"ERROR: NOT ENOUGH SPACE"));
		} else {
			free_inode = getFirstFreeInode();
		}
		//ASSERT: totalFreeNodes - 1
		setNumberFreeNodes(getNumberFreeNodes() - 1)
		//set prev
		uint next_free = getNextInode(free_inode);
		return free_inode,

}

//PRE:  MyString path, given a
//POST: determins if the path is absolut or relitive and returns the correct
//			beginning directory
uint FileSystem::getStartDirectory(MyString path) {
	bool start_directory = present_directory;
	if(path.requestindex(0) == '/') {
		start_directory = 1;
	}
	return start_directory;
}

//PRE: LList<MyString> tokens, the tokens to the path of the file
//		 uint start, where to start to look for the path
//POST: returns the inode of the destination
uint FileSystem::findLocation(LList<MyString> tokens, uint start) {
	uint return_value;
	if(tokens.getSize() == 0) {
		return_value = start;
	} else {
		cout << "hard part" << endl;
	}

	return return_value;
}

//PRE:  char * input, the input from the terminal
//POST: gets the path from the
char * FileSystem::extractPath(char * input) {
	MyString string = input;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
	return tokens.getBack().getStringDeepCopy();
}

//PRE:  char * input, takes the input from the terminal that should be no
//      more than three tokens and no less than 1
//POST: returns the content in the range specifted by the input
char * FileSystem::displayInode(char * input) {
	uint lower_bound = 0;
	uint upper_bound = getTotalNumberNodes() - 1;
	getUpperLowerBound(input, lower_bound, upper_bound);
	MyString string;                                     // string to be created
	char * header = new char[MAX_COL_DISPLAY_INODE];
	char * temp;
	for (int i = lower_bound; i <= upper_bound; i++) {
		sprintf (header, "Inode No. %d \n", i);
		string.addString(header);
		temp = getDisplayInode(i);
		string.addString(temp);
		delete [] temp;
		string.add('\n');
	}
	return string.getStringDeepCopy();
}

//PRE: @param int index, takes the index of memory, index > 0 < size
//POST: @return char* creates a string that represents the proper string
//      to be printed as one column to the terminal ie 0: 0x00000000 0
char * FileSystem::getDisplayInode(int index) {
	MyString string;
	for(int i = 0; i < NUM_LINES_IN_INODE; i++) {
		char * temp = new char[MAX_COL_DISPLAY_INODE];
		sprintf (temp, "0x%08X ", getWord(index, i));
		string.addString(temp);
		delete [] temp;
		if( (i + 1) % NUMBER_OF_COLS_IN_MEM == 0 ) {
			string.add('\n');
		}

	}
  return string.getStringDeepCopy();
}

//PRE:
//POST: makes the file
void FileSystem::makeFile() {
  disk = new fstream (FILE_SYSTEM_NAME, ios::out);
  disk->close();
}

//PRE : uint filesyssize, is the size of the current file system
//POST: creates the init free inodes for the disk
void FileSystem::initFreeNodes(uint filesyssize) {
  uint first_free = getFirstFreeInode();
  uint last_free  = getLastFreeInode();
  uint previous;
  uint next;
  for(int i = first_free; last_free >= i; i++) {
    if(i == first_free) {
      previous = 0;
      next = i + 1;
      makeFreeInode(previous, next, i);
    } else if(i == last_free) {
      previous = i - 1;
      next = 0;
      makeFreeInode(previous, next, i);
    } else {
      previous = i - 1;
      next = i + 1;
      makeFreeInode(previous, next, i);
    }
  }
}

//PRE:  takes no parameters
//POST: returns the number of free inodes
uint FileSystem::getNumberFreeNodes() {
  uint word = getWord(0, SUPERNODE_NODE_INFO_LINE);
  return getNum(word, 0, 1);
}

//PRE:  takes no parameters
//POST: sets the number of free nodes in the supernode
void setNumberFreeNodes(uint value) {
	uint word = getWord(value, SUPERNODE_NODE_INFO_LINE);
	word = insertNum(word, value, 0, 1);
	insertWord(word, SUPERNODE_ADDRESS, SUPERNODE_FREE_INODE_LINE);
}

//PRE:  takes no parameters
//POST: returns the total number of nodes
uint FileSystem::getTotalNumberNodes() {
  uint word = getWord(0, SUPERNODE_NODE_INFO_LINE);
  return getNum(word, 2, 3);
}

//PRE:
//POST:
uint setFirstFreeInode(uint value) {
	uint word = getWord(0, SUPERNODE_FREE_INODE_LINE);
	word = insertNum(word, value, 0, 1);
	insertWord(word, SUPERNODE_ADDRESS , SUPERNODE_FREE_INODE_LINE);
}

//PRE: takes not params
//POST: returns the address if the first inode specifed in the supernode
uint FileSystem::getFirstFreeInode() {
  uint word = getWord(0, SUPERNODE_FREE_INODE_LINE);
  return getNum(word, 0, 1);
}

//PRE: takes not params
//POST: returns the address of the last inode specifed in the supernode
uint FileSystem::getLastFreeInode() {
  uint word = getWord(0, SUPERNODE_FREE_INODE_LINE);
  return getNum(word, 2, 3);
}

//PRE:  uint prev_free_inode, the previous free inode address
//      uint next_free_inode, the next free inode address
//      uint inode_num, the address of the inode to be added
//POST: creates a inode with the given values at the given inode_num
void FileSystem::makeFreeInode(uint prev_free_inode, uint next_free_inode, uint inode_num) {
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
  insertPrevInode(prev_sib, inode_num);
  insertNextInode(next_sib, inode_num);
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

//PRE: uint inode_num, the inode address
//POST: returns the value of the previous inode
uint FileSystem::getPrevInode(uint inode_num) {
	uint word = getWord(inode_num, DIR_NUM_CHILD_LINE);
	return getNum(uint num, 0, 1);
}

//PRE: uint inode_num, the inode address
//POST: returns the value of the next inode
uint FileSystem::getNextInode(uint inode_num) {
	uint word = getWord(inode_num, DIR_NUM_CHILD_LINE);
	return getNum(uint num, 3, 4);
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
    //printf("Byte: %#08x \n" , c);
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
    line = insertNum(line, num_free_inodes , 0, 1);
    line = insertNum(line, filesyssize + 1, 2, 3);
    insertWord(line, 0, 0);

    //ASSERT: Bytes 0 and 1(as a 16 bit value):inode addr. of first free inode.
    //        Bytes 2 and 3 (as a 16 bit value): inode addr. of last free inode.
    //ASSERT: supernode location + '/'
    line = 0x00000000;
    uint first_free = 2;
    uint last_free = filesyssize;
    line = insertNum(line, first_free, 0, 1);
    line = insertNum(line, last_free , 2, 3);
    insertWord(line, 0, SUPERNODE_FREE_INODE_LINE);
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

//PRE: @param char * input, takes the input from the terminal
//     @param uint & lower_bound, is the lower requested by user
//     @param uint & upper_bound, is the upper requested by user
//POST:changes the upper and lower bound to correspond with the input request
//throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
void FileSystem::getUpperLowerBound(char * input, uint & lower_bound,
                                uint & upper_bound) {
  MyString string = input;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  tokens.deleteFront();
  uint size = getTotalNumberNodes();
  //ASSERT: tokens size is no more than 2
  if (tokens.getSize() == 1) {
    //first token to the end of memory
    lower_bound = arrayToInt(tokens.getFront().getString());
    if (lower_bound >= (size)) {
      throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
    }
  } else if(tokens.getSize() > 1) {
      lower_bound = arrayToInt(tokens.getFront().getString());
      upper_bound = arrayToInt(tokens.getBack().getString());
      if (lower_bound >= (size) || upper_bound >= (size) ||
          lower_bound > upper_bound) {
        throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
      }
  }
}

// Pre :
// Post:
FileSystem::~FileSystem() {
  disk->close();
}
