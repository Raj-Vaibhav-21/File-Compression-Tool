#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "file_io.h"
#include "huffman.h"


int main(int argc, char* argv[])
{

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
        
        // Step 6: Show compression stats (only for compression mode)
        if (mode == "compress")
        {
            size_t originalSize = inputData.size();
            size_t compressedSize = outputData.size();

            if (originalSize == 0)
            {
                std::cout << "Empty file. Nothing to compress.\n";
            }
            
            else
            {   //Compression Report
                double compressionPercentage =
                    (1.0 - (double)compressedSize / originalSize) * 100.0;


                double compressionRatio =
                    (double)compressedSize / originalSize;

                std::cout << "\nCompression Report\n";
                std::cout << "------------------\n";
                std::cout << "Original Size : " << originalSize << " bytes\n";
                std::cout << "Compressed Size : " << compressedSize << " bytes\n";
                std::cout << "Compresion Percentage : "
                          << std::fixed << std::setprecision(2)
                          << compressionPercentage << "%\n";
                std::cout << "Compression Ratio : "
                          << compressionRatio << "\n";
            }
        }

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
