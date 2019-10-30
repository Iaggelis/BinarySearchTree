#include <iostream>
// #include "binary_search_tree.hpp"
#include "smartBST.hpp"
// #include "testBST.hpp"

using namespace std;

int main()
{

    // BST<int> *bst = new BST<int>();
    // bst->insert(11);
    // bst->insert(1);
    // bst->insert(6);
    // bst->insert(-1);
    // bst->insert(-10);
    // bst->insert(100);
    // bst->insert(100);
    // bst->print();
    // cout << endl;
    // cout << "Nodes count: " << bst->nodesCount();
    // cout << endl;
    // cout << "Height: " << bst->height();
    // cout << endl;
    // cout << "Max path: ";
    // bst->printMaxPath();
    // cout << endl;
    // bst->deleteValue(11);
    // cout << "11 removed: ";
    // bst->print();
    // cout << endl;
    // cout << "1 removed: ";
    // bst->deleteValue(1);
    // bst->print();
    // cout << endl;
    // cout << "-1 removed: ";
    // bst->deleteValue(-1);
    // bst->print();
    // cout << endl;
    // cout << "6 removed: ";
    // bst->deleteValue(6);
    // bst->print();
    // cout << endl;
    // cout << "-10 removed: ";
    // bst->deleteValue(-10);
    // bst->print();
    // cout << endl;
    // cout << "100 removed: ";
    // bst->deleteValue(100);
    // bst->print();
    // cout << endl;

    cout << " smart Tree:" << endl;
    // smartBST<int> tree;
    // tree.insert(11);
    // tree.insert(1);
    // tree.insert(6);
    // tree.insert(-1);
    // tree.insert(-10);
    // tree.insert(100);

    // tree.print();
    // cout << endl;
    // cout << "Nodes count: " << tree.size();
    // cout << endl;
    // cout << "Height: " << tree.height();
    // cout << endl;
    // cout << "Max path: ";
    // tree.printMaxPath();
    // cout << endl;

    ///////////////////////////////////////////////////////////
    smartBST<int> treee;
    const string file_name{"./num.txt"};

    ifstream infile;
    infile.open(file_name);
    vector<int> nums;
    if (infile.is_open())
    {
        std::string str;
        while (getline(infile, str))
        {
            nums.push_back(stoi(str));
            for (const auto &n : nums)
            {
                cout << n << '\t';
            }
            cout << '\n';
            nums.clear();
        }
    }
    for (const auto &num : nums)
    {
        treee.insert(num);
    }

    // treee.print();
    treee.printMaxPathSum();

    return 0;
}
