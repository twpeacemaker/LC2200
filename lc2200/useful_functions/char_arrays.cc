#include "char_arrays.h"
#include "../constants.h"
#include "../Exception.h"


// Pre : @param char * firstArray
//       @param char * secondArray
// Post: returns true if the two arrays are =
bool compareCharArray(char * firstArray, char * secondArray){
  bool match  = true;
  int index = 0;
  while(match &&
        firstArray[index] != '\0' &&
        secondArray[index] != '\0')
  {
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


// Pre : @param char character, takes a charater
// Post: @returns an intager
int char_to_integer(char character){

  int ascii_value = (int)(character);
  int ascii_baseline;

  if (ascii_value > (int)('F') || ascii_value < (int)('0')){
    throw(Exception((char *)"ERROR: INVALID INPUT"));
  }else{
    if (ascii_value > (int)('9')){
      // convert the value of A into an ascii value integer
      ascii_baseline = (int)('A');
      //  pad the ascii_baseline with our Apadding
      ascii_baseline -= AOFFSET;
    }else{
      ascii_baseline = (int)('0');
    }
    // ASSERT:  determined the nature of ascii_value
    //         and aligned
    int updated_value = ascii_value - ascii_baseline;
    // ASSERT: updated_value is now the converted value of
    //       character
    // from character to integer
    return (updated_value);
  }
}

// Pre:  @param char * characters takes an array of characters to be converted
//       to an int
// Post: @return the intager, represented by the array
int array_to_int(char * characters){
  // variables for the array hunting
  int index = 0;
  char current_char = characters[index];
  int updated_value = 0;
  int current_int = 0;
  bool negative   = false;
  while (current_char != '\0'){
    if(current_char != '-'){
      //  have not found a end of string character
      current_int = char_to_integer(current_char);
      if (current_int <= (int)('9') && current_int >= (int)('0')){
	       throw(Exception((char *)"Invalid character input"));
      }
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
