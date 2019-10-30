#pragma once

#include <cmath>
#include <climits>
#include <memory>
#include <stack>

constexpr int INF = INT_MAX;

template <class T>
class BST
{
private:
    struct Node
    {
        T value;
        Node *left;
        Node *right;

        Node(T val)
        {
            this->value = val;
        }

        Node(T val, Node left, Node right)
        {
            this->value = val;
            this->left = left;
            this->right = right;
        }
    };

    Node *root;

    void addHelper(Node *root, T val)
    {
        if (root->value > val)
        {
            if (!root->left)
            {
                root->left = new Node(val);
            }
            else
            {
                addHelper(root->left, val);
            }
        }
        else
        {
            if (!root->right)
            {
                root->right = new Node(val);
            }
            else
            {
                addHelper(root->right, val);
            }
        }
    }

    void printHelper(Node *root)
    {
        if (root)
        {
            printHelper(root->left);
            std::cout << root->value << " ";
            printHelper(root->right);
        }
        else
        {
            return;
        }
    }

    int nodesCountHelper(Node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            return (1 + nodesCountHelper(root->left) + nodesCountHelper(root->right));
        }
    }
    int heightHelper(Node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            return (1 + std::max(heightHelper(root->left), heightHelper(root->right)));
        }
    }

    void printMaxPathHelper(Node *root)
    {
        if (!root)
        {
            return;
        }
        std::cout << root->value << ' ';
        if (heightHelper(root->left) > heightHelper(root->right))
        {
            printMaxPathHelper(root->left);
        }
        else
        {
            printMaxPathHelper(root->right);
        }
    }

    bool deleteValueHelper(Node *parent, Node *current, T value)
    {
        if (!current)
        {
            return false;
        }

        if (current->value == value)
        {
            if (current->left == nullptr || current->right == nullptr)
            {
                Node *temp = current->left;
                if (current->right)
                {
                    temp = current->right;
                }

                if (parent)
                {
                    if (parent->left == current)
                    {
                        parent->left = temp;
                    }
                    else
                    {
                        parent->right = temp;
                    }
                }
                else
                {
                    this->root = temp;
                }
            }
            else
            {
                Node *validSubs = current->right;
                while (validSubs->left)
                {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return (deleteValueHelper(current, current->left, value) ||
                deleteValueHelper(current, current->right, value));
    }

public:
    BST(){};
    void insert(T val)
    {
        if (root)
        {
            this->addHelper(root, val);
        }
        else
        {
            root = new Node(val);
        }
    };
    // bool search(T);

    void print()
    {
        printHelper(this->root);
    }

    int nodesCount()
    {
        return nodesCountHelper(root);
    }

    int height()
    {
        return heightHelper(this->root);
    }

    void printMaxPath()
    {
        printMaxPathHelper(this->root);
    }

    bool deleteValue(T value)
    {
        return this->deleteValueHelper(nullptr, this->root, value);
    }
};
