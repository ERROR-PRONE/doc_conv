/*
   AUTHOR: ERROR-PRONE et al.
           See the /authors.text file for contributors.
   FILE: pdf.cpp
   ORIGIN: 1461442211
   VERSION: 0.1
   
   This is a proof-of-concept for abstracting portable document format (PDF) data.
   
   The class declaration is in the "pdf.h" file.
*/

/*
   This is the default constructor.
*/
pdf::pdf()
{
  // There is no failure by default.
  _fileOpenFailure = false;
  
  return;
}

/*
   This signals an in-out operation failure.
   
   RETURN:
    bool: true if an in-out operation fails or
          false if there is no failure.
*/
bool pdf::fail()
{
  if( _fileOpenFailure ) return true;
  else return false;
}

/*
   This attempts to open a /path/to/some.file for in-only use.
   
   PARAMETER LIST:
    string file: a /path/to/some.file
*/
void pdf::inFileIs( string file )
{
  // Is it possible to open the caller's file?
  _inFile.open( file.c_str() );
  
  // If there is a failure
  if( _inFile.fail() )
  {
    // then inform the user
    cout << "FAIL: " << file;
    
    // and set the failure signal.
    _fileOpenFailure = true;
  }
  // If not
  else
  {
    // then inform the user
    cout << "OPEN: " << file;
    
    // and set the failure signal.
    _fileOpenFailure = false;
  }
  return;
}

/*
   This verifies a file's format.
   
   RETURN:
    bool: true if the header is valid or
          false if the header is not valid
*/
bool pdf::verifyHeader()
{
  // These are data processing strings.
  string buffer;
  buffer.clear();
  string token;
  token.clear();
  
  /*
     Per section "3.4 File Structure" of the specification:
     A one-line header identifies the version of the specification. An end-of-line (EOL) marker, which may be a carriage return, a line feed, or both, terminates each line.
  */
  getline( _inFile, buffer );
  
  if( buffer.empty() ) return false;
  /*
     Per section "3.4.1 File Header" of the specification:
     The first line of a PDF file is a header identifying the version of the PDF specification to which the file conforms.
  */
  else if( buffer.length() >= EIGHT ) 
  {
    cout << endl << "HEADER: " << buffer;
    cout << endl << " LENGTH: " << buffer.length();
    
    /*
       Per section "3.1.2 Comments" of the specification:
       The first character of the header is "%" which indicates a comment till the EOL marker.
    */
    token = buffer.substr( ZERO, ONE );
    cout << endl << " '" << token << "'";
    if( token != "%" ) return false;
    
    // The next four characters must be "PDF-" to comply.
    token = buffer.substr( ONE, FOUR );
    cout << endl << " '" << token << "'";
    if( token != "PDF-" ) return false;
    
    // The remaining three characters indicate the version of the PDF specification.
    token = buffer.substr( FIVE, buffer.length() - FIVE );
    cout << endl << " '" << token << "'";
    if( !( token == "1.0"
        || token == "1.1"
        || token == "1.2"
        || token == "1.3"
        || token == "1.4"
        || token == "1.5"
        || token == "1.6"
        || token == "1.7" ) ) return false;
    
    // If there are no other tests then return true.
    cout << endl << " STATUS: PASS";
    return true;
  }
}