// #include "smartBST.hpp"

// template <class T>
// size_t smartBST<T>::size()
// {
//     return sizeHelper(root);
// }

// // template <class T>
// // size_t smartBST<T>::height()
// // {
// //     return heightHelper(root);
// // }

// template <class T>
// void smartBST<T>::insert(const T &val)
// {
//     if (root)
//     {
//         this->addHelper(root, val);
//     }
//     else
//     {
//         root = std::make_shared<Node>(val);
//     }
// }

// template <class T>
// bool smartBST<T>::deleteValue(T val)
// {
//     return this->deleteValueHelper(nullptr, this->root, val);
// }

// template <class T>
// void smartBST<T>::print()
// {
//     printHelper(this->root);
// }

// template <class T>
// void smartBST<T>::printMaxPath()
// {
//     printMaxPathHelper(this->root);
// }