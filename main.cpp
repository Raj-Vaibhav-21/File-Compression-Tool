#include <iostream>
#include <string>

// Your file handling code
#include "file_io.h"

// Compression logic from Person 1
#include "huffman.h"

/*
 =====================================
 HOW TO RUN THIS PROGRAM:
 =====================================

 compress input.txt output.huff
 decompress input.huff output.txt
*/

int main(int argc, char* argv[])
{
    /*
     argc = argument count
     argv = argument values

     Example:
     compress input.txt output.huff

     argc = 4
     argv[0] = program name
     argv[1] = "compress"
     argv[2] = "input.txt"
     argv[3] = "output.huff"
    */

    // Step 1: Check correct number of arguments
    if (argc != 4)
    {
        std::cout << "Wrong usage!\n";
        std::cout << "Use:\n";
        std::cout << "  compress <input> <output>\n";
        std::cout << "  decompress <input> <output>\n";
        return 1;
    }

    // Step 2: Store command line values in variables
    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    try
    {
        // Step 3: Read the input file into memory
        std::vector<uint8_t> inputData =
            readBinaryFile(inputFile);

        // This will store compressed or decompressed data
        std::vector<uint8_t> outputData;

        // Step 4: Decide what to do
        if (mode == "compress")
        {
            /*
             We send raw file data to Huffman engine
             We do NOT know how it compresses
             We just trust it
            */
            outputData = compress(inputData);
        }
        else if (mode == "decompress")
        {
            /*
             Same idea, but reverse process
            */
            outputData = decompress(inputData);
        }
        else
        {
            std::cout << "Invalid mode!\n";
            return 1;
        }

        // Step 5: Save result into output file
        writeBinaryFile(outputFile, outputData);

        // Step 6: Success message
        std::cout << "Done! File processed successfully.\n";
    }
    catch (const std::exception& e)
    {
        // Any error in reading, writing, or compression comes here
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
