#include "huffman.h"

#include <fstream>
#include <queue>
#include <stdexcept> //used to include the standard library's exception classes for reporting errors through exceptions

// ---------- Node Constructors ----------

// Used an initializer list to initialize member variables directly.
// This avoids assignment in the constructor body after default initialization.
Node::Node(unsigned char b, uint64_t f)
    : byte(b), freq(f), left(nullptr), right(nullptr) {}

Node::Node(uint64_t f, Node* l, Node* r)
    : byte(0), freq(f), left(l), right(r) {}


// ---------- Frequency Analyzer ----------

std::array<uint64_t, 256> buildFrequencyTable(const std::string& filePath) {
    std::array<uint64_t, 256> freq{};//freq{} initializes all array values to zero
    freq.fill(0);//we fill freq{} with zeroes again to make it obvious & unambiguous

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    unsigned char byte;
    //reinterpret_cast<char*>(&byte) converts the address of byte (which is an unsigned char*) to a char*, which is what read() expects
    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        freq[byte]++;
    }

    return freq;
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

