#pragma once
#include "PriorityQueue.h"

template<typename T>
void PriorityQueue_Tree<T>::push(T data, int priority) {
    pushToRoot(root, std::make_pair(data, priority));
}

template<typename T>
void PriorityQueue_Tree<T>::pop() {
    removeMax();
}

template<typename T>
T PriorityQueue_Tree<T>::top() {
    return getMax();
}

template<typename T>
void PriorityQueue_Tree<T>::print() {
    if (root == nullptr) return;
    print(root);

}

template<typename T>
void PriorityQueue_Tree<T>::pushToRoot(Node*& root, std::pair<T, int>pair) {
        if (!root) {
            root = new Node{ pair , nullptr, nullptr};
            return;
        }
        else if ((root->data.second > pair.second)|| (pair.second == root->data.second && root->data.first < pair.first))
            pushToRoot(root->left, pair);
        else
            pushToRoot(root->right, pair);
    }

template<typename T>
void PriorityQueue_Tree<T>::removeMax() {
    if (!root->right && !root->left) {
        delete root;
        return;
    } else if (!root->right) {
        Node* temp = root;
        root = root->left;
        delete temp;
        return;
    } else {
        Node* current = root;
        while (current->right->right) {
            current = current->right;
        }
        delete current->right;
        current->right = nullptr;
        return;
    }
}

template<typename T>
T PriorityQueue_Tree<T>::getMax() {
        Node* current = root;
        while (current->right)
            current = current->right;
       
        return current->data.first;
}

template<typename T>
void PriorityQueue_Tree<T>::print(Node* root) {
        if (root == nullptr)
            return;

        print(root->right);
        std::cout << '(' << root->data.first << ", " << root->data.second << ')';
        print(root->left);
}
