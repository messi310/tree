#include "BinaryTree.h"
#include "PerformanceTest.h"
#include "Visualization.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;

TreeNode* createTreeManually(int levels, TreeNode* parent = nullptr, int level = 1, int pos = 1, bool isLeft = false) {
    if (level > levels) {
        return nullptr;
    }
    int val;
    cout << "位于第" << level << "层";
    if (level > 1) {
        cout << (isLeft ? "左" : "右") << "子节点";
        cout << "（父节点值为 " << parent->val << "）";
    }
    else {
        cout << "根节点";
    }
    cout << "的值: ";
    cin >> val;

    if (val == -1) {
        return nullptr;
    }

    TreeNode* node = new TreeNode(val);
    node->left = createTreeManually(levels, node, level + 1, pos * 2 - 1, true);
    node->right = createTreeManually(levels, node, level + 1, pos * 2, false);

    return node;
}

void displayMainMenu() {
    cout << "\n===== 二叉树管理系统 =====" << endl;
    cout << "1. 二叉树创建与测试" << endl;
    cout << "2. 二叉树性能比较" << endl;
    cout << "3. 退出" << endl;
    cout << "请选择: ";
}

void displayTreeCreationMenu() {
    cout << "\n===== 二叉树创建菜单 =====" << endl;
    cout << "1. 随机生成二叉树" << endl;
    cout << "2. 手动创建二叉树" << endl;
    cout << "3. 返回主菜单" << endl;
    cout << "请选择: ";
}

void handleRandomTreeCreation(BinaryTreeImpl& tree) {
    int levels;
    bool isFull;

    cout << "\n请输入要生成的层数: ";
    cin >> levels;

    char choice;
    cout << "是否生成满二叉树(y/n): ";
    cin >> choice;
    isFull = (choice == 'y' || choice == 'Y');

    tree.createRandomTree(levels, isFull);
    cout << "\n二叉树创建成功！" << endl;
    Visualization::displayTreeStructure(tree);
}

void handleManualTreeCreation(BinaryTreeImpl& tree) {
    int levels;
    cout << "\n请输入要创建的二叉树的层数: ";
    cin >> levels;
    cout << "\n手动创建方式输入节点值(输入-1表示空节点)" << endl;
    TreeNode* root = createTreeManually(levels, nullptr, 1, 1, false);
    tree.setRoot(root);
    cout << "\n二叉树创建成功！" << endl;
    Visualization::displayTreeStructure(tree);
}

void testTreeTraversals(BinaryTreeImpl& tree) {
    cout << "\n===== 测试菜单 =====" << endl;

    auto measureTraversal = [&tree](const string& name, auto traversalFunc) {
        auto start = chrono::high_resolution_clock::now();
        size_t metric = 0;
        vector<int> result = (tree.*traversalFunc)(false, metric);  // 获取遍历结果
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        size_t memoryUsage = pmc.PrivateUsage / 1024; // KB

        // 使用 Visualization::displayTraversalResult 输出遍历结果
        Visualization::displayTraversalResult(result, name);

        cout << "  耗时: " << duration << " 微秒" << endl;
        cout << "  内存: " << memoryUsage << " KB" << endl;
        if (name.find("Recursive") != string::npos) {
            cout << "  最大递归深度: " << metric << endl;
        }
        else if (name.find("Iterative") != string::npos) {
            if (name.find("层序") != string::npos) {
                cout << "  最长队列长度: " << metric << endl;
            }
            else {
                cout << "  最大栈深度: " << metric << endl;
            }
        }
        cout << endl;
    };

    // 递归遍历测试
    cout << "\n递归遍历 " << endl;
    measureTraversal("前序遍历(Recursive)", &BinaryTreeImpl::preorderRecursive);
    measureTraversal("中序遍历(Recursive)", &BinaryTreeImpl::inorderRecursive);
    measureTraversal("后序遍历(Recursive)", &BinaryTreeImpl::postorderRecursive);
    measureTraversal("层序遍历(Recursive)", &BinaryTreeImpl::levelorderRecursive);

    // 非递归遍历测试
    cout << "\n非递归遍历 " << endl;
    measureTraversal("前序遍历(Iterative)", &BinaryTreeImpl::preorderIterative);
    measureTraversal("中序遍历(Iterative)", &BinaryTreeImpl::inorderIterative);
    measureTraversal("后序遍历(Iterative)", &BinaryTreeImpl::postorderIterative);
    measureTraversal("层序遍历(Iterative)", &BinaryTreeImpl::levelorderIterative);
}

int main() {
    BinaryTreeImpl tree;
    PerformanceTest perfTest;
    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        cin.ignore(1000, '\n');

        switch (choice) {
        case 1: {
            int subChoice;
            do {
                displayTreeCreationMenu();
                cin >> subChoice;
                cin.ignore(1000, '\n');

                switch (subChoice) {
                case 1:
                    handleRandomTreeCreation(tree);
                    testTreeTraversals(tree);
                    break;
                case 2:
                    handleManualTreeCreation(tree);
                    testTreeTraversals(tree);
                    break;
                case 3:
                    break;
                default:
                    cout << "无效选择，请重新输入！" << endl;
                }
            } while (subChoice != 3);
            break;
        }
        case 2: {
            cout << "\n===== 二叉树性能比较 =====" << endl;
            BinaryTreeImpl bigDataTree;
            bigDataTree.createBigDataTree(100000);
            perfTest.bigDataTest(bigDataTree);
            break;
        }
        case 3:
            cout << "感谢使用，再见！" << endl;
            return 0;
        default:
            cout << "无效选择，请重新输入！" << endl;
        }
    }

    return 0;
}