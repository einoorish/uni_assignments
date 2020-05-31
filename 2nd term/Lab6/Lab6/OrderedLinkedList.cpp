#include "OrderedLinkedList.h"
#include <iostream>

void OrderedLinkedList::add(Ñoordinates coords){

    Node* current = first;
    size++;

    if (current == nullptr) {
        Node* new_node = new Node(coords, nullptr, nullptr);
        first = new_node;
        last = new_node;
        return;
    }
    
    while (current) {
        if (coords > current->coords) {
            Node* newNode = new Node(coords, current->prev, current);

            if (current->prev != nullptr) {
                current->prev->next = newNode;
            } else {
                first = newNode;
            }

            current->prev = newNode;
            return;
        }
        current = current->next;
    }

    //if did not reach return statement then new node is the smallest end should be at the end
    Node* new_node = new Node{coords, last, nullptr};
    last->next = new_node;
    last = new_node;
}

void OrderedLinkedList::remove(int index) {
    if (index > size - 1) { std::cout << "Invalid index." << std::endl; return; }
    
    size--;

    if (index == 0) {
        Node* temp = first;
        first = first->next;
        first->prev = nullptr;
        delete temp;
    }
    else if (index == size - 1) {
        Node* temp = last;
        temp->prev->next = nullptr;
        last = temp->prev;
        delete temp;
    }
    else {
        Node* current = first;
        int i = 0;
        while (i != index - 1) {
            current = current->next;
            i++;
        }
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
}

int OrderedLinkedList::find(Ñoordinates value) {
    int index = 0;
    Node* current = first;
    while (current) {
        if (current->coords == value) {
            return index;
        }
        else {
            current = current->next;
            index++;
        }
    }
    return -1;
}

std::vector<Ñoordinates*> OrderedLinkedList::find(Ñoordinates start, Ñoordinates end) {
    std::vector<Ñoordinates*> result;
    if (start > end) return result;

    Node* current = first;

    while (current) {
        if (current->coords > start && current->coords < end) {
            result.push_back(&current->coords);
        }
        current = current->next;
    }
    return result;
}


void OrderedLinkedList::print() {
    Node* head = first;
    while (head) {
        std::cout << head->coords << " ";
        head = head->next;
    }
}


OrderedLinkedList::~OrderedLinkedList(){
    Node* head = first;
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    first = last = nullptr;
}

