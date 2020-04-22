#include <string>


class BinaryTree {
private:

    int data;

    BinaryTree* root = nullptr;
    BinaryTree* right = nullptr, *left = nullptr;

    void add(int value, BinaryTree* leaf);


public:
    explicit BinaryTree(const int value){
        if(root == nullptr) root = this;
        data = value;
    }
    void add(int value);
    void print();
};
