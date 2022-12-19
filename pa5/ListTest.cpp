// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA5
//  ListTest.cpp
//  This file contains code for different test cases in List ADT.
// -----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


using namespace std;

int main(){
List A;
  List B;

    if (A.length() != 0)
        cout << "emptysize error1" << endl;
    
    cout << "empty size test " << A << endl;

    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);

    if (A.length() != 5) {
      cout << "insert after e1" << endl;
    }

    cout << "insert after test " << A << endl;

    A.clear();
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);
    if (A.length() != 5) {
        cout << "insert before error 1" << endl;
    }
    cout << "insert before test 1 " << A << endl;

    A.clear();
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);

    A.movePrev();
    A.eraseAfter();
    if (A.length() != 4)
      cout << "erase after error 1" << endl;
    cout << "erase after test 1 " << A << endl;

    A.findPrev(2);
    A.eraseAfter();  
    if (A.length() != 3)
      cout << "erase after error 2" << endl;
    cout << "erase after test 2 " << A << endl;

    A.clear();
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);

    A.moveNext();
    A.eraseBefore();
    if (A.length() != 4)
      cout << "erase before error 1" << endl;
    cout << "erase before test 1 " << A << endl;

    A.findNext(2);
    A.eraseBefore();    
    if (A.length() != 3)
      cout << "erase before error 2" << endl;
    cout << "erase before test 2 " << A << endl;

    A.clear();
    List C;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    C = A.concat(B);
    if (C.length() != 6)
        cout << "concat error 1" << endl;
    cout << "Concat test! " << C << endl;
    
    A.clear();
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(1);
    cout << "Cleanup size test" << endl;
    A.cleanup();
    if (A.length() != 3)
      cout << "cleanup error 1" << endl;
    cout << A << endl;

    cout << A.length() << endl;  // len
    cout << A.front() << endl;
    cout << A.back() << endl;
    cout << A.position() << endl;

    cout << 118 << A << endl;
    A.moveFront();
    cout << A.peekNext() << endl;

    A.moveBack();
    cout << A.peekPrev() << endl;

    A.moveFront();
    A.moveNext();
    A.insertBefore(54);
    A.insertAfter(43);
    A.setAfter(3);
    A.setBefore(7);
    A.movePrev();

    A.findNext(3);
    A.findPrev(3);

    cout << A.equals(B) << endl;
    string box = A.to_string();
    cout << box << endl;
    if (A == B) {
      cout << "hi" << endl;
    }
    else {
      cout << "bye" << endl;
    }

    List Z = A; // copy constructor
    C.moveFront();

    A = B; // operator=()
    if (A == B) {
      cout << "A and B are equal now." << endl;
    }


  A.clear();


    return 0;
}