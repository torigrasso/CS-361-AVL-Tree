//
//  AVLTree.hpp
//  Lab4_CS361
//
//  Created by Tori Grasso on 10/3/19.
//  Copyright © 2019 Tori Grasso. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>

#include "BinaryTreeNode.hpp"

template <typename T>
class AVLTree {
public:
    AVLTree();

    AVLTree(const AVLTree &source);

    AVLTree& operator=(const AVLTree &source);

    /// inserts item into the tree
    /// @param item item to be inserted
    void insert(const T &item);

    /// finds the node with the specified item
    /// @param item value to find in the tree
    /// @return the node where item is or nullptr if item is not in the tree
    std::shared_ptr<BinaryTreeNode<T>> find(const T &item);

    int size() const { return _size; }


    /// outputs the tree items use preorder traversal
    void printPreorder();

    /// outputs the tree items use inorder traversal
    void printInorder();

    /// outputs the tree items use postorder traversal
    void printPostorder();

private:
    // MARK: private helper methods

    /// makes a deepcopy of the subtree rooted at rootNode
    /// @param rootNode root of the subtree that it makes a deep copy of
    /// @return newly created deep copy of the rootNode subtree
    std::shared_ptr<BinaryTreeNode<T>> _copyNodes(const std::shared_ptr<BinaryTreeNode<T>> &rootNode);


    /// inserting item into the tree rooted at node
    /// @param node root of the subtree to insert item into
    /// @param item value to insert into tree
    void _insertHelp(std::shared_ptr<BinaryTreeNode<T>> &node, const T &item);

    /// see book for rotation details
    void _leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _leftRightRotate(std::shared_ptr<BinaryTreeNode<T>> &node);


    /// return node of subtree containing item
    /// @param node root of subtree to search for the item
    /// @param item value to find
    std::shared_ptr<BinaryTreeNode<T>> _findHelp(const std::shared_ptr<BinaryTreeNode<T>> &node, const T &item);

    /// helpers for tree traversals
    void printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);
    void printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);
    void printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);


    // MARK: data
    /// root of the tree
    std::shared_ptr<BinaryTreeNode<T>> _root;
    // number of elements in the tree
    int _size;
};

// maximum function for use with tree heights
inline int max(int a, int b)
{
    return a > b ? a : b;
}

// constructor
template <typename T>
AVLTree<T>::AVLTree() {
    _root = nullptr;
    _size = 0;
}

// copy constructor
template <typename T>
AVLTree<T>::AVLTree(const AVLTree &source){
    _root = _copyNodes(source._root);
    _size = source._size;
}

// assignment operator
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree &source){
    if (this != &source){
        _root = _copyNodes(source._root);
        _size = source._size;
    }
    return *this;
}

// insert item into tree
template <typename T>
void AVLTree<T>::insert(const T &item){
    _insertHelp(_root, item);
    _size++;
}
// finds the node with the specified item
template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::find(const T &item){
    return _findHelp(_root, item);
}

// outputs the tree items using preorder traversal
template <typename T>
void AVLTree<T>::printPreorder(){
    printPreorderHelp(_root);
}

// outputs the tree items using inorder traversal
template <typename T>
void AVLTree<T>::printInorder(){
    printInorderHelp(_root);
}


// outputs the tree items using postorder traversal
template <typename T>
void AVLTree<T>::printPostorder(){
    printPostorderHelp(_root);
}

/// Private Methods -------------------------------------------------------------------------------------------------------------------

// makes a deepcopy of the subtree rooted at rootNode
template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::_copyNodes(const std::shared_ptr<BinaryTreeNode<T>> &rootNode){
    //_size = rootNode._size;
    if (rootNode == nullptr){
        return nullptr;
    }
    else{
        // making a new shared pointer
        auto newNode = std::make_shared<BinaryTreeNode<T> >(rootNode->_item);
        // recursive call for copying both left and right of the tree
        newNode->_left =  _copyNodes(rootNode->_left);
        newNode->_right =  _copyNodes(rootNode->_right);
        return newNode;
    }

}

