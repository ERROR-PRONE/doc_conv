/*
   AUTHOR: ERROR-PRONE et al.
           See the /authors.text file for contributors.
   FILE: convert.cpp
   ORIGIN: 1461388161
   VERSION: 0.1
   
   This is a proof-of-concept for converting document formats.
*/

#include <iostream>
#include <string>

using namespace std;

// Any non-standard C++ classes and libraries follow.
#include "pdf.h"

/*
   This displays usage.
*/
void usage()
{
  cout << "USAGE: convert /path/to/in.file";
  return;
}

/*
   This proof-of-concept opens some in.file, verifies its format, and puts its content to the console.
   
   The scope of this proof-of-concept is the portable document format (PDF).
*/
int main( int argumentCount, char* argumentValues[] )
{
  // This constant is for initialization.
  static const int ZERO = 0;
  static const int ONE = 1;
  static const int TWO = 2;
  
  // This is a PDF object.
  pdf object;
  
  /*
     Are there two arguments?
     If not then display usage.
  */
  if( argumentCount != TWO ) usage();
  // The in.file is latter.
  else
  {
    // Is it possible to open in.file?
    object.inFileIs( string( argumentValues[ ONE ] ) );
    if( object.fail() ) return ONE;
    
    // Is the header valid?
    if( !( object.verifyHeader() ) ) return ONE;
  }
  
  // There are no errors so return ZERO.
  return ZERO;
}
