#include "BinaryTree.h"
#include <iostream>
#include <queue>
#include <stack>
#include <random>

void BinaryTree::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinaryTree::createRandomTree(int levels, bool isFull) {
    if (levels <= 0) {
        cout << "层数必须大于0" << endl;
        return;
    }

    clear(root);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    root = new TreeNode(dis(gen));

    if (levels > 1) {
        queue<TreeNode*> q;
        q.push(root);
        int currentLevel = 1;

        while (currentLevel < levels && !q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* current = q.front();
                q.pop();

                // 创建左子节点
                if (isFull || dis(gen) % 2 == 0) {
                    current->left = new TreeNode(dis(gen));
                    q.push(current->left);
                }

                // 创建右子节点
                if (isFull || dis(gen) % 2 == 0) {
                    current->right = new TreeNode(dis(gen));
                    q.push(current->right);
                }
            }
            currentLevel++;
        }
    }
}

void BinaryTree::createBigDataTree(int nodeCount) {
    if (nodeCount < 1) {
        cout << "节点数量必须大于0" << endl;
        return;
    }

    clear(root);
    queue<TreeNode*> q;
    root = new TreeNode(1);
    q.push(root);
    int createdNodes = 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    while (createdNodes < nodeCount && !q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (createdNodes < nodeCount) {
            current->left = new TreeNode(dis(gen));
            q.push(current->left);
            createdNodes++;
        }

        if (createdNodes < nodeCount) {
            current->right = new TreeNode(dis(gen));
            q.push(current->right);
            createdNodes++;
        }
    }
}

void BinaryTree::printTree() const {
    if (!root) {
        cout << "空树" << endl;
        return;
    }
    printTreeHelper(root, 0);
    cout << endl;
}

void BinaryTree::printTreeHelper(TreeNode* node, int space) const {
    const int COUNT = 6;
    if (!node) return;

    space += COUNT;
    printTreeHelper(node->right, space);

    cout << endl;
    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }
    cout << node->val << "\n";

    printTreeHelper(node->left, space);
}

// ========== BinaryTreeImpl 实现 ==========

// 递归前序遍历实现
vector<int> BinaryTreeImpl::preorderRecursive(bool printResult, size_t& maxDepth) {
    vector<int> result;
    maxDepth = 0;
    preorderHelper(root, result, printResult, 1, maxDepth);
    return result;
}

void BinaryTreeImpl::preorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth) {
    if (!node) return;
    if (currentDepth > maxDepth) maxDepth = currentDepth;
    if (printResult) cout << node->val << " ";
    result.push_back(node->val);
    preorderHelper(node->left, result, printResult, currentDepth + 1, maxDepth);
    preorderHelper(node->right, result, printResult, currentDepth + 1, maxDepth);
}

// 递归中序遍历实现
vector<int> BinaryTreeImpl::inorderRecursive(bool printResult, size_t& maxDepth) {
    vector<int> result;
    maxDepth = 0;
    inorderHelper(root, result, printResult, 1, maxDepth);
    return result;
}

void BinaryTreeImpl::inorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth) {
    if (!node) return;
    if (currentDepth > maxDepth) maxDepth = currentDepth;
    inorderHelper(node->left, result, printResult, currentDepth + 1, maxDepth);
    if (printResult) cout << node->val << " ";
    result.push_back(node->val);
    inorderHelper(node->right, result, printResult, currentDepth + 1, maxDepth);
}

// 递归后序遍历实现
vector<int> BinaryTreeImpl::postorderRecursive(bool printResult, size_t& maxDepth) {
    vector<int> result;
    maxDepth = 0;
    postorderHelper(root, result, printResult, 1, maxDepth);
    return result;
}

void BinaryTreeImpl::postorderHelper(TreeNode* node, vector<int>& result, bool printResult, size_t currentDepth, size_t& maxDepth) {
    if (!node) return;
    if (currentDepth > maxDepth) maxDepth = currentDepth;
    postorderHelper(node->left, result, printResult, currentDepth + 1, maxDepth);
    postorderHelper(node->right, result, printResult, currentDepth + 1, maxDepth);
    if (printResult) cout << node->val << " ";
    result.push_back(node->val);
}

// 非递归前序遍历实现
vector<int> BinaryTreeImpl::preorderIterative(bool printResult, size_t& maxStackDepth) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> s;
    s.push(root);
    maxStackDepth = 1;

    while (!s.empty()) {
        if (s.size() > maxStackDepth) {
            maxStackDepth = s.size();
        }

        TreeNode* node = s.top();
        s.pop();

        if (printResult) cout << node->val << " ";
        result.push_back(node->val);

        if (node->right) {
            s.push(node->right);
            if (s.size() > maxStackDepth) {
                maxStackDepth = s.size();
            }
        }
        if (node->left) {
            s.push(node->left);
            if (s.size() > maxStackDepth) {
                maxStackDepth = s.size();
            }
        }
    }
    return result;
}

