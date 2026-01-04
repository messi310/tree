#include "PerformanceTest.h"
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

size_t PerformanceTest::getCurrentMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.PrivateUsage / 1024; // 转换为KB
    }
    return 0;
}

PerformanceTest::TestResult PerformanceTest::testTraversal(BinaryTree& tree, const string& traversalType, bool isRecursive) {
    TestResult result;
    result.traversalType = traversalType;
    result.isRecursive = isRecursive;
    result.maxStackDepth = 0;
    result.maxQueueLength = 0;

    // 在遍历前获取内存使用情况
    size_t startMemory = getCurrentMemoryUsage();
    
    auto start = high_resolution_clock::now();

    if (traversalType == "前序") {
        if (isRecursive) {
            result.result = tree.preorderRecursive(false, result.maxStackDepth);
        }
        else {
            result.result = tree.preorderIterative(false, result.maxStackDepth);
        }
    }
    else if (traversalType == "中序") {
        if (isRecursive) {
            result.result = tree.inorderRecursive(false, result.maxStackDepth);
        }
        else {
            result.result = tree.inorderIterative(false, result.maxStackDepth);
        }
    }
    else if (traversalType == "后序") {
        if (isRecursive) {
            result.result = tree.postorderRecursive(false, result.maxStackDepth);
        }
        else {
            result.result = tree.postorderIterative(false, result.maxStackDepth);
        }
    }
    else if (traversalType == "层序") {
        if (isRecursive) {
            result.result = tree.levelorderRecursive(false, result.maxStackDepth);
        }
        else {
            result.result = tree.levelorderIterative(false, result.maxQueueLength);
        }
    }

    auto end = high_resolution_clock::now();
    result.durationMicro = duration_cast<microseconds>(end - start).count();
    
    // 计算内存增量
    size_t endMemory = getCurrentMemoryUsage();
    result.memoryUsageKB = endMemory - startMemory;

    return result;
}

void PerformanceTest::compareTraversals(BinaryTree& tree, const string& traversalType) {
    cout << "\n=== " << traversalType << "遍历性能比较 ===" << endl;

    // 测试递归遍历
    TestResult recursiveResult = testTraversal(tree, traversalType, true);
    cout << "递归遍历:" << endl;
    cout << "  耗时: " << recursiveResult.durationMicro << " 微秒" << endl;
    cout << "  内存: " << recursiveResult.memoryUsageKB << " KB" << endl;
    cout << "  最大递归深度: " << recursiveResult.maxStackDepth << endl;

    // 测试非递归遍历
    TestResult iterativeResult = testTraversal(tree, traversalType, false);
    cout << "\n非递归遍历:" << endl;
    cout << "  耗时: " << iterativeResult.durationMicro << " 微秒" << endl;
    cout << "  内存: " << iterativeResult.memoryUsageKB << " KB" << endl;

    // 层序遍历显示最大队列长度
    if (traversalType == "层序") {
        cout << "  最长队列长度: " << iterativeResult.maxQueueLength << endl;
    }
    else {
        // 其他遍历显示最大栈深度
        cout << "  最大栈深度: " << iterativeResult.maxStackDepth << endl;
    }

    // 性能比较
    double timeRatio = (double)recursiveResult.durationMicro / iterativeResult.durationMicro;
    double memoryRatio = (double)recursiveResult.memoryUsageKB / iterativeResult.memoryUsageKB;

    cout << "\n性能比较:" << endl;
    cout << "  时间比率(递归/非递归): " << fixed << setprecision(2) << timeRatio << endl;
    cout << "  内存比率(递归/非递归): " << fixed << setprecision(2) << memoryRatio << endl;
}

void PerformanceTest::bigDataTest(BinaryTree& tree) {
    cout << "\n========== 大数据性能测试 (N >= 1M) ==========" << endl;
    cout << "说明: 比较各种遍历方式" << endl;

    vector<string> traversalTypes = { "前序", "中序", "后序", "层序" };

    for (const auto& type : traversalTypes) {
        compareTraversals(tree, type);
        cout << "\n----------------------------------------" << endl;
    }
}
