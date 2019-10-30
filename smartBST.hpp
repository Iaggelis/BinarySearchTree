#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

template <class T>
class smartBST
{
private:
    struct Node
    {
        T value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        Node(const T val) : value(val), left{nullptr}, right{nullptr}
        {
            parent.reset();
        }

        Node(const T val, Node left, Node right) : value(val), left{left}, right{right}
        {
            parent.reset();
        }
    };
    std::shared_ptr<Node> root;

    void addHelper(std::shared_ptr<Node> &root, const T &val)
    {
        std::shared_ptr<Node> current = root;
        std::shared_ptr<Node> parent = nullptr;
        while (current != nullptr)
        {
            parent = current;
            if (val > current->value)
            {
                current = current->right;
            }
            else if (val <= current->value)
            {
                current = current->left;
            }
        }

        current = std::make_shared<Node>(val);
        current->parent = parent;
        if (parent == nullptr)
        {
            root = current;
        }
        else if (current->value > parent->value)
        {
            parent->right = current;
        }
        else if (current->value <= parent->value)
        {
            parent->left = current;
        }
    }

    bool deleteValueHelper(std::shared_ptr<Node> parent, std::shared_ptr<Node> current, T val)
    {
        if (!current)
        {
            return false;
        }

        if (current->value == val)
        {
            if (current->left == nullptr || current->right == nullptr)
            {
                auto temp = current->left;
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
                    root = temp;
                }
            }
            else
            {
                auto validSubs = current->right;
                while (validSubs->left)
                {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            return true;
        }
        return (deleteValueHelper(current, current->left, val) ||
                deleteValueHelper(current, current->right, val));
    }

    size_t sizeHelper(std::shared_ptr<Node> &x)
    {
        return x == nullptr ? 0 : 1 + sizeHelper(x->left) + sizeHelper(x->right);
    }
    size_t heightHelper(std::shared_ptr<Node> &x)
    {
        return x == nullptr ? 0 : 1 + std::max(heightHelper(x->left), heightHelper(x->right));
    }

    void printHelper(std::shared_ptr<Node> &x)
    {
        if (x)
        {
            printHelper(x->left);
            std::cout << x->value << " ";
            printHelper(x->right);
        }
        else
        {
            return;
        }
    }

    void printMaxPathHelper(std::shared_ptr<Node> &x)
    {
        if (!x)
        {
            return;
        }
        std::cout << x->value << " ";
        if (heightHelper(x->left) > heightHelper(x->right))
        {
            printMaxPathHelper(x->left);
        }
        else
        {
            printMaxPathHelper(x->right);
        }
    }

    T printMaxPathSumHelper(std::shared_ptr<Node> &x, T &sum)
    {
        if (!x)
        {
            return 0;
        }
        sum += x->value;
        std::cout << sum << '\n';
        if (heightHelper(x->left) >= heightHelper(x->right))
        {
            printMaxPathSumHelper(x->left, sum);
        }
        else
        {
            printMaxPathSumHelper(x->right, sum);
        }
        return sum;
    }

    void traversal_inorder_helper(std::shared_ptr<Node> &x)
    {
        if (x == nullptr)
        {
            return;
        }
        traversal_inorder_helper(x->left);
        std::cout << x->value << '\n';
        traversal_inorder_helper(x->right);
    }

public:
    smartBST() {}
    size_t size()
    {
        return sizeHelper(root);
    }

    size_t height()
    {
        return heightHelper(root);
    }

    void insert(const T &val)
    {
        if (root)
        {
            this->addHelper(root, val);
        }
        else
        {
            root = std::make_shared<Node>(val);
        }
    }

    bool deleteValue(T val)
    {
        return this->deleteValueHelper(nullptr, root, val);
    }

    void print()
    {
        printHelper(root);
    }

    void printMaxPath()
    {
        printMaxPathHelper(root);
    }

    T printMaxPathSum()
    {
        static T sum = 0;
        return printMaxPathSumHelper(root, sum);
    }

    void traversal_inorder_recursive()
    {
        traversal_inorder_helper(root);
    }

    void traversal_inorder_iterative()
    {
        if (!root)
        {
            return;
        }

        std::stack<std::shared_ptr<Node>> traversal;
        std::shared_ptr<Node> current = root;
        bool complete = false;

        while (!complete)
        {
            if (current != nullptr)
            {
                traversal.push(current);
                current = current->left;
            }
            else if (!traversal.empty())
            {
                current = traversal.top();
                traversal.pop();
                std::cout << current->value << '\n';
                current = current->right;
            }
            else
            {
                complete = true;
            }
        }
    }

    // void fromfile(std::string file_name)
    // {
    //     std::ifstream infile;
    //     infile.open(file_name);

    //     if (infile.is_open())
    //     {
    //         T num;
    //         std::string str;
    //         while (getline(infile, str))
    //         {
    //             std::cout << stoi(str) << '\n';
    //             this->insert(1);
    //         }
    //     }
    //     // infile.close();
    // }
};