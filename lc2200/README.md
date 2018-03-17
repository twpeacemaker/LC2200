#README
#Author:    Thomas Peacemaker
#Professor: Dr. Shende
#Purpose:   to create a low level OS

#Instructions
  To compile:
    make or make Simulator
  To run:
    ./Simulator

#Convention:
  Naming:
    Classes:            CamelCase
    Variables:          snake_case
    Functions/Methods:  lowerCamelCase

#Known Errors/Bugs:
  #BUG when running queue is > 3 and steps have been made. when user trys to
  delete a item not in the front or the back it seg faults, patch is being
  worked on currently. it has been found the error occurs then the
  program attempts
  line 159 prevNode->setNext(nextNode);
  I may be asking questions monday if I can not find the cause
#Test Cases:
  Instructions located in the test/test-cases file
