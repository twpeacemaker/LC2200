#ifndef INCLUDED_MYSTRING
#define INCLUDED_MYSTRING

#include <iostream>
#include <stdio.h>
#include "MyString.h"
#include "LList.h"
using namespace std;

class MyString {

 private:

  char * theString; // pointer to the space allocated for the array of
		    // characters.
  int currentMax;   // the maximum number of characters that can be
		    // currently accommodated in this MyString object.

  int maxIntSize;   // the max size of added integers
  // CI: theString points to space allocated for at least one
  //       character.
  //     currentMax >= 0. theString points to space allocated for
  //       currentMax + 1 characters (one character space is reserved for
  //       the end of string character)
  //     currentSize = 0. currentSize <= currentMax.
  //       theString[0]..theString[currentSize-1] is
  //       defined. theString[currentSize] is the end of string
  //       character.

  int currentSize;  // the number of characters currently in this
  // MyString object.


 public:

  // Default constructor
  // PRE:
  // POST: currentMax = 0. currentSize = 0. There is one space
  //         allocated for the object. theString[0] = '\0'.
  //         CI is satisfied.
  MyString ();




  // PRE:
  // POST: currentMax = 0. currentSize = 0. There is one space
  //         allocated for the object. theString[0] = '\0'.
  //         CI is satisfied.
  MyString (char * name);

  // Pre : This object is defined
  // Post: We return a copy of this MyString Object
  MyString & operator =(const MyString & S);


  // Pre : this object is defined
  // Post: we make a copy of MyString
  MyString(const MyString & S);


  //PRE: takes a init my string object
  //POST: returns true if the two strings are the same, false if they are
  //      differant
  bool isEqual(MyString s2);

  // Output member functions
  // PRE: This MyString object is defined and satisfies the CI.
  // POST: OS contains a newline followed by the values of currentMax,
  // currentSize and the characters in theString followed by a
  // newline.
  void debugPrint () const;

  // PRE: This MyString object is defined and satisfies the CI.
  // POST: OS contains the characters in this string.
  void print () const;

  //PRE: s must be initalized
  //POST: return int current size
  int getCurrentSize();

  // Modifiers

  // PRE: This MyString object is defined with values
  //       currentMax = M, currentSize = S, and satisfies the CI.
  // POST: ch is defined.
  //       theString[0]..theString[S-1] are the same as before.
  //       theString[S] = ch
  //       theString[S+1] = '\0'
  //       The result object satisfies the CI.
  void add (char ch);

  // Pre : char * ch is the string of characters to be added
  // Post: we will call the add function on each of the characters
  void addString(char * ch);

  // Pre :
  // Post: we will return theString
  char * getString();

  // Pre : MyLines object is defined and statisfies the CI
  //       requested is an integer
  // Post: OS contains the requested index
  char requestindex(int index);


  // Pre : MyString ch is the MyString object we want to add
  // Post: we will cycle through all the characters of ch
  //       and add them to our current object
  void addMyString(MyString ch);


  // Pre : this object is declared
  // Post: we return the string back to defaults
  void resetString();

  // Pre : the integer is less then or equal to maxIntSize
  //        digits long
  //       this object is defined
  // Post: we will convert the integer into a char array
  //       we will then add the char array to the mystring
  void addInt(int ch);

  friend ostream & operator <<(ostream & str, const MyString & M);

  friend ostream & operator <<(ostream & str, const MyString * M);

  //PRE: inited mystring, ch is the character you want the fuction to split the
  //     string up into
  //POST:returns a linked list object of of string split by the var given so if
  //     given, Thomas Peacemaker with ch = " " it will return ["Thomas",
  //     "Peacemaker"],
  LList<MyString> split(char ch);

  // Pre : This object is defined
  // Post: returns all memory to the system
  ~MyString();

};
#endif
