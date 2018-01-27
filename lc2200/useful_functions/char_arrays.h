#ifndef INCLUDED_CHAR_ARRAYS
#define INCLUDED_CHAR_ARRAYS

// Pre : @param char * firstArray
//       @param char * secondArray
// Post: returns true if the two arrays are =
bool compareCharArray(char * firstArray, char * secondArray);

// Pre : @param char character, takes a charater
// Post: @returns an intager
int char_to_integer(char character);

// Pre:  @param char * characters takes an array of characters to be converted
//       to an int
// Post: @return the intager, represented by the array
int array_to_int(char * characters);

#endif
