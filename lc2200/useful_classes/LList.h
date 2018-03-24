#ifndef INCLUDED_LList
#define INCLUDED_LList
//@Author: Thomas Peacemaker

#include <iostream>      // ostream used
#include "LNode.h"
#include "../Exception.h"

using namespace std;

template <class T>
class LList {

  // Class Invariant (CI): This object contains a defined pointer f
  // that points to the first LNode and defined pointer r that points to
  // the last LNode

  // NOTE: We will sometimes also refer to the elements of the list as
  // f(0), f(1),..., f(n-1), where f(0) is the LNode at the front of
  // the list.

 protected:
  LNode<T> * front;   //is the pointer that is pointed to the head of the LList
  LNode<T> * back;    //is the pointer that is pointed to the rear of the LList
  int n;              //is defined as the number of items in the LList

  // PRE: N is defined. This object is defined and n > N.
  // POST: RV = the T stored in the f(N).
  LNode<T> * getNthNode(int N) const{
    int count = 0;
    LNode<T> * temp = front;  // temp is an alias for front.
    // ASSERT: temp points to the node f(0).
    while (count < N) {
      temp = temp->getNext();
      count++;
      // ASSERT: temp points to the node f(count).
    }
    // ASSERT: count = N. Therefore, temp points to the node f(N).
    return (temp);
  }
 public:
  // ========================================
  // constructors
  // ========================================

  // default constructor
  // PRE:
  // POST: This object is defined with f = NULL and n = 0.
  LList(){
    front = NULL;
    back = NULL;
    n = 0;
  }

