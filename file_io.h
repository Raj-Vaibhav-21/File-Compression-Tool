#ifndef FILE_IO_H
#define FILE_IO_H

// We include these so we can use vector, string, and uint8_t
#include <vector>
#include <string>
#include <cstdint>

/*
 ===============================
 FUNCTION: readBinaryFile
 ===============================
 WHAT IT DOES:
 - Opens a file (like input.txt)
 - Reads ALL its data (even binary files like images)
 - Stores the data in a vector of bytes
 - Returns that vector

 WHY vector<uint8_t>?
 - uint8_t = 1 byte
 - vector = dynamic array
 - Perfect for raw file data
*/
std::vector<uint8_t> readBinaryFile(const std::string& filename);

/*
 ===============================
 FUNCTION: writeBinaryFile
 ===============================
 WHAT IT DOES:
 - Creates or opens a file
 - Writes binary data into it
 - Used for compressed output
*/
void writeBinaryFile(
    const std::string& filename,
    const std::vector<uint8_t>& data
);

#endif
