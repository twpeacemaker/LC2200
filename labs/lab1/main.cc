#include <fstream>
#include <iostream>

using namespace std;

void part1() {
  char ch;
  short s;
  int i;
  long int li;
  long long int lli;

  unsigned char uch;
  unsigned short us;
  unsigned int ui;
  unsigned long int uli;
  unsigned long long int ulli;

  float f;
  double d;

  cout << "Size of a char is " << sizeof(ch) << " byte(s)." << endl;
  cout << "Size of a short is " << sizeof(s) << " byte(s)." << endl;
  cout << "Size of a int is " << sizeof(i) << " byte(s)." << endl;
  cout << "Size of a long int is " << sizeof(li) << " byte(s)." << endl;
  cout << "Size of a long long int is " << sizeof(lli) << " byte(s)." << endl;

  cout << "Size of a unsinged char is " << sizeof(uch) << " byte(s)." << endl;
  cout << "Size of a unsinged short is " << sizeof(us) << " byte(s)." << endl;
  cout << "Size of a unsinged int is " << sizeof(ui) << " byte(s)." << endl;
  cout << "Size of a unsinged long int is " << sizeof(uli) << " byte(s)." << endl;
  cout << "Size of a unsinged long long int is " << sizeof(ulli) << " byte(s)." << endl;

  cout << "Size of a char is " << sizeof(ch) << " byte(s)." << endl;
  cout << "Size of a char is " << sizeof(d) << " byte(s)." << endl;
}

void part2() {
  int num;
  cout << "Type an int: ";
  cin >> num;
  cout << "Normal Cout: " << num << endl;;
  cout << "Hex Cout: " << hex << num << endl;
  cout << "Dec Cout: "<< dec << num << endl;

}

void part3() {
  int X1 = 1;
  float Y1 = 1;
  int X2 = 1;
  int Y2 = 1;
  printf ("The points (%04d, %7.2f) and (%x,  %#08x) are on the given line \n", X1, Y1, X2, Y2);

  int a = 26;
  int b = -47;
  printf ("(%0x, %0x) \n", (unsigned int)a, (unsigned int)b);


  char line [50];
  int n;
  n = sprintf (line, "(%0x, %0x)", (unsigned int)a, (unsigned int)b);

  printf ("[%s] is a string %d chars long \n",line,n);

}

void part6() {
  int num1 = 0xA;
  int num2 = 0xFFFFFFFF;
  printf("Num1: %d, Num2: %d \n", num1, num2);
}

void part7() {
  int num1 = 1;
  int num2 = 3;
  int num4 = ~num1;
  //printf("~Num1: %d \n", ~num1); //~ flips all the bits
  //printf("Num1 & Num2: %d \n", num1 & num2); //& 1&1 = 1; 1&0 = 0; 0&0 = 0
  //printf("Num1 | Num2: %d \n", num1 | num2); //& 1|1 = 1; 1|0 = 1; 0|0 = 0
  //printf("Num1 ^ Num2: %d \n", num1 ^ num2); //& 1^1 = 0; 1^0 = 1; 0^0 = 0
  printf("Num1: %d, Num4: %d \n", num1, num4);
}

void part8() {
    int org    = 1;
    // int mask3  = 0x00000004;
    // int mask7  = 0x00000040;
    // int mask10 = 0x00000200;

    int mask3  = org << 2;
    int mask7  = org << 6;
    int mask10 = org << 9;

    // printf("3rd: %#08x \n",  mask3);
    // printf("7rd: %#08x \n",  mask7);
    // printf("10rd: %#08x \n", mask10);

    int num    = 4;

    printf("3rd: %d \n", num & mask3);
    printf("3rd: %d \n", num & mask7);
    printf("3rd: %d \n", num & mask10);
}

void part9() {
  int num = 0xC0000004;
  printf("Shifted to the left: %x \n" , num << 1);
  printf("Shifted to the right: %x \n", num >> 1);
  printf("Shifted to the right and unsigned int: %x \n", (unsigned int)num >> 1);
  // it all checks out
}

