#include <iostream>
#include <stdio.h>
#include "MyString.h"
#include "LList.h"

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
  maxIntSize = 100;
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
  maxIntSize = 100;
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
    // Creating space for more characters
    char * tempString = theString;
    // Double space (saves a lot of time in the future)
    theString = new char[2*(currentMax + 1)];
    // copying from temporary string to our actual string
    for (int character_index = 0; character_index < currentSize;
	 character_index++){
      theString[character_index] = tempString[character_index];
    }
    // deleting temporary so we dont have memory leaks
    delete [] tempString;
    currentMax = 2 * (currentMax + 1);

  }

  // ASSERT: There is space for a new character in theString
  // assigning ch to its correct place
 //cerr << "info: "<< currentSize << " "<< currentMax << " "<< ch << endl;

  theString[currentSize] = ch;
  //cerr << "Adding after " << ch << endl;

  // showing we added to the size
  currentSize++;
  // adding end of string character to the end of the array
  theString[currentSize] = '\0';


}

// Pre : char * ch is the string of characters to be added
// Post: we will call the add function on each of the characters
void MyString::addString(char * ch){
  int index = 0;
  while (ch[index] != '\0'){
    add(ch[index]);
    index++;
  }
}

// Pre :
// Post: we will return theString
char * MyString::getString(){
  return (theString);
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

// Pre : the integer is less then or equal to maxIntSize
//        digits long
//       this object is defined
// Post: we will convert the integer into a char array
//       we will then add the char array to the mystring
void MyString::addInt(int ch){
  char add_string[maxIntSize];
  sprintf(add_string, "%d", ch);
  int index = 0;
  while (add_string[index] != '\0'){
    add(add_string[index]);
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

// Pre : MyLines object is defined and statisfies the CI
//       requested is an integer
// Post: OS contains the requested index
char MyString::requestindex(int index){
  return (theString[index]);
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
          //cout << requestindex(i) << ' ' << "Space"<< endl;
          if(requestindex(i) == ch || i == currentSize) {
               MyString temp = MyString(current.getString());
               list.addBack(temp);
               current.resetString();
          } else {
               current.add(requestindex(i));
          }
     }
     return list;
}

// Pre : This object is defined
// Post: returns all memory to the system
MyString::~MyString(){
  delete [] theString;
}
