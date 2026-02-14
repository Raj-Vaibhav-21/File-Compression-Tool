File Compression Tool (C++17)

A lightweight file compression & decompression tool built from scratch in C++17, using Huffman Coding.

I built this project to better understand how real-world compression tools (like ZIP/GZIP) work internally — especially the systems-level details like binary file handling, bit manipulation, and tree-based encoding.

This is a fully working, lossless compressor.

✨ Features

Compress any file into a binary format

Decompress back to the exact original file

Lossless compression using Huffman Coding

Works for text files, logs, source code, and binary files

Manual bit-level encoding and decoding

Clean and modular C++ implementation

🧠 How It Works
1. Frequency Analysis

The program reads the file byte-by-byte and counts how often each of the 256 possible byte values appears.

2. Huffman Tree Construction

Using a min-heap (std::priority_queue), it builds a Huffman tree based on frequency (greedy algorithm).

Frequent bytes → shorter bit codes
Rare bytes → longer bit codes

3. Encoding

Each byte is replaced with its Huffman bit pattern.
Bits are manually packed into bytes for efficient storage.

4. Compressed File Format

The compressed file contains:

A header (full 256-entry frequency table, 2048 bytes total)

The encoded bitstream

Because the frequency table is stored, the decompressor can rebuild the exact same Huffman tree.

5. Decompression

Read frequency table

Rebuild Huffman tree

Decode bitstream

Restore original file exactly

🛠 Tech Stack

C++17

STL (vector, array, priority_queue, unordered_map, fstream)

Manual bit manipulation

Binary-safe file I/O

📁 Project Structure
File-Compression-Tool/
│── main.cpp
│── huffman.cpp
│── huffman.h
│── file_io.cpp
│── file_io.h
│── README.md
│── LICENSE

🔨 Build
g++ main.cpp file_io.cpp huffman.cpp -std=c++17 -O2 -Wall -Wextra -o compressor

▶️ Usage
Compress
./compressor compress input.txt output.bin

Decompress
./compressor decompress output.bin restored.txt

📊 Example Output:

Original Size   : 100000000 bytes
Compressed Size : 32694356 bytes
Compression Percentage : 67.31%
Compression Ratio : 0.33


🎓 What I Learned

Building this helped me understand:

How Huffman coding actually works under the hood

How compression tools store metadata (headers)

Bit-level packing and unpacking

Tree construction using heaps

Binary file handling in C++

Writing small system utilities from scratch

🚀 Possible Improvements

Store only used symbols instead of full 256-entry header

Canonical Huffman codes

Streaming compression (avoid full in-memory bitstring)

Performance benchmarking

Archive multiple files

📜 License

MIT License
