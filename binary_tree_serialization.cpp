// K McCarthy 2022

#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>

// Simple program to serialize and deserialize binary tree of int32
// 
// Runtime for Serialize or Deserialize: O(n) where n = Binary Tree Size
//
// Assumptions:
//  Serialization does not need to be human-readable
//  Sender and recipient have same endianness
//  Size limit of 2^31 items in tree, and range limit of 2^32 signed values
//  Input is valid binary tree (enforced by unique_ptr)
//  In case of invalid or empty inputs, returns an empty string (serialization) or nullptr (deserialization)
// 
// Binary Tree Serialization Schema
// Because values are all int32, we can assume fixed size blocks for all values (block end denoted by |)
// Child nodes will be referred to by index (no child is index -1) in the order of left first, right second
// Context-free Frames Schema:
//  Node 1 value | Left child index | Right child index | Node 2 val | L child index | R child index {...}
// For a simple binary tree of root node 8 with left child 13 right child 20
//  8|1|2|13|0|0|20|0|0

struct Node {
    Node() = delete;
    Node(int value, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
        value(value),
        left(std::move(left)),
        right(std::move(right))
    {}
    const int32_t value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

class Serializer {
public:
    Serializer() = default;
    ~Serializer() = default;

    std::string SerializeBTree(std::unique_ptr<Node> root) {
        // return emptry string if no binary tree
        if (root.get() == nullptr)
            return "";

        // reset state in case called multiple times
        data_buffer_.clear();
        current_node_index_ = 0;

        // get tree size to create buffer
        int size = GetTreeSize(root.get());
        // calculate bytes for tree as 4 bytes for each of 3 int32's per each node
        int bytes = 3 * 4 * size;
        data_buffer_.resize(bytes);
        int32_t* recast_buffer = reinterpret_cast<int32_t*>(&data_buffer_[0]);

        // traverse in breadth first search
        int array_index = 0; // 1 node index covers 3 array indexes, so tracking seperately
        node_queue_.push(std::move(root));
        while (!node_queue_.empty()) {
            std::unique_ptr<Node> current_node = std::move(node_queue_.front());
            node_queue_.pop();
            // add current node to buffer, followed by the planned indices of its two children
            recast_buffer[array_index++] = current_node->value;
            int left_node_index = ProcessChildNode(std::move(current_node->left));
            recast_buffer[array_index++] = left_node_index;
            int right_node_index = ProcessChildNode(std::move(current_node->right));
            recast_buffer[array_index++] = right_node_index;
        }

        return data_buffer_;
    }

private:
    std::queue<std::unique_ptr<Node>> node_queue_; // queue of nodes to be serialized
    int current_node_index_ = 0; // start with the first node
    std::string data_buffer_; // data buffer

    // returns child node index in future serialized string
    int ProcessChildNode(std::unique_ptr<Node> node) {
        // child index is -1 to indicate no child
        if (node == nullptr)
            return -1;
        // if child node exists, put it on the queue
        node_queue_.push(std::move(node));
        // return next index in queue because it is breadth first traversal
        return ++current_node_index_;
    }

    // returns number of nodes in tree through depth first search
    int GetTreeSize(Node* node) {
        if (node == nullptr)
            return 0;
        return GetTreeSize(node->left.get()) + GetTreeSize(node->right.get()) + 1;
    }
};

class Deserializer {
public:
    Deserializer() = default;
    ~Deserializer() = default;

    std::unique_ptr<Node> DeserializeBTree(const std::string& input) {
        // sanity check that incoming string is not empty and length is a multiple of 32 bytes
        if (input.empty() || input.size() % 4 != 0)
            return nullptr;
        // make note of the tree size to check for valid indexes
        tree_size_ = input.size() / 4;
        // clear the visited set in case called multiple times
        visited_.clear();
        // treat string as int32 data
        raw_array_ = reinterpret_cast<const int32_t*>(&input.front());
        return DeserializeFrame(0);
    }

private:
    int tree_size_ = 0; // number of nodes expected based on string size
    std::unordered_set<int> visited_; // visited set to check for bad faith data
    const int32_t* raw_array_ = nullptr; // raw string buffer recast as int32 data

    // Utility to convert indexes from node index to array index
    int ConvertIndex(int nodeIndex) {
        // zero is index to mean empty child
        // each node contains 3 indexes for value, left node, right node
        // so recalculation for blocks of 3 is needed
        if (nodeIndex == -1)
            return nodeIndex;
        // return array index
        return (nodeIndex * 3);
    }

    // Recursive method for depth first construction of Nodes
    std::unique_ptr<Node> DeserializeFrame(int array_index) {
        // check for valid index
        if (array_index > tree_size_ - 2)
            return nullptr;
        // this is not a child or child already claimed
        if (array_index == -1 || visited_.count(array_index) == 1)
            return nullptr;

        // add to visited set
        visited_.insert(array_index);

        // extract data
        int32_t current_node_value = raw_array_[array_index];
        int left_node_index = raw_array_[array_index + 1];
        int left_array_index = ConvertIndex(left_node_index);
        int right_node_index = raw_array_[array_index + 2];
        int right_array_index = ConvertIndex(right_node_index);

        std::unique_ptr<Node> left_ptr = DeserializeFrame(left_array_index);
        std::unique_ptr<Node> right_ptr = DeserializeFrame(right_array_index);
        std::unique_ptr<Node> current_node = std::make_unique<Node>(current_node_value, std::move(left_ptr), std::move(right_ptr));

        return current_node;
    }
};

void TestBinaryTreeSerialization()
{
    // Sample test data
    std::unique_ptr<Node> mostfun = std::make_unique<Node>(9, nullptr, nullptr);
    std::unique_ptr<Node> fun = std::make_unique<Node>(-2, nullptr, nullptr);
    std::unique_ptr<Node> morefun = std::make_unique<Node>(23587, nullptr, std::move(mostfun));
    std::unique_ptr<Node> left = std::make_unique<Node>(13, std::move(fun), nullptr);
    std::unique_ptr<Node> right = std::make_unique<Node>(20, nullptr, std::move(morefun));
    std::unique_ptr<Node> root = std::make_unique<Node>(8, std::move(left), std::move(right));

    // Create classes
    Serializer serializer;
    Deserializer deserializer;

    // Do and Undo match test
    std::string s_btree = serializer.SerializeBTree(std::move(root));
    std::unique_ptr<Node> btree = deserializer.DeserializeBTree(s_btree);
    std::string new_s_btree = serializer.SerializeBTree(std::move(btree));
    if (s_btree == new_s_btree && !s_btree.empty()) {
        std::cout << "Correct" << std::endl;
    }
    else {
        // don't match, recieved bad data, or no data
        std::cout << "Incorrect" << std::endl;
    }
}
