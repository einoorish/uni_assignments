#include <iostream>
#include "BinaryTree.h"

void BinaryTree::add(int value)  {
    if(root == nullptr){
        root = this;
        data = value;
        return;
    }
    add(value, root);
}


void BinaryTree::add(const int value, BinaryTree* node){

    if(value < node->data){
        if(node->left != nullptr) {
            add(value, node->left);
        } else {
            node->left = new BinaryTree(value);
            node->left->root = node;
        }

    } else if(value >= node->data) {
        if (node->right != nullptr) {
            add(value, node->right);
        } else {
            node->right = new BinaryTree(value);
            node->right->root = node;
        }
    }
}

void BinaryTree::print() {
    std::cout << data;
    if(left != nullptr && right != nullptr) {
        std::cout << "(";
        left->print();
        std::cout << ", ";
        right->print();
        std::cout << ")";
    }
    else if(left == nullptr && right != nullptr) {
        std::cout << "( -, ";
        right->print();
        std::cout << ")";
    }
    else if(left != nullptr && right == nullptr) {
        std::cout << "(";
        left->print();
        std::cout << ", -)";
    }
}
