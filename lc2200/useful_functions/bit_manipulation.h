#ifndef INCLUDED_BIT_M
#define INCLUDED_BIT_M

#include "../constants.h"

//PRE:  @param int left_index: the left most index of the sub-bit
//      @param int right_index: the right most index of the sub-bit
//POST: returns the mask with ones from the left index to the right index
//      if there is no errors, if the function throws an error the function
//      return garbage data;
int getMaskBit(int left_index, int right_index);

//PRE:  @param int num: # which you want to get a sub-bit for
//      @param int left_index: [right_index-0]the left most index of the sub-bit
//      @param int right_index:[31-left_index]the right most index of the
//             sub-bit
//      the left and right indexes are inclusive and this function will not
//      changen int num.
//POST: will return the sub-bit of int num from left index to right index
//      inclusive if no errors, if errors will return garbage data
int getBits(int num, int left_index, int right_index);


//PRE:  @param int byte_num, [1-4]
//POST: returns the mask where ones are everywhere other than the byte_num
//      specifed s
int getByteMask(int byte_num);

//PRE: @param int num: the number to be inserted to
//     @param int to_insert: the number being inserted, should only be a byte
//            long
//     @param int byte_num: [0-7]the byte number that to_insert will be
//            inserted to
//POST: return num[new_num] where num is replaced by the to_insert
int insertByte (int num, int to_insert, int byte_num);


#endif