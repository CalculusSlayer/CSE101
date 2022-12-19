// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA8
//  Order.cpp
//  This file contains code for the main program of the assignment.
// -----------------------------------------------------------------------------

#include "Dictionary.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
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

   Dictionary solution;
   string ex1;
   int count = 0;
   while (getline(in, ex1)) {
       count++;
       solution.setValue(ex1, count);
   }

    out << solution << endl;
    out << solution.pre_string() << endl;
    return 0;
}