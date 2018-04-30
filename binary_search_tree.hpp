#pragma once

#include <cmath>
#include <memory>

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
            else if (val < current->value)
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
        else if (current->value < parent->value)
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
                    this->root = temp;
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
        return this->deleteValueHelper(nullptr, this->root, val);
    }

    void print()
    {
        printHelper(this->root);
    }

    void printMaxPath()
    {
        printMaxPathHelper(this->root);
    }
};