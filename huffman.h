#pragma once /* A specialized preprocessor directive used as a header guard. Its job is to
               ensure that this header file is included only once during a single compilation, even if multiple other files try to include it */

#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint> /* A standard C++ header file that provides fixed-width integer types, such as uint8_t, int32_t, uint64_t, etc. */

// Huffman Tree Node
struct Node {
    unsigned char byte;   // valid only for leaf nodes; we used unsigned because we can't have our characters as negatives
    uint64_t freq;
    Node* left;
    Node* right;

    Node(unsigned char b, uint64_t f); // Leaf Nodes (Character/Symbol)
    Node(uint64_t f, Node* l, Node* r); // Inner nodes, gives structure to the tree
};

// Frequency Analyzer
std::array<uint64_t, 256> buildFrequencyTable(const std::vector<unsigned char>& data);
/* Constructor for the Node struct
Creates a node with the given symbol and frequency */

//Takes a vector of bytes(input) and returns the compressed data
std::vector<unsigned char> compress(
    const std::vector<unsigned char>& input
);

//Takes the vector of compressed data and reconstructs the original, uncompressed data
std::vector<unsigned char> decompress(
    const std::vector<unsigned char>& input
);

// Huffman Tree Builder
Node* buildHuffmanTree(const std::array<uint64_t, 256>& freqTable);
// buildHuffmanTree will repeatedly call "Node(uint64_t f, Node* l, Node* r)" while constructing the tree.

// Huffman Code Generator
void buildHuffmanCodes(
    Node* root,
    const std::string& prefix,
    std::unordered_map<unsigned char, std::string>& codeTable
);
// Traverses the Huffman tree and builds the binary codes for each symbol.

// Cleanup
void freeHuffmanTree(Node* root);
// This function will recursively delete every node in the Huffman tree to prevent memory leaks.


