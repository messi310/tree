#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <windows.h>
#include <psapi.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
  virtual ~BinaryTree() { clear(root); } 

    // 树遍历接口
    virtual vector<int> preorderRecursive(bool printResult, size_t& maxDepth) = 0;
    virtual vector<int> inorderRecursive(bool printResult, size_t& maxDepth) = 0;
    virtual vector<int> postorderRecursive(bool printResult, size_t& maxDepth) = 0;
    virtual vector<int> levelorderRecursive(bool printResult, size_t& maxDepth) = 0;

    // 非递归树遍历接口
    virtual vector<int> preorderIterative(bool printResult, size_t& maxStackDepth) = 0;
    virtual vector<int> inorderIterative(bool printResult, size_t& maxStackDepth) = 0;
    virtual vector<int> postorderIterative(bool printResult, size_t& maxStackDepth) = 0;
    virtual vector<int> levelorderIterative(bool printResult, size_t& maxQueueLength) = 0;

    void createRandomTree(int levels, bool isFull);
    void createBigDataTree(int nodeCount);
    void printTree() const;
    TreeNode* getRoot() const { return root; }

protected:
    TreeNode* root;
    void clear(TreeNode* node);
    void printTreeHelper(TreeNode* node, int space) const;
};

class BinaryTreeImpl : public BinaryTree {
public:
    // 树遍历实现
    vector<int> preorderRecursive(bool printResult, size_t& maxDepth) override;
    vector<int> inorderRecursive(bool printResult, size_t& maxDepth) override;
    vector<int> postorderRecursive(bool printResult, size_t& maxDepth) override;
    vector<int> levelorderRecursive(bool printResult, size_t& maxDepth) override;

    // 非递归树遍历实现
    vector<int> preorderIterative(bool printResult, size_t& maxStackDepth) override;
    vector<int> inorderIterative(bool printResult, size_t& maxStackDepth) override;
    vector<int> postorderIterative(bool printResult, size_t& maxStackDepth) override;
    vector<int> levelorderIterative(bool printResult, size_t& maxQueueLength) override;

    void setRoot(TreeNode* newRoot) {
        clear(root); // 清除原有树
        root = newRoot;
    }

private:
    // 树遍历辅助函数
    void preorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth);
    void inorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth);
    void postorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth);
    void levelorderHelper(TreeNode* node, int level, vector<vector<int>>& levels, bool printResult, size_t& maxDepth);
};