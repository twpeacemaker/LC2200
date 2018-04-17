#ifndef INCLUDED_BIT_M
#define INCLUDED_BIT_M

#include "../Exception.h"
#include "../constants.h"
#include <iostream>
using namespace std;

//PRE:  @param int left_index: the left most index of the sub-bit
//      @param int right_index: the right most index of the sub-bit
//POST: returns the mask with ones from the left index to the right index
//      if there is no errors, if the function throws an error the function
//      return garbage data;
//throw(Exception((char *)"ERROR: The left index must be larger than the right
//index."));
//throw(Exception((char *)"ERROR: The left index if greater than the word
//size."));
//throw(Exception((char *)"ERROR: The right index is less than 0."));
uint getMaskBit(int left_index, int right_index);

//PRE:  @param int num: # which you want to get a sub-bit for
//      @param int left_index: [right_index-0]the left most index of the sub-bit
//      @param int right_index:[31-left_index]the right most index of the
//             sub-bit
//      the left and right indexes are inclusive and this function will not
//      changen int num.
//      @param bool check_for_neg (optional), tells the program to check for neg
//POST: will return the sub-bit of int num from left index to right index
//      inclusive if no errors, if errors will return garbage data
//throw(Exception((char *)"ERROR: The left index must be larger than the right
//index."));
//throw(Exception((char *)"ERROR: The left index if greater than the word
//size."));
//throw(Exception((char *)"ERROR: The right index is less than 0."));
uint getBits(uint num, int left_index, int right_index,
             bool check_for_neg = false);


//PRE:  @param int byte_num, [1-4]
//POST: returns the mask where ones are everywhere other than the byte_num
//      specifed s
//throw(Exception((char *)"ERROR: byte_num must be less than the length of a
//byte." ));
uint getByteMask(int byte_num);

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
uint insertByte (uint num, uint to_insert, int byte_num);

//PRE: uint num, the number that is being tested to be neg
//     int left_index, the left most index
//POST:returns the correct number with negitive accounted for
uint accountForNeg(uint num, int left_index);

//PRE: @param uint num: the number to be inserted to
//     @param uint to_insert: the number being inserted, should only be a byte
//            long
//     @param uint start_byte, the byte number you want the intager to begin at
//    @param uint  end_byte, the byte number you want the intager to begin at
//POST: @return, returns the word with the byte inserted
uint insertNum(uint num, uint to_insert, uint start_byte, uint end_byte);

//PRE: @param uint num, the number to extract the byte form
//     @param uint byte_num, the byte number to be extracted
//POST:
uint getByte(uint num, uint byte_num);


//PRE: uint num, the number to get a subnum from
//     uint start_byte, the very leftmost byte to be included into the num
//     uint end_byte, the very rightmost byte to be included into the num
//POST:returns the sub number
uint getNum(uint num, uint start_byte, uint end_byte);


#endif
