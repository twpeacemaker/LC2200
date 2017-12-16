#include "LList.h"
//#include "MyString.h"
#include <iostream>
using namespace std;
// Author: Thomas Peacemaker
// Pre : argc is the number of command line arguements passed
//       argv is the command line arguements passed
// Post:
int main(int argc, char * argv[])
{
  LList<int> llist;
  llist.addBack(0);
  llist.addBack(2);
  llist.addBack(3);
  llist.insertAfterNth(0,1);
  cout << llist << endl;
}
