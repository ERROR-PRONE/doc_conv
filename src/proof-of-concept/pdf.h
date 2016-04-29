/*
   AUTHOR: ERROR-PRONE et al.
           See the /authors.text file for contributors.
   FILE: pdf.h
   ORIGIN: 1461448598
   VERSION: 0.1
   
   This is a proof-of-concept for abstracting portable document format (PDF) data.
   
   The class definition is in the "pdf.cpp" file.
*/

// If the compiler does not have a definition for the pdf.h header then use the following definition:

#ifndef PDF_H
#define PDF_H

#include <fstream>
#include <iostream>
#include <string>

/*
   This pdf object abstracts the portable document format (PDF). An in file for this object conforms to version 1.7 of the PDF specification.
   
   Per section "3.4 File Structure" of the specification:
   A canonical PDF file consists of four elements: a one-line header, a body, a cross-reference table, and a trailer.
*/
class pdf
{
  // These are accessible to callers.
  public:
    
    // This is the default constructor.
    pdf();
    
    // This signals an in-out operation failure.
    bool fail();
    
    // This adds an in-only file reference.
    void inFileIs( string file );
    
    // This verifies a file's header.
    bool verifyHeader();
    
  // These are not accessible to callers.
  private:
    
    // These are constants that the class uses.
    static const int ZERO = 0;
    static const int ONE = 1;
    static const int FOUR = 4;
    static const int FIVE = 5;
    static const int EIGHT = 8;
    
    // Is there a failure with regards to opening a file?
    bool _fileOpenFailure;
    
    // This is an in-only file stream.
    ifstream _inFile;
};

// The class definition is in the "pdf.cpp" file.
#include "pdf.cpp"
#endif