  // copy constructor
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the LNodes in f being physically
  //         distinct from the LNodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  LList(const LList & L){
    front = NULL;
    back = NULL;
    n = 0;
    for (int index = L.n-1; index >= 0; index--) {
      addFront (L.getNth(index));
      // ASSERT: f = L.f(index),L.f(index+1),...,L.f(L.n-1)
      //         n = (L.n-1) - index + 1.
    }
    // ASSERT: f = L.f(0),...,L.f(L.n-1).
    //
  }

  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  //       Thus, f = L.f, with all the LNodes in f being physically
  //         distinct from the LNodes of L.
  //       n = L.n
  //       Note here that L is being passed by reference to avoid the
  //        shallow copy of the actual parameter being passed as L. We
  //        indicate that L does not change with the keyword const.
  LList<T> & operator= (const LList<T> & L){
    // First need to delete any nodes that this LList object
    // contains.
    // ADD code here to do so.
    for (int index = L.n-1; index >= 0; index--) {
      addFront (L.getNth(index));
      // ASSERT: f = L.f(index),L.f(index+1),...,L.f(L.n-1)
      //         n = (L.n-1) - index + 1.
    }
    // ASSERT: f = L.f(0),...,L.f(L.n-1).
    //         n = L.n.
    return (*this);

  }

  // ========================================
  //       accessor functions
  // ========================================

  // PRE: This object is defined.
  // POST: RV = n
  int getSize () const{
    return (n);
  }

  // PRE: This object is defined and n > 0.
  // POST: RV = the T stored in f(0).
  T getFront () const {
    return (front->getData());
  }

  // Pre :
  // Post:
  T getBack () const {
    return (back->getData());
  }

  // PRE: N is defined. This object is defined and n > N.
  // POST: RV = the T stored in the f(N).
  T getNth (int N) const{
    int count = 0;
    LNode<T> * temp = front;  // temp is an alias for front.
    // ASSERT: temp points to the node f(0).
    while (count < N) {
      temp = temp->getNext();
      count++;
      // ASSERT: temp points to the node f(count).
    }
    // ASSERT: count = N. Therefore, temp points to the node f(N).
    return (temp->getData());
  }

  // PRE: N is defined. This object is defined. n > N.
  // POST: This object is defined and n = (pre)n - 1.
  //       f = (pre)f(0),...,(pre)f(N-1),(pre)f(N+1),...,(pre)f((pre)n - 2).
  //throw(Exception((char *)"@LIST: N > NUMBER OF NODES"));
  void deleteNth (int N){
    if(N < n) {
      if(N == 0) {
         deleteFront();
      } else if(N == (n - 1)) {
         deleteBack();
      } else {
         int count = 0;
          LNode<T> * temp = front;  // temp is an alias for front.
          // ASSERT: temp points to the node f(0).
          while (count < N) {
             temp = temp->getNext();
              count++;
               // ASSERT: temp points to the node f(count).
          }
        	//ASSERT: not the fromnt or the back so length >= 3

        	LNode<T> * prevNode = temp->getPrev();
        	LNode<T> * nextNode = temp->getNext();
        	prevNode->setNext(nextNode); //
        	nextNode->setPrev(prevNode);
          temp->setNext(NULL);
          temp->setPrev(NULL);
          delete (temp);
          n--;

      }
    } else {
      //ASSERT: the user attempted N < n, throws error
      throw(Exception((char *)"@LIST: N > NUMBER OF NODES"));
    }

  }

  // ========================================
  // modifier functions
  // ========================================

  // PRE: num = v is defined. This object is defined.
  // POST: This object is defined with n = (pre)n + 1. An LNode
  //       object t contains the T data v.
  //       f = t, (pre)f(0),(pre)f(1),...,(pre)f((pre)n).
  //       NOTE: (pre) is an informal mechanism of referring to the
  //             state of the variable in the PRE state of the function.
  void addFront (T num){
    LNode<T> * tempNode = new LNode<T> (num);
    // ASSERT: tempnode points to inNode object t containing v.
    if(front == NULL && back == NULL) {
      front = tempNode;
      back  = tempNode;
    } else {
      tempNode->setNext(front);
      front->setPrev(tempNode);
      //ASSERT: back = front
      front = tempNode;
    }
    n++;
  }

  //PRE: takes a T * num that will be inserted after the int nth given
  //      nth must be > 0  and less than n + 1
  //POST:inserts the node after the given nth node
  //throw(Exception((char *) "@LLIST: COULD NOT BE INSERTED TO NTH" ));
  void insertAfterNth(int nth, T num) {
    if(nth == (n - 1)) {
      //ASSERT: the user wants the add to the end of the list
      addBack(num);
    } else if(nth >= 0 && nth < n && back != NULL) {
      //ASSERT:front != null because n < 0
      //ASSERT:nth is not the end of the list because nth < n
      LNode<T> * tempNode = new LNode<T> (num);
      LNode<T> * nth_node = getNthNode(nth);
      LNode<T> * next_node = nth_node->getNext();
      nth_node->setNext(tempNode); //nth =>
      tempNode->setPrev(nth_node); // nth <= num
      tempNode->setNext(next_node); // num => num
      next_node->setPrev(tempNode);
      n++;
    } else {
      throw(Exception((char *) "@LLIST: COULD NOT BE INSERTED TO NTH" ));
    }


  }

  // Pre : item is what we want to add to the list
  //       this object is defined
  // Post: this object now containts item at the back of the list
  //       if this object was empty we simply added to the front
  //       we update the n
  void addBack(T item){
    if(n < 1) {
      //ASSERT: list is empty
      addFront(item);
    } else {
      LNode<T> * tempNode = new LNode<T> (item);
      tempNode->setPrev(back);
      back->setNext(tempNode);
      tempNode->setNextNull();
      back = tempNode;
      n++;
    }
  }




  // PRE: This object is defined. n > 0.
  // POST: This object is defined and n = (pre)n - 1.
  //       f = (pre)f(1), (pre)f(2),..., (pre)f((pre)n-2).
  //throw(Exception((char *) "@LLIST: DELETE ITEMS THAT ARE NOT IN THE LIST" ));
  void deleteFront (){
    LNode<T> * temp = front;// temp is an alias for the first node in this list.
    if (n == 1) {
      front = NULL;
      back = NULL;
      n--;
      // ASSERT: f = (pre)f(1),...,(pre)f((pre)n-2).
      temp->setNext(NULL);
      temp->setPrev(NULL);
      delete (temp); // deallocate storage for the ;d node.
    } else if( n > 1) {
      front = front->getNext();
      front->setPrev(NULL);
      n--;
      // ASSERT: f = (pre)f(1),...,(pre)f((pre)n-2).
      temp->setNext(NULL);
      temp->setPrev(NULL);
      delete (temp); // deallocate storage for the deleted node.
    } else {
      throw(Exception((char *) "@LLIST: DELETE ITEMS THAT ARE NOT IN THE LIST" ));
    }
    // ASSERT: f = (pre)f(1),...,(pre)f(n-1).

  }

  // PRE: This object is defined. n > 0.
  // POST: This object is defined and n = n - 1(after).
  //throw(Exception((char *) "@LLIST: DELETE ITEMS THAT ARE NOT IN THE LIST" ));
  void deleteBack(){
    LNode<T> * temp = back;
    if (n == 1) {
      front = NULL;
      back = NULL;
    } else if(n > 1){
      back = back->getPrev();
      if(n == 2) {
	       front = back;
         front->setNext(NULL);
         front->setPrev(NULL);
      } else {
	       back->setNextNull();
      }
      n--;
      temp->setNext(NULL);
      delete (temp);
    } else  {
      throw(Exception((char *) "@LLIST: DELETE ITEMS THAT ARE NOT IN THE LIST" ));
    }

  }

  // ========================================
  //     Input/Output
  // ========================================

  // PRE: L is defined.
  // POST: str contains L.f(0),...,L.f(L.n-1).
  //       NOTE: Here L.f refers to the elements of the LList object L.
  friend ostream & operator<< (ostream & str, const LList<T> & L){
    for (int index = 0; index < L.n; index++) {
      str << L.getNth(index) << ", ";
      // ASSERT: str contains L.f(0), L.f(1), ..., L.f(index),
    }
    return (str);  // The stream is modified by thie operation. So, we
                   // need to return the modified stream
  }

  // ========================================
  // destructor
  // ========================================

  // PRE: This object is defined.
  // POST: This object has no elements. f = NULL and n = 0.
  //       All space allocated for this object is deallocated.
  ~LList(){
    delete front;
    // ASSERT: f is empty.
    n = 0;
    front = NULL;
    back = NULL;
  }


};
#endif
