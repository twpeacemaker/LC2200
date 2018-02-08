#include "../constants.h"
#include "bit_manipulation.h"

#include <iostream>
using namespace std;

//PRE:  @param int left_index: the left most index of the sub-bit
//      @param int right_index: the right most index of the sub-bit
//POST: returns the mask with ones from the left index to the right index
//      if there is no errors, if the function throws an error the function
//      return garbage data;
uint getMaskBit(int left_index, int right_index) {
  uint return_value; //Assert: will hold garbage data
  if (left_index < right_index) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: The left index must be larger than the right index." << endl;
  } else if(left_index >= WORD_SIZE) {
    ///Assert: error catch & will return garbage data
    cerr << "ERROR: The left index if greater than the word size." << endl;
  } else if(right_index < 0) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: The right index is less than 0." << endl;
  } else {
    int size_of = (left_index - right_index) + 1;;
    //Assert: (1) must be added because the numbers are inclusive
    uint template_mask = 0x00000001;
    uint created_mask  = 0;
    //Assert: mask is all 0 till the last byte then it is 0001
    for (int i = 0; i < size_of; i++) {
      created_mask  = created_mask + template_mask;
      template_mask = template_mask << 1;
    }
    return_value = created_mask << right_index;
    //Assert: will return the mask
  }
  return (return_value);
}

//PRE:  @param int num: # which you want to get a sub-bit for
//      @param int left_index: [right_index-0]the left most index of the sub-bit
//      @param int right_index:[31-left_index]the right most index of the
//             sub-bit
//      the left and right indexes are inclusive and this function will not
//      changen int num.
//POST: will return the sub-bit of int num from left index to right index
//      inclusive if no errors, if errors will return garbage data
uint getBits(uint num, int left_index, int right_index) {
    uint return_value; //Assert: will hold garbage data
    if (left_index < right_index) {
      //Assert: error catch & will return garbage data
      cerr << "ERROR: The left index must be larger than the right index." << endl;
    } else if(left_index >= WORD_SIZE) {
      ///Assert: error catch & will return garbage data
      cerr << "ERROR: The left index if greater than the word size." << endl;
    } else if(right_index < 0) {
      //Assert: error catch & will return garbage data
      cerr << "ERROR: The right index is less than 0." << endl;
    } else {
      //Assert: the left index is greater than the right
      uint mask = getMaskBit(left_index, right_index);
      uint new_num = (mask & num) >> right_index;
      //printf("Created Mask: %#08x \n" , mask);
      //printf("Num in get bits: %#08x \n" , new_num);
      int new_num_size = left_index - right_index;
      //printf("new_num_size: %d \n" , new_num_size);
      int remove_leading_one_mask = getMaskBit(new_num_size, 0);
      //printf("remove_leading_one_mask: %#08x \n" , remove_leading_one_mask);
      return_value = remove_leading_one_mask & new_num;
      //printf("Num: %#08x \n" , return_value);
      //return_value = new_num;

    }

    return (return_value);
}


//PRE:  @param int byte_num, [1-4]
//POST: returns the mask where ones are everywhere other than the byte_num
//      specifed s
uint getByteMask(int byte_num) {
  uint return_value;
  if (BYTES_IN_WORD <= byte_num) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: byte_num must be less than the length of a byte." << endl;
  } else {
    uint mask_template = 0xFFFFFFFF;
    uint mask_byte_num = 0xFF000000 >> ((byte_num) * BITS_IN_BYTES);
    return_value = mask_template ^ mask_byte_num;
  }
  return return_value;
}

//PRE: @param int num: the number to be inserted to
//     @param int to_insert: the number being inserted, should only be a byte
//            long
//     @param int byte_num: [0-7]the byte number that to_insert will be
//            inserted to
//POST: return num[new_num] where num is replaced by the to_insert
uint insertByte (uint num, uint to_insert, int byte_num) {
  uint return_value;
  if (to_insert > MAX_BYTE_SIZE) {
    cout << to_insert << " > " << MAX_BYTE_SIZE << endl;
    //printf("Created Mask: %#08x \n" , to_insert);
    //Assert: error catch & will return garbage data
    cerr << "ERROR: to_insert must be less than the length of a byte." << endl;
  } else if (BYTES_IN_WORD < byte_num) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: byte_num must be less than the length of a byte." << endl;
  } else {
      uint mask = getByteMask(byte_num);
      uint temp = num & mask;
      uint shift = ((BYTES_IN_WORD-(byte_num + 1)) * BITS_IN_BYTES);
      uint shifted_num2 = to_insert << shift;
      return_value = shifted_num2 | temp;
  }
  return(return_value);
}
