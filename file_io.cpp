#include "file_io.h"
#include <fstream>
#include <stdexcept>

/*
 =====================================
 FUNCTION: readBinaryFile
 =====================================
 STEP-BY-STEP EXPLANATION:
*/
std::vector<uint8_t> readBinaryFile(const std::string& filename)
{
    // Step 1: Try to open the file in BINARY mode
    // Binary mode is IMPORTANT for compression tools
    std::ifstream file(filename, std::ios::binary);

    // Step 2: Check if file opened successfully
    if (!file)
    {
        // If file doesn't exist or can't be opened → crash safely
        throw std::runtime_error("Cannot open input file.");
    }

    // Step 3: Move the file cursor to the END of the file
    // This helps us find file size
    file.seekg(0, std::ios::end);

    // Step 4: Get the current cursor position = file size
    std::streamsize size = file.tellg();

    // Step 5: Move cursor back to the START
    file.seekg(0, std::ios::beg);

    // Step 6: Create a vector that can store ALL file bytes
    std::vector<uint8_t> buffer(size);

    // Step 7: Read file data into the vector
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    // Step 8: Check if reading failed
    if (!file)
    {
        throw std::runtime_error("Error while reading file.");
    }

    // Step 9: Return the file data to whoever called this function
    return buffer;
}

/*
 =====================================
 FUNCTION: writeBinaryFile
 =====================================
 STEP-BY-STEP EXPLANATION:
*/
void writeBinaryFile(
    const std::string& filename,
    const std::vector<uint8_t>& data)
{
    // Step 1: Open (or create) a file in BINARY mode
    std::ofstream file(filename, std::ios::binary);

    // Step 2: Check if file opened
    if (!file)
    {
        throw std::runtime_error("Cannot open output file.");
    }

    // Step 3: Write ALL bytes from vector into the file
    file.write(
        reinterpret_cast<const char*>(data.data()),
        data.size()
    );

    // Step 4: Confirm writing was successful
    if (!file)
    {
        throw std::runtime_error("Error while writing file.");
    }
}