// inserting item into the tree rooted at node
template <typename T>
void AVLTree<T>::_insertHelp(std::shared_ptr<BinaryTreeNode<T>> &node, const T &item){
    // if node is the root
    //if( _size == 0){   maybe not bc root can change. need to figure out.
   //     _root = node;
 //   }
    // if node is null insert
    if (node == nullptr){
        node = std::make_shared<BinaryTreeNode<T> >(item);
    }
    // if the node's item is greater than the new item's value
    else if (item < node->_item){
        // recursive call
        _insertHelp(node->_left, item);
        // left subtree height could be bigger than the right subtree
        if (getHeight(node->_left) - getHeight(node->_right) == 2){
            // figure out which subtree has the new value
            if (item < node->_left->_item){
                // call left single rotate to balance out the tree
                _leftSingleRotate(node);
            }
            else{
                // call the right left rotate to balance out the tree
                _rightLeftRotate(node);
            }
        }
    }
    else{
        _insertHelp(node->_right, item);
        // right subtree height could be bigger than the left subtree
        if (getHeight(node->_right) - getHeight(node->_left) == 2){
            // figure out which subtree has the new value
            if (item > node->_right->_item){
                // call right single rotate to balance out the tree
                _rightSingleRotate(node);
            }
            else{
                // call the left right rotate to balance out the tree
                _leftRightRotate(node);
            }
        }
    }
    node->_height = (max(getHeight(node->_left), getHeight(node->_right))) + 1;
}

template <typename T>
void AVLTree<T>::_leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node){
    auto grandparent = node;
    auto parent = node->_left;
    
    // grandparents left becomes parents right and then the parents right goes to grandparent
    grandparent->_left = parent->_right;
    parent->_right = grandparent;
    node = parent;
    
    // set the heights
    grandparent->_height = max(getHeight(grandparent->_left), getHeight(grandparent->_right)) + 1;
    parent->_height = max(getHeight(parent->_left), getHeight(parent->_right)) + 1;
}

template <typename T>
void AVLTree<T>::_rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node){
    auto grandparent = node;
    auto parent = node->_right;
    
    // grandparents right becomes parents left and then the parents left goes to grandparent
    grandparent->_right = parent->_left;
    parent->_left = grandparent;
    node = parent;
    
    // set the heights
    grandparent->_height = max(getHeight(grandparent->_right), getHeight(grandparent->_left)) + 1;
    parent->_height = max(getHeight(parent->_right), getHeight(parent->_left)) + 1;
}

template <typename T>
void AVLTree<T>::_rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>> &node){
    _rightSingleRotate(node->_left);
    _leftSingleRotate(node);
}

template <typename T>
void AVLTree<T>::_leftRightRotate(std::shared_ptr<BinaryTreeNode<T>> &node){
    _leftSingleRotate(node->_right);
    _rightSingleRotate(node);
}

// return node of subtree containing item
template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::_findHelp(const std::shared_ptr<BinaryTreeNode<T>> &node, const T &item){
    if (item == node->_item){
        return node;
    }
    // if item is less than the root go to the left side of the tree
    else if(item < node->_item){
        // if the item is not in the tree
        if(node->_left == nullptr){
            return nullptr;
        }
        else{
            // recursive call to keep searching
            return _findHelp(node->_left, item);
        }
    }
    // if item is greater than the root go to the right side of the tree
    else{
       // if the item is not in the tree
        if(node->_right == nullptr){
            return nullptr;
        }
        else{
            // recursive call to keep searching
            return _findHelp(node->_right, item);
        }
    }
}

template <typename T>
void AVLTree<T>::printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node){
    // if tree is not empty
    if (node != nullptr){
        printInorderHelp(node->_left);
        // prints out each item
        std::cout << node->_item << endl;
        printInorderHelp(node->_right);
    }
    else if (_size == 0){
        //print that the tree is empty
        std::cout << "There is nothing in this tree, so the Inorder is unavailable";
    }
}

template <typename T>
void AVLTree<T>::printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node){
    // if tree is not empty
    if (node != nullptr){
        // prints out each item
        std::cout << node->_item << endl;
        printPreorderHelp(node->_left);
        printPreorderHelp(node->_right);
    }
    else if (_size == 0){
        //print that the tree is empty
        std::cout << "There is nothing in this tree, so the Preorder is unavailable";
    }
}

template <typename T>
void AVLTree<T>::printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node){
    // if tree is not empty
    if (node != nullptr){
        printPostorderHelp(node->_left);
        printPostorderHelp(node->_right);
        // prints out each item
        std::cout << node->_item << endl;
    }
    else if (_size == 0){
      //print that the tree is empty
        std::cout << "There is nothing in this tree, so the Postorder is unavailable";
    }
}

#endif /* AVLTree_hpp */
