#ifndef INCLUDED_LNode
#define INCLUDED_LNode
//Author: Thomas Peacemaker

#include <iostream>
using namespace std;

template <class T>
class LNode {

  // Class Invariant (CI): This object is template that holds the class given as
  // T denoted as n. LNode denoted by c will hold a pointer denoted by p which
  // points to the LNode that precedes it and will hold a pointer denoted by a,
  // that will hold a LNode that is after c.

 private:
  T data;               // stores the data item in this node denoted by n.
  LNode<T> * nextItem;  // p, will point the the node preceding c (p<-c)
  LNode<T> * prevItem;  // a, will point the the node after (c->a)

 public:

  // ========================================
  // constructors
  // ========================================

  // default constructor
  // PRE:
  // POST: This object is defined with n = 0 and p = NULL.
  LNode(){
    nextItem = NULL;
    prevItem = NULL;
  }

  // PRE: num = v is defined.
  // POST: This object is defined with n = v, and p = NULL.
  LNode (T item){
    data = item;
    nextItem = NULL;
    prevItem = NULL;
  }

  // ========================================
  //       accessor functions
  // ========================================

  // PRE: This object is defined.
  // POST: RV = n.
  T getData () {
    return (data);
  }

  // PRE: This object is defined.
  // POST: RV = p.
  LNode<T> * getNext () const{
    return (nextItem);
  }

  // Pre : this object is defined
  // POST: RV = a.
  LNode<T> * getPrev () const{
    return (prevItem);
  }

  // ========================================
  // modifier functions
  // ========================================

  // PRE: This object is defined. item denoted by v, is defined.
  // POST: This object is defined and n = v.
  void setData (T item){
    data = item;
  }

  // PRE: This object is defined. next = x is defined.
  // POST: This object is defined and a = x.
  void setNext (LNode<T> * next){
    nextItem = next;
  }

  // PRE: This object is defined. prev = x is defined.
  // POST: This object is defined and p = x.
  void setPrev (LNode<T> * prev){
    prevItem = prev;
  }

  // PRE:
  // POST: This object is defined and a = NULL.
  void setNextNull (){
    nextItem = NULL;
  }

  // Pre :
  // POST: This object is defined and p = x.
  void setPrevNull (){
    prevItem = NULL;
  }

  // ========================================
  // destructor functions
  // ========================================

  // PRE: This object is defined.
  // POST: The object that next pointed to is destroyed.
  ~LNode() {
    if(nextItem != NULL) {
      delete (nextItem);
      nextItem = NULL;
    }
  }
};
#endif
