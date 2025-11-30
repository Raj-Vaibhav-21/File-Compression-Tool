File Compression Tool (C++)

A lightweight and efficient file compression & decompression tool built in C++, inspired by ZIP-like compression systems.
This project is designed to deepen understanding of systems programming, data structures, and low-level file handling.

Features

✔️ Compress any file into a smaller binary format

✔️ Decompress it back to original

✔️ Uses Huffman Coding (lossless compression algorithm)

✔️ Works for text, logs, source code, binaries, etc.

✔️ Efficient bit-level encoding/decoding

✔️ Clean, modular C++ codebase

How It Works (High-Level Overview)

1. Frequency Analysis

The tool reads the file byte by byte and counts how many times each character appears.

2. Huffman Tree Construction

Using those frequencies, it builds a Huffman Tree (a min-heap based greedy algorithm).

3. Bit Encoding

Each character receives a unique variable-length bit pattern:

Frequent characters → shorter codes

Rare characters → longer codes

This reduces total file size.

4. Binary Output Creation

The compressor writes:

Header containing the frequency table

Encoded bitstream of the file

5. Decompression

Reads the header → rebuilds the Huffman tree → decodes the bitstream → restores the original file exactly.

Tech Stack

C++17

STL: priority_queue, unordered_map, vector, fstream

Bit manipulation

System-level file handling

Project Structure
/FileCompressionTool
│── src/
│   ├── main.cpp
│   ├── compressor.cpp
│   ├── compressor.hpp
│   ├── huffman.cpp
│   ├── huffman.hpp
│── build/
│── README.md

Usage
Compile
g++ -std=c++17 src/*.cpp -o compressor

Compress a file
./compressor -c input.txt output.bin

Decompress a file
./compressor -d output.bin restored.txt

Example

Input file: 500 KB
Compressed output: 130 KB
Savings: ~74% reduction

(Actual compression varies by file type.)

Learning Outcomes

This project helps you understand:

How real-world compression tools (ZIP, GZIP) work internally

File I/O at a low level

Memory management & bit operations

Trees, heaps, greedy algorithms

How system utilities are built in C++

Perfect project for:

System programming

Resume building

Preparing for C++ development roles

Contributions

Pull requests and suggestions are welcome!
Feel free to open an issue to discuss improvements.

License

MIT License.
