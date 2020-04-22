#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Tree{
private:
    int data = 0;

    Tree* parent = nullptr;
    Tree* root = nullptr;
    std::vector<Tree*> children;

    Tree()= default;

    void add_child(Tree* child){
        child->parent = this;
        child->root = root;
        children.push_back(child);
    }

public:
    explicit Tree(int data) : data(data){
        if(root == nullptr)
            root = this;
    }

    void add(int value, double probability);
    void remove(int data);

    void print();
};

