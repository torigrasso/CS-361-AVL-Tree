//
//  main.cpp
//  Lab4_CS361
//
//  Created by Tori Grasso on 10/3/19.
//  Copyright © 2019 Tori Grasso. All rights reserved.
//

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
// in order to do white box testing
#define private public
#include "AVLTree.hpp"
#include "BinaryTreeNode.hpp"

void testLeftSingleRotate() {
    AVLTree<int> t;
    t.insert(3);
    t.insert(2);
    t.insert(1);
    assert(t._root->_item == 2);
    assert(t._root->_left->_item == 1);
    assert(t._root->_right->_item == 3);
    
}

void testRightSingleRotate() {
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    assert(t._root->_item == 2);
    assert(t._root->_left->_item == 1);
    assert(t._root->_right->_item == 3);
}

void testLeftRightRotation(){
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    assert(t._root->_item == 4);
    assert(t._root->_left->_item == 2);
    assert(t._root->_left->_left->_item == 1);
    assert(t._root->_left->_right->_item == 3);
    assert(t._root->_right->_item == 6);
    assert(t._root->_right->_left->_item == 5);
    assert(t._root->_right->_right->_item == 7);
}

void testRightLeftRotation(){
    AVLTree<int> t;
    t.insert(7);
    t.insert(6);
    t.insert(5);
    t.insert(4);
    t.insert(3);
    t.insert(2);
    t.insert(1);
    assert(t._root->_item == 4);
    assert(t._root->_left->_item == 2);
    assert(t._root->_left->_left->_item == 1);
    assert(t._root->_left->_right->_item == 3);
    assert(t._root->_right->_item == 6);
    assert(t._root->_right->_left->_item == 5);
    assert(t._root->_right->_right->_item == 7);
}

void testPrintInorder(){
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.printInorder();
}

void testPrintPreOrder(){
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.printPreorder();
}

void testPrintPostOrder(){
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.printPostorder();
}

void testCopy(){
    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    AVLTree<int> a;
    a = t;
    assert(t._root->_item == a._root->_item);
    assert(t._root->_right->_item == a._root->_right->_item);
    assert(t._root->_left->_item == a._root->_left->_item);
}

void testFind(){
   AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    auto node = t.find(3);
    assert(node == t._root->_left->_right);
    auto node2 = t.find(5);
    assert(node2 == t._root->_right->_left);
    auto node3 = t.find(4);
    assert(node3 == t._root);
    auto NoNode = t.find(11);
    assert(NoNode == nullptr);
}

int main(int argc, const char * argv[]) {
    // rotation tests
    testLeftSingleRotate();
    testRightSingleRotate();
    testLeftRightRotation();
    testRightLeftRotation();
    
    // tree traversal tests/print outs
    std::cout << "Inorder" << endl;
    testPrintInorder();
    std::cout << " " << endl << "Preorder" << endl;
    testPrintPreOrder();
    std::cout << " " << endl << "Postorder" << endl;
    testPrintPostOrder();
    
    // copy and find tests
    testCopy();
    testFind();
}
