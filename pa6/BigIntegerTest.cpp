// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA6
//  BigIntegerTest.cpp
//  This file contains code for different test cases in BigInteger ADT.
// -----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(void){
    // Initialize different Big Integers
    BigInteger A = BigInteger("-111122223333");
    BigInteger B = BigInteger("-112122223333");
    BigInteger C;
    cout << C << endl;
    BigInteger D = BigInteger("1000000000");
    BigInteger E = D; // copy constructor
    bool bool_value;

    // Assignment operators
    A += B;
    cout << A << endl;

    A -= B;
    cout << A << endl;

    A *= B;
    cout << A << endl;

    cout << "sign is: " << A.sign() << endl;
    cout << A.compare(B) << endl;
    cout << "number: " << A << endl;

    A = BigInteger("-111122223333");
    B = BigInteger("-110122223333");
    D = BigInteger("-1000000000");
    A -= B;

    D = A + B;
    cout << D << endl;

    D = A - B;
    cout << D << endl;

    D = A * B;
    cout << D << endl;

    cout << "sign is: " << A.sign() << endl;
    cout << "number: " << A << endl;
    A.makeZero();
    B.negate();

    cout << A << endl;
    cout << B << endl;
    cout << C << endl;
    cout << D << endl;

    bool_value = (A==B);
    cout << "TEST EQUAL: " << bool_value << endl;
    bool_value = (A > B);
    cout << "TEST Greater: " << bool_value << endl;
    bool_value = (A < B);
    cout << "TEST Less: " << bool_value << endl;
    bool_value = (A>=B);
    cout << "TEST Greater/equal: " << bool_value << endl;
    bool_value = (A<=B);
    cout << "TEST Less/equal: " << bool_value << endl;

    bool_value = (D==A);
    cout << "TEST EQUAL: " << bool_value << endl;
    bool_value = (D > A);
    cout << "TEST Greater: " << bool_value << endl;
    bool_value = (D < B);
    cout << "TEST Less: " << bool_value << endl;
    bool_value = (D >= B);
    cout << "TEST Greater/equal: " << bool_value << endl;
    bool_value = (D <= B);
    cout << "TEST Less/equal: " << bool_value << endl;

    A = BigInteger("999");
    B = BigInteger("999");
    C = BigInteger();
    D = BigInteger("12348148518469129628889");

    C = A * B;
    cout << C.sign() << endl;
    cout << C << endl;


   return 0;
}

/* Expected output:
0
-223244446666
-111122223333
0
110122223333000000000
TEST EQUAL: 0
TEST Greater: 0
TEST Less: 1
TEST Greater/equal: 0
TEST Less/equal: 1
TEST EQUAL: 0
TEST Greater: 1
TEST Less: 0
TEST Greater/equal: 1
TEST Less/equal: 0
1
998001
*/