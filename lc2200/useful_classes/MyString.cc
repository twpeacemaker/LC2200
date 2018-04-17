#include <iostream>
#include <stdio.h>
#include "MyString.h"
#include "LList.h"
#include "../Exception.h"

using namespace std;

// Default constructor
// PRE:
// POST: currentMax = 0. currentSize = 0. There is one space
//         allocated for the object. theString[0] = '\0'.
//         CI is satisfied.
MyString::MyString () {
  // we can currently hold no items
  currentMax = 0;
  // we need room for an end of string character
  theString = new char[currentMax + 1];
  // adding the end of string character
  theString[0] = '\0';
  // currently have no items
  currentSize = 0;
}

// PRE:
// POST: currentMax = 0. currentSize = 0. There is one space
//         allocated for the object. theString[0] = '\0'.
//         CI is satisfied.
MyString::MyString (char * name) {
  currentMax = 0;
  theString = new char[currentMax + 1];
  theString[0] = '\0';
  currentSize = 0;
  int index = 0;
  addString(name);
}

// Pre : This object is defined
// Post: We return a copy of this MyString Object
MyString & MyString::operator =(const MyString & S) {
                               // there are some characters in this
                               // (implicit parameter) object.
  delete (theString);          // free the current space used for a
                               // string by the  implicit parameter.

  currentMax = S.currentMax;   // copy the values of the static member
  currentSize = S.currentSize; //   data objects
  theString = new char[currentMax]; // get space allocated for the
                                    //   string.
  // Copy the string character by character.
  for (int i = 0; i < currentSize; i++) {
    theString[i] = S.theString[i];
  }
  theString[currentSize] = '\0'; // add the end of string character.
  return (*this);                // "this" is the reserved word of C++
                                 // to refer to the implicit
                                 // parameter
                                 //   object.
}

//PRE:
//POST: returns if the string is filled with any charater
bool MyString::empty() {
  bool rv = false;
  if(currentSize == 0) {
    rv = true;
  }
  return rv;
}

// Pre : this object is defined
// Post: we make a copy of MyString
MyString::MyString(const MyString & S) {
  currentMax = S.currentMax;        // copy the values
                                    //of the static member
  currentSize = S.currentSize; //   data objects
  theString = new char[currentMax]; // get space allocated for the
                                    //   string.
  // Copy the string character by character.
  for (int i = 0; i < currentSize; i++) {
    theString[i] = S.theString[i];
  }
  theString[currentSize] = '\0'; // add the end of string character.
}

// Output member functions
// PRE: This MyString object is defined and satisfies the CI.
// POST: OS contains a newline followed by the values of currentMax,
//       currentSize and the characters in theString followed by a
//       newline.
void MyString::debugPrint () const  {
  cout << endl;
  cout << "currentMax = " << currentMax << "; "
       << "currentSize = " << currentSize << "; "
       << "current string = ";
  for (int i = 0; i < currentSize; i++) {
    cout << "(" << i << ", *" << theString[i] << "*) ";
  }
  cout << "(" << currentSize;
  if (theString[currentSize] == '\0') {
    cout << ", *EOS*)";
  }
  else {
    cout << ", *NOT EOS*)";
  }
  cout << endl;
}

// PRE: This MyString object is defined and satisfies the CI.
// POST: OS contains the characters in this string.
void MyString::print () const {
  cout << theString;
}

// PRE: This MyString object is defined with values
//       currentMax = M, currentSize = S, and satisfies the CI.
// POST: ch is defined.
//       theString[0]..theString[S-1] are the same as before.
//       theString[S] = ch
//       theString[S+1] = '\0'
//       The result object satisfies the CI.
void MyString::add(char ch) {

  // Check for space for another character
  if (currentMax == currentSize){
    setNewMaxSize(2*(currentMax + 1));
  }
  // ASSERT: There is space for a new character in theString
  // assigning ch to its correct place
  theString[currentSize] = ch;
  // showing we added to the size
  currentSize++;
  // adding end of string character to the end of the array
  theString[currentSize] = '\0';


}

// Pre : char * ch is the string of characters to be added
// Post: we will call the add function on each of the characters
void MyString::addString(char * ch){
  int index = 0;
  int size = getCharArraySize(ch);
  if (currentMax <= (currentMax + size)){
    //ASSERT: this will make enough space for new string making the prog
    //        more efficent with less new calls
    int new_size = currentMax + size;
    setNewMaxSize(new_size);
  }
  while (ch[index] != '\0'){
    //add will not make a new call
    add(ch[index]);
    index++;
  }
}

