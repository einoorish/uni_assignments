#pragma once
#include "Ñoordinates.h"
#include <vector>

class OrderedLinkedList {

    struct Node {
        Ñoordinates coords;
        Node* prev;
        Node* next;
        Node(Ñoordinates coords, Node* prev, Node* next) :coords(coords), prev(prev), next(next) {};
    };


    Node* first = nullptr;
    Node* last = nullptr;

    int size;

public:
    OrderedLinkedList() : size(0) {}
    static OrderedLinkedList create_empty() { return OrderedLinkedList(); };
    void add(Ñoordinates coords);
    void remove(int index);
    int find(Ñoordinates coords);
    std::vector<Ñoordinates*> find(Ñoordinates begin, Ñoordinates end);
    void print();
    ~OrderedLinkedList();

};

