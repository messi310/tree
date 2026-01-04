#pragma once
#include "BinaryTree.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace chrono;

class PerformanceTest {
public:
    struct TestResult {
        vector<int> result;
        long long durationMicro;
        size_t memoryUsageKB;
        size_t maxStackDepth;
        size_t maxQueueLength;
        string traversalType;
        bool isRecursive;

        TestResult()
            : durationMicro(0),
            memoryUsageKB(0),
            maxStackDepth(0),
            maxQueueLength(0),
            isRecursive(false) {
        }
    };

    // 测试遍历性能
    TestResult testTraversal(BinaryTree& tree, const string& traversalType, bool isRecursive);

    // 比较递归和非递归遍历性能
    void compareTraversals(BinaryTree& tree, const string& traversalType);

    // 大数据测试
    void bigDataTest(BinaryTree& tree);

private:
    size_t getCurrentMemoryUsage();
};