//PRE: takes a int size, size to be set to the string, does not include int
//     '\0' characters, must be positive
//POST: makes the string able to hold more charaters
//throw(Exception((char *)"MYSTRING: INDEX GIVEN < 0"));
void MyString::setNewMaxSize(int new_size) {
  // Creating space for more characters
  if(new_size <= 0) {
    throw(Exception((char *)"MYSTRING: INDEX GIVEN < 0"));
  } else {
    char * tempString = theString;
    theString = new char[new_size + 1];
    // copying from temporary string to our actual string
    for (int character_index = 0; character_index < currentSize;
       character_index++){
       theString[character_index] = tempString[character_index];
    }
    // deleting temporary so we dont have memory leaks
    delete [] tempString;
    currentMax = (new_size + 1);
  }

}

//PRE:  @param char * ch, the sting must be ended with at least one char
//      which is the '\0' charater
//POST: @returns the length of the string
int MyString::getCharArraySize(char * char_array) {

  int size = 0;
  char ch = char_array[size];
  while(ch != '\0') {
    size++;
    ch = char_array[size];
  }
  size++;
  return size;
}

// Pre :
// Post: we will return theString
char * MyString::getString(){
  return (theString);
}

// Pre :
// Post: we will return a deep copy of theString, allocates the proper amount
//       memory
char * MyString::getStringDeepCopy(){
  char * newString = new char[currentMax + 1];
  for(int i = 0; currentMax + 1 > i; i++ ) {
    newString[i] = theString[i];
  }
  return newString;
}

// Pre : MyString ch is the MyString object we want to add
// Post: we will cycle through all the characters of ch
//       and add them to our current object
void MyString::addMyString(MyString ch){
  int index = 0;
  while (ch.requestindex(index) != '\0'){
    add(ch.requestindex(index));
    index++;
  }
}



//PRE: takes a init my string object
//POST: returns true if the two strings are the same, false if they are
//      differant
bool MyString::isEqual(MyString s2) {
  bool rv = true;
  if(s2.getCurrentSize() == currentSize) {
    //ASSERT: the strings have the same length
    for(int i = 0; i < currentSize; i++) {
      if(rv == true) {
        //ASSERT: rv is true
        rv = (s2.requestindex(i) == theString[i]);//IF false will skip loop
      }
    }
  }else{
    rv = false;
  }
  return(rv);
}

// Pre : @param index, index must be positive and be in bounds of the
//              sting.
// Post: @return returns the index at the index specifed, str[index]
//throw(Exception((char *)"MYSTRING: INDEX OUT OF BOUNDS"));
char MyString::requestindex(int index){
  if(index >= 0 && index <= currentSize) {
    return (theString[index]);
  } else {
    throw(Exception((char *)"MYSTRING: INDEX OUT OF BOUNDS"));
  }

}

//PRE: s must be initalized
//POST: return int current size
int MyString::getCurrentSize() {
  return(currentSize);
}

// Pre : this object is declared
// Post: we return the string back to defaults
void MyString::resetString(){
  delete [] theString;
  // we can no longer hold any items
  currentMax = 0;
  // we need room for an end of string character
  theString = new char[currentMax + 1];
  // adding the end of string character
  theString[0] = '\0';
  // currently have no items
  currentSize = 0;
}

ostream & operator <<(ostream & str, const MyString & M){
  str << M.theString;
  return (str);
}

ostream & operator <<(ostream & str, const MyString * M){
  str << M->theString;
  return (str);
}


//PRE: inited mystring, ch is the character you want the fuction to split the
//     string up into
//POST:returns a linked list object of of string split by the var given so if
//     given, Thomas Peacemaker with ch = " " it will return ["Thomas",
//     "Peacemaker"],
LList<MyString> MyString::split(char ch) {
     LList<MyString> list;
     MyString current = MyString();

     for(int i = 0; i < currentSize + 1; i++) {
      if(i == 0 && requestindex(i) == ch) {
         //cout << "here" << endl;
      } else {
        if(requestindex(i) == ch || i == currentSize) {
             MyString temp = MyString(current.getString());
             list.addBack(temp);
             current.resetString();
        } else {
             current.add(requestindex(i));
        }
      }
      //cout << requestindex(i) << ' ' << "Space"<< endl;

     }
     return list;
}

// Pre : This object is defined
// Post: returns all memory to the system
MyString::~MyString(){
  delete [] theString;
}
