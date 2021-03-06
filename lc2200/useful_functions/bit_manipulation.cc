#include "../constants.h"
#include "bit_manipulation.h"
#include "../Exception.h"

#include <iostream>
using namespace std;

//PRE:  @param int left_index: the left most index of the sub-bit
//      @param int right_index: the right most index of the sub-bit
//POST: returns the mask with ones from the left index to the right index
//      if there is no errors, if the function throws an error the function
//      return garbage data;\
//throw(Exception((char *)"ERROR: The left index must be larger than the right
//index."));
//throw(Exception((char *)"ERROR: The left index if greater than the word
//size."));
//throw(Exception((char *)"ERROR: The right index is less than 0."));
uint getMaskBit(int left_index, int right_index) {
  uint return_value; //Assert: will hold garbage data
  if (left_index < right_index) {
    //Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: The left index must be larger than the right index."));
  } else if(left_index > WORD_SIZE) {
    ///Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: The left index if greater than the word size."));
  } else if(right_index < 0) {
    //Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: The right index is less than 0."));
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
//      @param bool check_for_neg optional, tells the program to check for neg
//POST: will return the sub-bit of int num from left index to right index
//      inclusive if no errors, if errors will return garbage data
//throw(Exception((char *)"ERROR: The left index must be larger than the right
//index."));
//throw(Exception((char *)"ERROR: The left index if greater than the word
//size."));
//throw(Exception((char *)"ERROR: The right index is less than 0."));
uint getBits(uint num, int left_index, int right_index,
             bool check_for_neg){
    uint return_value; //Assert: will hold garbage data
    if (left_index < right_index) {
      //Assert: error catch & will return garbage data
      throw(Exception((char *)"ERROR: The left index must be larger than the right index."));
    } else if(left_index >= WORD_SIZE) {
      ///Assert: error catch & will return garbage data
      throw(Exception((char *)"ERROR: The left index if greater than the word size."));
    } else if(right_index < 0) {
      //Assert: error catch & will return garbage data
      throw(Exception((char *)"ERROR: The right index is less than 0."));
    } else {
      //Assert: the left index is greater than the right
      uint mask = getMaskBit(left_index, right_index);
      uint new_num = (mask & num) >> right_index;
      if(check_for_neg) {
        //ASSERT: the optional parameters check_for_neg was given as true,
        //        the function will account for neg numbers
        return_value = accountForNeg(new_num, left_index);
      } else {
        return_value = new_num;
      }
    }

    return (return_value);
}

//PRE: uint num, the number that is being tested to be neg
//     int left_index, the left most index
//POST:returns the correct number with negitive accounted for
uint accountForNeg(uint num, int left_index) {
  int rv;
  uint mask = getMaskBit(left_index, left_index);
  uint test = (mask & num);
  if (test == 0) {
    rv = num;
  } else {
    mask = getMaskBit(WORD_SIZE - 1, left_index + 1);
    rv = (mask | num);
  }
  return rv;
}


//PRE:  @param int byte_num, [1-4]
//POST: returns the mask where ones are everywhere other than the byte_num
//      specifed s
//throw(Exception((char *)"ERROR: byte_num must be less than the length of a
//byte." ));
uint getByteMask(int byte_num) {
  uint return_value;
  if (BYTES_IN_WORD <= byte_num) {
    //Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: byte_num must be less than the length of a byte." ));
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
//throw(Exception((char *)"ERROR: to_insert must be less than the length of
//a byte." ));
//throw(Exception((char *)"ERROR: byte_num must be less than the length of
//a byte." ));
uint insertByte (uint num, uint to_insert, int byte_num) {
  uint return_value;
  if (to_insert > MAX_BYTE_SIZE) {
    cout << to_insert << " > " << MAX_BYTE_SIZE << endl;
    //printf("Created Mask: %#08x \n" , to_insert);
    //Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: to_insert must be less than the length of a byte." ));
  } else if (BYTES_IN_WORD < byte_num) {
    //Assert: error catch & will return garbage data
    throw(Exception((char *)"ERROR: byte_num must be less than the length of a byte." ));
  } else {
      uint mask = getByteMask(byte_num);
      uint temp = num & mask;
      uint shift = ((BYTES_IN_WORD-(byte_num + 1)) * BITS_IN_BYTES);
      uint shifted_num2 = to_insert << shift;
      return_value = shifted_num2 | temp;
  }
  return(return_value);
}