int WORD_SIZE = 32;

//PRE:  @param int left_index: the left most index of the sub-bit
//      @param int right_index: the right most index of the sub-bit
//POST: returns the mask with ones from the left index to the right index
//      if there is no errors, if the function throws an error the function
//      return garbage data;
int getMaskBit(int left_index, int right_index) {
  int return_value; //Assert: will hold garbage data
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
    int template_mask = 0x00000001;
    int created_mask  = 0;
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
int getBits(int num, int left_index, int right_index) {
    int return_value; //Assert: will hold garbage data
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
      int mask = getMaskBit(left_index, right_index);
      //printf("Created Mask: %#08x \n" , mask);
      return_value = (mask & num) >> right_index;
    }
    return (return_value);
}

void part11() {
  //int mask = 0x0000003C;
  int num  = 0xAB0F1234;
  //printf("From Not funtion: %#08x \n" , (mask & num) >> 2);
  int bits = getBits(num, 5, 2);
  printf("From Function: %#08x \n" , bits);
}

int MAX_BYTE_SIZE = 0x000000FF;
int BYTES_IN_WORD = 4;
int BITS_IN_BYTES = 8;

//PRE:  @param int byte_num, [1-4]
//POST: returns the mask where ones are everywhere other than the byte_num
//      specifed s
int getByteMask(int byte_num) {
  int return_value;
  if (BYTES_IN_WORD <= byte_num) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: byte_num must be less than the length of a byte." << endl;
  } else {
    int mask_template = 0xFFFFFFFF;
    int mask_byte_num = 0xFF000000 >> ((byte_num) * BITS_IN_BYTES);
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
int insertByte (int num, int to_insert, int byte_num) {
  int return_value;
  if (to_insert > MAX_BYTE_SIZE) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: to_insert must be less than the length of a byte." << endl;
  } else if (BYTES_IN_WORD < byte_num) {
    //Assert: error catch & will return garbage data
    cerr << "ERROR: byte_num must be less than the length of a byte." << endl;
  } else {
      int mask = getByteMask(byte_num);

      int temp = num & mask;
      int shift = ((BYTES_IN_WORD-(byte_num + 1)) * BITS_IN_BYTES);
      int shifted_num2 = to_insert << shift;
      return_value = shifted_num2 | temp;
      //printf("Mask: %#08x \n" , return_value);
  }
  return(return_value);
}

void part12() {
  int num1 = 0x12345678;
  int num2 = 0x000000AB;
  int new_num = insertByte(num1, num2, 3);
  //printf("New Num: %#08x \n" , new_num);
}

//ask about part 14

void part15() {
  char ch1;char ch2;
  char ch3;char ch4;
  cout << "Type first char : ";  cin >> ch1;
  cout << "Type second char: ";  cin >> ch2;
  cout << "Type third char: ";   cin >> ch3;
  cout << "Type fourth char: ";  cin >> ch4;
  printf("The four characters on input are: '%c', '%c', '%c', '%c'.\n", ch1, ch2, ch3, ch4);
  printf("Their ASCII values in hexadecimal are: '%#0x', '%#0x', '%#0x', '%#0x'.\n", ch1, ch2, ch3, ch4);

  int word = 0x0;
  word = insertByte(word, ch1, 0);
  word = insertByte(word, ch2, 1);
  word = insertByte(word, ch3, 2);
  word = insertByte(word, ch4, 3);
  printf("The 32 bit word in decimal: '%d'.\n", word);
  printf("The 32 bit word as an unsigned decimal: '%d'.\n", (unsigned int)word);
  printf("The 32 bit word as hexadecimal: '%#0x'.\n", word);
}

int main () {
  //part1();
  //part2();
  //part3();
  //part6();
  //part7();
  //part8();
  //part9();
  //part11();
  //part12();
  part15();
  //printf("a: %d \n" , 'a');

}
