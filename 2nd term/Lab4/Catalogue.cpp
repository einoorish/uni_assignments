#include "Catalogue.h"

void Catalogue::print() {
    std::cout << *this << ": \n";

    int i = 0;
    Catalogue* temp = first_child;

    while(temp){
        std::cout << ++i << ". " << *temp << std::endl;
        temp = temp->next_sibling;
    }
}

std::string Catalogue::getTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return  buf;
}

void Catalogue::updateSizes(Catalogue* current, int size){
    Catalogue* temp = current;
    while(temp!= nullptr){
        temp->size+=size;
        temp = temp->parent;
    }
}

Catalogue *Catalogue::getRoot(){
    Catalogue* root = this;
    while(root->parent!= nullptr)
        root = root->parent;
    return root;
}

std::ostream &operator<<(std::ostream &stream, const Catalogue &catalogue) {
    stream << "\""<< catalogue.title << "\", size: " << catalogue.size << ", last edit: " << catalogue.last_edit_time;
    return stream;
}


void Catalogue::addFolder(std::string title) {
    if(is_file) {
        std::cout << "Cannot add children to file";
        return;
    }

    updateEditTime();

    if(first_child == nullptr){
        first_child = new Catalogue(title, 0, getTime());
        first_child->parent = this;
        return;
    }

    Catalogue* temp = this;

    temp = temp->first_child;

    while(temp->next_sibling!= nullptr)
        temp = temp->next_sibling;

    temp->next_sibling = new Catalogue(title, 0, getTime());
    temp->next_sibling->parent = this;
}

void Catalogue::addFile(std::string title, int size){

    if(is_file) {
        std::cout << "Cannot add children to file";
        return;
    }

    updateSizes(this, size);
    updateEditTime();

    if(first_child == nullptr){
        first_child = new Catalogue(title, size, getTime());
        first_child->parent = this;
        first_child->is_file = true;
        return;
    }

    Catalogue* temp = this;


    temp = temp->first_child;

    while(temp->next_sibling!= nullptr)
        temp = temp->next_sibling;

    temp->next_sibling = new Catalogue(title, size, getTime());
    temp->next_sibling->is_file = true;
    temp->next_sibling->parent = this;

}

Catalogue *Catalogue::goToHelper(std::string title, Catalogue* root){
    if(root->title == title) return root;

    Catalogue* temp = first_child;
    while(temp && temp->title != title){
        temp = temp->next_sibling;
        temp = temp->goToHelper(title, temp);
    }

    if(temp && temp->title == title)
        return temp;
    else return nullptr;
}


Catalogue *Catalogue::goTo(std::string title){
    Catalogue* root = getRoot();
    return goToHelper(std::move(title), root);
}


//is used to filter by is_file value
std::vector<Catalogue*> Catalogue::find_if(Catalogue* current, bool (*condition)(Catalogue*)){

    std::vector<Catalogue*> result;

    if(condition(current)) result.push_back(current);

vertical:
    //go until meet a leaf
    while(current->first_child!= nullptr){
        if(condition(current->first_child)) result.push_back(current->first_child);
        current = current->first_child;
    }
    
horizontal:
    //try to move to a sibling
    while(current->next_sibling!= nullptr){
        if(condition(current->next_sibling)) result.push_back(current->next_sibling);
        current = current->next_sibling;
        goto vertical;
    }
    //if met a leaf move up until found a sibling
    while(current->next_sibling == nullptr) {
        if(current->parent!= nullptr){
            current = current->parent;
            goto horizontal;
        } else return result;
    }

}

//used to filter by time
Catalogue* Catalogue::compare_all(Catalogue* current, bool (*condition)(Catalogue*,Catalogue*)){

    Catalogue* result = current;

vertical:
    //go until meet a leaf
    while(current->first_child!= nullptr){
        if(condition(current->first_child, result)) result = current->first_child;
        current = current->first_child;
    }

horizontal:
    //try to move to a sibling
    while(current->next_sibling!= nullptr){
        if(condition(current->next_sibling, result)) result = current->next_sibling;
        current = current->next_sibling;
        goto vertical;
    }
    //if met a leaf move up until found a sibling
    while(current->next_sibling == nullptr) {
        if(current->parent!= nullptr){
            current = current->parent;
            goto horizontal;
        } else return result;
    }

}