// 非递归中序遍历实现
vector<int> BinaryTreeImpl::inorderIterative(bool printResult, size_t& maxStackDepth) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* current = root;
    maxStackDepth = 1; 

    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            if (s.size() > maxStackDepth) {
                maxStackDepth = s.size();
            }
            current = current->left;
        }

        current = s.top();
        s.pop();

        if (printResult) cout << current->val << " ";
        result.push_back(current->val);
        current = current->right;
    }
    return result;
}

// 非递归后序遍历实现
vector<int> BinaryTreeImpl::postorderIterative(bool printResult, size_t& maxStackDepth) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> s;
    s.push(root);
    TreeNode* prev = nullptr;
    maxStackDepth = 1; 

    while (!s.empty()) {
        if (s.size() > maxStackDepth) {
            maxStackDepth = s.size();
        }

        TreeNode* current = s.top();

        if (!current->left && !current->right ||
            (prev && (prev == current->left || prev == current->right))) {
            if (printResult) cout << current->val << " ";
            result.push_back(current->val);
            s.pop();
            prev = current;
        }
        else {
            if (current->right) {
                s.push(current->right);
                if (s.size() > maxStackDepth) {
                    maxStackDepth = s.size();
                }
            }
            if (current->left) {
                s.push(current->left);
                if (s.size() > maxStackDepth) {
                    maxStackDepth = s.size();
                }
            }
        }
    }
    return result;
}

// 递归层序遍历辅助函数
void BinaryTreeImpl::levelorderHelper(TreeNode* node, int level, vector<vector<int>>& levels, bool printResult, size_t& maxDepth) {
    if (!node) return;

    if (level >= levels.size()) {
        levels.push_back({});
    }
    levels[level].push_back(node->val);
    if (printResult) cout << node->val << " ";

    maxDepth = max(maxDepth, static_cast<size_t>(level + 1));

    levelorderHelper(node->left, level + 1, levels, printResult, maxDepth);
    levelorderHelper(node->right, level + 1, levels, printResult, maxDepth);
}

// 递归层序遍历实现
// BinaryTreeImpl.cpp
vector<int> BinaryTreeImpl::levelorderRecursive(bool printResult, size_t& maxDepth) {
    if (!root) {
        maxDepth = 0;
        return {};
    }

    maxDepth = 0;
    auto computeHeight = [](TreeNode* node, size_t depth, auto&& self) -> size_t {
        if (!node) return depth;
        size_t left = self(node->left, depth + 1, self);
        size_t right = self(node->right, depth + 1, self);
        return max(left, right);
    };
    maxDepth = computeHeight(root, 0, computeHeight);

    vector<int> result;
    result.reserve(1 << (maxDepth + 1)); 

    vector<TreeNode*> currentLevel = { root };
    vector<TreeNode*> nextLevel;
    nextLevel.reserve(1 << maxDepth); 

    auto processLevel = [&]() {
        while (!currentLevel.empty()) {
            for (TreeNode* node : currentLevel) {
                if (printResult) cout << node->val << " ";
                result.push_back(node->val);

                if (node->left) nextLevel.push_back(node->left);
                if (node->right) nextLevel.push_back(node->right);
            }

            currentLevel.clear();
            swap(currentLevel, nextLevel);
        }
    };

    processLevel();

    return result;
}

// 非递归层序遍历实现
vector<int> BinaryTreeImpl::levelorderIterative(bool printResult, size_t& maxQueueLength) {
    vector<int> result;
    if (!root) return result;

    vector<TreeNode*> nodeQueue;
    nodeQueue.reserve(1024); 

    size_t frontIndex = 0;
    nodeQueue.push_back(root);
    maxQueueLength = 1; 

    if (printResult) cout << "层序遍历: ";

    while (frontIndex < nodeQueue.size()) {
        size_t currentQueueLength = nodeQueue.size() - frontIndex;

        if (currentQueueLength > maxQueueLength) {
            maxQueueLength = currentQueueLength;
        }

        for (size_t i = 0; i < currentQueueLength; i++) {
            TreeNode* node = nodeQueue[frontIndex++];

            if (printResult) cout << node->val << " ";
            result.push_back(node->val);

            if (node->left) nodeQueue.push_back(node->left);
            if (node->right) nodeQueue.push_back(node->right);
        }

        if (frontIndex > 1024 && frontIndex > nodeQueue.size() / 2) {
            vector<TreeNode*> newQueue;
            newQueue.reserve(nodeQueue.size() - frontIndex + 128);
            newQueue.assign(nodeQueue.begin() + frontIndex, nodeQueue.end());
            nodeQueue.swap(newQueue);
            frontIndex = 0;
        }
    }
    return result;
}