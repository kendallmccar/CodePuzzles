// K McCarthy 2022

#include <iostream>
#include <math.h>
#include <queue>
#include <vector>

// https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/
// Given the root of a binary tree, return its maximum depth.
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

// Definition for a binary tree node from leetcode,
// ergo not a representation of how I would write this struct
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// recursive solution
int MaxDepth(TreeNode* root) {
    // no depth here, end of the line
    if (root == NULL)
        return 0;
    // check the max depth of left and right nodes
    int left_depth = MaxDepth(root->left);
    int right_depth = MaxDepth(root->right);
    // return the higher child depth, plus one for the current depth
    return std::max(left_depth, right_depth) + 1;
}

// iterative solution
int MaxDepthIterative(TreeNode* root) {
    // no depth for an empty tree
    if (root == NULL)
        return 0;
    // queue for btree traversal
    std::queue<TreeNode*> q;
    int depth = 0;
    // start queue with root node
    q.push(root);
    while (!q.empty()) {
        // each loop is another depth layer in breadth-first traversal
        ++depth;
        // hold queue size steady as it will change during the loop
        int queue_size = q.size();
        for (int i = 0; i < queue_size; ++i) {
            // prepare all child nodes for next depth level down from current
            TreeNode* current = q.front();
            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
            // remove nodes from current depth level
            q.pop();
        }
    }
    return depth;
}

// utility method not required by problem, wrote to help testing
TreeNode* BuildBinaryTree(std::vector<int>& v) {
    // can't create a tree from an empty vector or null root node
    if (v.empty() || v.at(0) == NULL)
        return NULL;
    // create vector to hold the new binary tree nodes
    std::vector<TreeNode*> nodes(v.size());
    // create root node
    TreeNode* root = new TreeNode(v.at(0));
    // add root node to node vector
    nodes.at(0) = root;
    for (int i = 1; i < v.size(); ++i) {
        // bypass empty nodes
        if (v.at(i) == NULL)
            continue;
        // create new node for value from vector
        TreeNode * node = new TreeNode(v.at(i));
        // add new node to the node vector
        nodes.at(i) = node;
        // calculate the index of the parent in the node vector
        size_t parent_index = floor((i - 1) / 2);
        // use that index to find the parent node
        TreeNode * parent = nodes.at(parent_index);
        // odd indexes are left nodes, even indexes are right nodes
        if (i % 2 == 0) {
            parent->right = node;
        }
        else {
            parent->left = node;
        }
    }
    return root;
}

void TestMaxDepth() {
    std::vector<int> btree = { 3,9,20,NULL,NULL,15,7 };
    TreeNode * root = BuildBinaryTree(btree);
    int max_depth = MaxDepth(root);
    std::cout << max_depth << std::endl;
}