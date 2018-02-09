#include "char_arrays.h"
#include "../constants.h"
#include "../Exception.h"


// Pre : @param char * firstArray
//       @param char * secondArray
// Post: returns true if the two arrays are =
bool compareCharArray(char * firstArray, char * secondArray){
  bool match  = true;
  int index = 0;
  while(match && firstArray[index] != '\0' && secondArray[index] != '\0') {
    if(firstArray[index] != secondArray[index]){
       match = false;
    }
    index++;
  }
  if (firstArray[index] != '\0' || secondArray[index] != '\0'){
    match = false;
  }
  return (match);
}

//PRE:  char c any character
//POST: @return bool true iff the characer is a number
bool isDigit( char c ) {
  return ( '0' <= c && c <= '9');
}

// Pre : @param char character, takes a charater
// Post: @returns an intager verion of the character 
//throw(Exception((char *)"ERROR: INVALID INPUT"));
int charToInteger(char c){
  int ascii_value = (int)(c);
  int baseline;
  if (!isDigit(c)){
    throw(Exception((char *)"ERROR: INVALID INPUT"));
  }
  baseline = (int)('0');
  // ASSERT:  determined the nature of ascii_value
  //         and aligned
  int rv = ascii_value - baseline;
  // ASSERT: updated_value is now the converted value of
  //       character
  // from character to integer
  return (rv);
}

// Pre:  @param char * characters takes an array of characters to be converted
//       to an int
// Post: @return the intager, represented by the array
int arrayToInt(char * characters){
  // variables for the array hunting
  int index = 0;
  char current_char = characters[index];
  int updated_value = 0;
  int current_int = 0;
  bool negative   = false;
  while (current_char != '\0'){
    if(current_char != '-'){
      //  have not found a end of string character
      current_int = charToInteger(current_char);
      // update the value
      updated_value = (updated_value * 10) + current_int;
    }else{
      negative = true;
    }
    index++;
    current_char = characters[index];
  }
  if(negative){
    updated_value = updated_value * -1;
  }
  return (updated_value);
}
