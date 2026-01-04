#ifndef TREE_H
#define TREE_H
#include <list>
#include <queue>

/*------------------------二叉树------------------------*/
class NodeItem;

template<typename T>
struct BinTreeNode
{
    //指针域
    BinTreeNode *left;
    BinTreeNode *right;
    NodeItem *p_item;
    //数据域
    T data;
};

enum BinTreeOrder
{
    Preorder,
    Inorder,
    Postorder,
    Levelorder
};

enum BinTreeLinkDir
{
    LinkLeft,
    LinkRight
};

class BinTree
{
public:
    template<typename T>
    static void DeleteTree(BinTreeNode<T> *root)
    {
        if(root != nullptr)
        {
            DeleteTree(root->left);
            DeleteTree(root->right);
            root->left = nullptr;
            root->right = nullptr;
            delete root;
        }
    }

    template<typename T>
    static void CopyTree(BinTreeNode<T> *src, BinTreeNode<T> *&target)
    {
        if(src == nullptr)
            target = nullptr;
        else {
            target = new BinTreeNode<T>;
            target->data = src->data;
            CopyTree(src->left, target->left);
            CopyTree(src->right, target->right);
        }
    }

    template<typename T>
    static int NodeCount(BinTreeNode<T> *root)
    {
        if(root == nullptr) return 0;
        else return NodeCount(root->left) + NodeCount(root->right) + 1;
    }

    template<typename T>
    static int TreeDepth(BinTreeNode<T> *root)
    {
        if(root == nullptr) return 0;
        else {
            int leftDepth = TreeDepth(root->left);
            int rightDepth = TreeDepth(root->right);
            return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
        }
    }

    template<typename T>
    static void Traversal(BinTreeOrder order, BinTreeNode<T> *root, std::list<BinTreeNode<T> *> &nodeList)
    {
        if(root == nullptr) return;
        else if(order == Preorder)
        {
            nodeList.push_back(root);
            Traversal(order, root->left, nodeList);
            Traversal(order, root->right, nodeList);
        }
        else if(order == Inorder)
        {
            Traversal(order, root->left, nodeList);
            nodeList.push_back(root);
            Traversal(order, root->right, nodeList);
        }
        else if(order == Postorder)
        {
            Traversal(order, root->left, nodeList);
            Traversal(order, root->right, nodeList);
            nodeList.push_back(root);
        }
        else if(order == Levelorder)
        {
            LevelOrderTraversal(root, nodeList);
        }
    }

    template<typename T>
    static void LevelOrderTraversal(BinTreeNode<T> *root, std::list<BinTreeNode<T> *> &orderNodeList)
    {
        if (root == nullptr) return;

        std::queue<BinTreeNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            BinTreeNode<T> *current = q.front();
            q.pop();
            orderNodeList.push_back(current);

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
};

#endif // TREE_H
