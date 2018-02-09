#ifndef INCLUDED_CHAR_ARRAYS
#define INCLUDED_CHAR_ARRAYS

#include "../constants.h"
#include "../Exception.h"

// Pre : @param char * firstArray
//       @param char * secondArray
// Post: returns true if the two arrays are =
bool compareCharArray(char * firstArray, char * secondArray);

// Pre : @param char character, takes a charater
// Post: @returns an intager
int charToInteger(char character);

// Pre:  @param char * characters takes an array of characters to be converted
//       to an int
// Post: @return the intager, represented by the array
int arrayToInt(char * characters);

//PRE:  char c any character
//POST: @return bool true iff the characer is a number
bool isDigit( char c );


#endif
