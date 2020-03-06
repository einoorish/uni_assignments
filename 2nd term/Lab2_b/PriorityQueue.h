#include <iostream>

#ifndef LAB2_B_PRIORITYQUEUE_H
#define LAB2_B_PRIORITYQUEUE_H

//<T extends Comparable> equivalent?
template <typename T>
class PriorityQueue {

    private:
        size_t queueSize = 0;

        struct Node{
            T data;
            int priority;
            Node *next = nullptr;

            Node(T data, int priority) : data(data), priority(priority) {}
        };
        Node* rear = nullptr; // enqueue
        Node* front = nullptr; // dequeue

    public:
        bool isEmpty() const {return queueSize == 0;}
        void enqueue(T data, int priority);
        T dequeue() noexcept(false);
        friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& stack){
            Node* current = stack.front;
            while(current != nullptr){
                std::cout << current->data << "  ";
                current=current->next;
            }
            return os;
        }
};


#endif //LAB2_B_PRIORITYQUEUE_H
