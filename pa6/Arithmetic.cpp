// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA6
//  Arithmetic.cpp
//  This file contains code for the main program which prints out the 
//  results of many different arithmetic operations.
// -----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"
using namespace std;

int main(int argc, char *argv[]){

    // CITE: File IO code from Professor Tantalo
   ifstream in;
   ofstream out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   string string_A, string_B;
   in >> string_A;
    in >> string_B;

    BigInteger A = BigInteger(string_A);
    BigInteger B = BigInteger(string_B);
    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");
    BigInteger nine = BigInteger("9");
    BigInteger sixteen = BigInteger("16");

    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << three * A - two * B << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << nine * A * A * A * A + sixteen * B * B * B * B * B << endl << endl;

    return 0;
}