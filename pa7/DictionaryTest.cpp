// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA7
//  DictionaryTest.cpp
//  This file contains code for Dictionary ADT test cases
// -----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   cout << "TESTING DICTIONARY ADT!!!" << endl;

   string s;
   int x;
   string S[] = {"bar", "twwwo", "bbbboo", "car", "baaaapy", "piss", "tour", "proar"};

   Dictionary A;
   Dictionary B;

   cout << endl;

   for(int i=0; i<8; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("bar", 9);

   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << A.getValue("bar") << endl;
   A.getValue("bar") *= 10; // change the value associated with "happy"
   cout << A.getValue("bar") << endl << endl;
   A.remove("twwwo");
   A.remove("car");

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // do forward iteration on B
   for(B.begin(); B.hasCurrent(); B.next()){
      s = B.currentKey();
      x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   cout << endl << endl;


   cout << "END OF THE DICTIONARY TEST!!!" << endl;  

   return 0;
}