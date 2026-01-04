#pragma once
#include "BinaryTree.h"
#include "PerformanceTest.h"
#include <vector>
#include <string>

class Visualization {
public:
    // 显示遍历结果
    static void displayTraversalResult(const vector<int>& result, const string& traversalName);

    // 显示树结构
    static void displayTreeStructure(BinaryTree& tree);
};