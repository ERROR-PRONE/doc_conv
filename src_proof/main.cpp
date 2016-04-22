#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <sys/stat.h>

using namespace std;

int main()
{
    // struct to store size of file
    struct stat results;

    //test for size of file
    stat("test_documents/test.pdf", &results);

    // open pdf file
    fstream pdf;
    pdf.open("test_documents/test.pdf", ios::binary);

    //create buffer to hold the entire file (change later)
    char buffer[results.st_size];

    // read file into buffer
    pdf.read(buffer, results.st_size);

     /* convert binary data to human readable ascii
      * we want to confirm what we're seeing is correct */

    // convert buffer to string
    string data(buffer);
    // string to hold converted ascii data
    string ascii_data;

    // string stream to get the buffer one byte at a time
    stringstream convert_to_ascii(data);

    while (convert_to_ascii.good())
    {
        // set the size of each block to one byte each
        bitset<8> bits;
        // grab the block of binary data
        convert_to_ascii >> bits;
        // convert to ascii
        char c = char(bits.to_ulong());
        // add to ascii string
        ascii_data += c;

    }

    //out put file in ascii
    cout << ascii_data;
}
