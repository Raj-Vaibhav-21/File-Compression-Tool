#include "huffman.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept> //used to include the standard library's exception classes for reporting errors through exceptions
using std::cout;

// ---------- Node Constructors ----------

// Used an initializer list to initialize member variables directly.
// This avoids assignment in the constructor body after default initialization.
Node::Node(unsigned char b, uint64_t f)
    : byte(b), freq(f), left(nullptr), right(nullptr) {}

Node::Node(uint64_t f, Node* l, Node* r)
    : byte(0), freq(f), left(l), right(r) {}


// ---------- Frequency Analyzer ----------

std::array<uint64_t, 256> buildFrequencyTable(
    const std::vector<unsigned char>& data
) {
    std::array<uint64_t, 256> freq{};
    freq.fill(0);

    for (unsigned char byte : data) {
        freq[byte]++;
    }

    return freq;
}

// -------Compress-------
std::vector<unsigned char> compress(
    const std::vector<unsigned char>& input
) {
    if (input.empty()) return {};

    // 1️⃣ Build frequency table
    auto freq = buildFrequencyTable(input);
    
    //counting how many unique symbols/characters actually appear in the input data
    int nonZero = 0;
    for (int i = 0; i < 256; ++i)
        if (freq[i] > 0)
            nonZero++;

    std::cout << "Unique symbols: " << nonZero << std::endl;

    // 2️⃣ Build Huffman Tree
    Node* root = buildHuffmanTree(freq);

    // 3️⃣ Generate Codes
    std::unordered_map<unsigned char, std::string> codeTable;
    buildHuffmanCodes(root, "", codeTable);

    // 4️⃣ Encode input into bit string
    std::string bitStream;
    for (unsigned char byte : input) {
        bitStream += codeTable[byte];
    }

    // 5️⃣ Pack bits into bytes
    std::vector<unsigned char> output;

    // ----- HEADER -----
    //Storing the frequency table with the compressed data
    //This table is needed during decompression to reconstruct the Huffman tree
    for (uint64_t value : freq) {
        for (int i = 0; i < 8; ++i) {
            output.push_back((value >> (i * 8)) & 0xFF);
        }
    }

    // ----- BODY -----
    unsigned char currentByte = 0;//Temporarily stores bits as you build up each byte
    int bitCount = 0;// Counts how many bits you’ve put into currentByte

    for (char bit : bitStream) {
        currentByte <<= 1;
        if (bit == '1')
            currentByte |= 1;

        bitCount++;

        if (bitCount == 8) {
            output.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }

    // Handle leftover bits
    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);
        output.push_back(currentByte);
    }

    std::cout << "Input bytes: " << input.size() << std::endl;
    std::cout << "Compressed bytes: " << output.size() << std::endl;

    freeHuffmanTree(root);
    return output;
}

// -------Decompress-------
std::vector<unsigned char> decompress(
    const std::vector<unsigned char>& input
) {
    if (input.size() < 256 * 8) return {};

    std::array<uint64_t, 256> freq{};
    size_t index = 0;

    // 1️⃣ Read frequency table from header
    for (int i = 0; i < 256; ++i) {
        uint64_t value = 0;
        for (int j = 0; j < 8; ++j) {
            value |= (uint64_t)input[index++] << (j * 8);
        }
        freq[i] = value;
    }
    uint64_t totalSymbols = 0;
    for (uint64_t f : freq)
        totalSymbols += f;


    // 2️⃣ Rebuild tree
    Node* root = buildHuffmanTree(freq);
    if (!root) return {};

    std::vector<unsigned char> output;
    Node* current = root;

    // 3️⃣ Decode bitstream
    for (; index < input.size() && output.size() < totalSymbols; ++index) {
        unsigned char byte = input[index];

        for (int i = 7; i >= 0 && output.size() < totalSymbols; --i) {
            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left;

        /*  When you reach a leaf node (no left/right child), you’ve fully decoded
            one symbol
            Add the decoded symbol (current->byte) to the output
            Reset current to the root to start decoding the next symbol  */
            if (!current->left && !current->right) {
                output.push_back(current->byte);
                current = root;
            }
        }
    }


    freeHuffmanTree(root);
    return output;
}


// ---------- Huffman Tree Builder ----------

struct MinHeapCompare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // Smaller the frequency; higher the priority
    }
};

//buildHuffmanTree takes a frequency table as input and will return the root node of the constructed Huffman tree.
Node* buildHuffmanTree(const std::array<uint64_t, 256>& freqTable) {
    std::priority_queue<Node*, std::vector<Node*>, MinHeapCompare> minHeap;

    // Creates leaf nodes representing the byte and its frequency
    for (int i = 0; i < 256; ++i) {
        if (freqTable[i] > 0) {
            minHeap.push(new Node(static_cast<unsigned char>(i), freqTable[i]));
        }
    }

    // Edge case: empty file
    if (minHeap.empty()) {
        return nullptr;
    }

    // Iteratively combine the two nodes with the lowest frequency, creating new parent nodes,
    // until only one node (the root of the Huffman tree) remains.
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* parent = new Node(left->freq + right->freq, left, right);
        minHeap.push(parent);
    }

    return minHeap.top();
    // This root node is returned to represent the entire Huffman tree structure.
}


// ---------- Huffman Code Generator ----------

void buildHuffmanCodes(
    Node* root,
    const std::string& prefix,
    std::unordered_map<unsigned char, std::string>& codeTable
) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        codeTable[root->byte] = prefix.empty() ? "0" : prefix;
        return;
    }

    buildHuffmanCodes(root->left,  prefix + "0", codeTable);
    buildHuffmanCodes(root->right, prefix + "1", codeTable);
}


// ---------- Cleanup ----------

void freeHuffmanTree(Node* root) {
    if (!root) return;

    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}


