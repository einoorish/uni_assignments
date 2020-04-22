#include "Tree.h"

void Tree::add(const int value, double probability)  {

    //roulette wheel selection
    Tree* current_node = this;
    Tree* new_node = new Tree(value);

    srand( (unsigned)time(0));
    int random_number = rand()%100;

    //deside whether add to this node or its child
    if(probability*100 - random_number > 0){
        //add to this
        current_node->add_child(new_node);
    } else {
        //add to child

        int children_count = current_node->children.size();

        while(children_count!=0){

            //choose random child
            random_number = rand()%children_count;
            current_node = current_node->children.at(random_number);

            //decide whether to add to this node or its child
            probability = 1 - probability;
            random_number = rand()%100;
            if(probability*100 - random_number > 0) {
                //add to this
                current_node->add_child(new_node);
                return;
            }

            //update children count for the next loop
            children_count = current_node->children.size();
        }

        //add to this if there're no children
        current_node->add_child(new_node);
    }
}

void Tree::print() {
    std::cout << data;
    if (!(children.empty())) {
        std::cout << " {";
        children.at(0)->print();
        for (int i = 1; i < children.size(); i++) {
            std::cout << ", ";
            children.at(i)->print();
        }
        std::cout << "}";
    }
}

void Tree::remove(const int value) {
    Tree* currentNode = this;

    //if leaf node is getting removed
    if(this->data == value && this->children.empty()){
        //if it's not root node
        if(this->parent!= nullptr){
            for(int i = 0; i < parent->children.size(); i++){
                if(parent->children.at(i)->data == value)
                    parent->children.erase(parent->children.begin() + i);
            }
        }
        delete this;
        return;
    }

    //if non-leaf node is getting removed
    while (this->data == value  && !this->children.empty()){
        currentNode = children.at(0);

        for(int i = 1; i < children.size(); ++i)
            currentNode->add_child(children.at(i));

        *this = *currentNode;
    }

    //rearrange children of the removed node
    for(auto & i : currentNode->children){
        i->remove(value);
    }
}

