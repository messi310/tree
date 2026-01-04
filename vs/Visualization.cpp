#include "Visualization.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Visualization::displayTraversalResult(const vector<int>& result, const string& traversalName) {
    cout << "\n" << traversalName << "遍历结果: ";
    for (size_t i = 0; i < result.size() && i < 20; i++) {
        cout << result[i] << " ";
    }
    if (result.size() > 20) {
        cout << "... (共 " << result.size() << " 个节点)";
    }
    cout << endl;
}

void Visualization::displayTreeStructure(BinaryTree& tree) {
    cout << "\n树的结构:" << endl;
    tree.printTree();
}