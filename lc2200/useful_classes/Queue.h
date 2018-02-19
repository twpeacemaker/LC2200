#ifndef INCLUDED_Queue
#define INCLUDED_Queue

//NOTE: this is not included to the simulator, still in DEV

#include <iostream>
using namespace std;
#include "LList.h"

template <class T>
class Queue : public LList<T> {

  // Class Invariant (CI): This object contains a defined pointer f
  // that points to the first LNode and defined pointer r, nodes enter from
  // the queue from the back and exit from the fron, first in first out
  // items may be deleted from any place.

private:

public:

  //PRE:
  //POST:
  Queue() {
    // called but not new data to init
  };

  //
  //PRE:  takes a T item,
  //POST: adds the item to the end of the LList
  void enqueue(T item) {
    LList<T>::addBack(item);
  };

  //PRE:  LList<T> must hold a item at them beginning of the LList<T>
  //POST: removes the T from the beginning of the queue
  void dequeue() {
    LList<T>::deleteFront();
  };

  //PRE:  n < lenth of queue
  //POST: returns the T object at LList<T>[n]
  T getNthQueued(int index) const {
    return LList<T>::getNth(index);
  };

  //PRE:  n < length of queue
  //POST: deletes the nth term in the quue
  void deleteNthQueued(int index) {
    LList<T>::deleteNth(index);
  };

  // PRE: This object is defined.
  // POST: RV = n
  int getQueueSize() {
    return LList<T>::getSize();
  };

  ~Queue(){
    //all data is destucted from the LList in that class
  };


};
#endif
