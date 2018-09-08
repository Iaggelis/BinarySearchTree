#include "binary_search_tree.hpp"


size_t smartBST::size()
{
    return sizeHelper(root);
}

size_t smartBST::height()
{
    return heightHelper(root);
}

void smartBST::insert(const T &val)
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

bool smartBST::deleteValue(T val)
{
    return this->deleteValueHelper(nullptr, this->root, val);
}

void smartBST::print()
{
    printHelper(this->root);
}

void smartBST::printMaxPath()
{
    printMaxPathHelper(this->root);
}