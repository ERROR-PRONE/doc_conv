/*
 * Copyright (c) 2016 Error Prone, All Rights Reserved
 * Error Prone is: Allan Manangan, Bryan Haley, Christopher Wirtes, Joey Cauthen
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // open the pdf in an input filestream
    ifstream pdf("test_documents/test.pdf", ios::binary | ios::in);
    // open/create a pdf file to copy the data to
    ofstream copy_pdf("test_documents/copy_test_pdf.pdf", ios::binary | ios::in | ios::out | ios::trunc);

    // throw an exception if the file doesn't open correctly
    if (!pdf.is_open())
    {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    else if (!copy_pdf.is_open())
    {
        cout << "Error opening/creating output file!" << endl;
        return 2;
    }

    // make sure we're at the beginning of the file
    pdf.seekg(0);

    string pdf_data;

    // read until the end of the file
    while (pdf.good())
    {
        // get one character at a time
        char read_buff;
        pdf.get(read_buff);

        // output to console (compare to ascii section when
        //                    opened in hex editor)
        cout << read_buff;

        //make a copy of the pdf to prove data is retained properly
        copy_pdf.put(read_buff);

        pdf_data += read_buff;
    }

    // for proof of concept, locate and extract the first stream object
    int loc_first_stream_start = -1;
    int loc_first_stream_end = -1;

    // stream objects are encapsulated by "stream" and "endstream", so we can search for
    // that using ascii strings just fine
    loc_first_stream_start = pdf_data.find("stream");
    loc_first_stream_end = pdf_data.find("endstream")+sizeof("endstream");

    // All pdfs should have at least one stream object, so if this happens, something went
    // wrong when reading the data
    if (loc_first_stream_start == -1 || loc_first_stream_end == -1)
    { cout << "Could not locate a stream object."; }

    // output the stream object to the console
    else
    {
        string first_stream_obj = pdf_data.substr(loc_first_stream_start,
                                                  loc_first_stream_end-loc_first_stream_start);

        cout << "First stream object in pdf:\n\n" << first_stream_obj << endl;
    }

    // in the future, storing an entire file in a string is obviously not ideal; we'll need to use buffers

    return 0;
}

/*
 * Notes from previous test:
 * Converting the binary data to ascii proved unnecessary;
 * it seems any binary data that can be interpreted as ascii
 * is done so automatically before being outputted to the console.
 * In addition, we can search through the pdf using ascii strings
 * such as "stream" just fine, it seems.
*/
