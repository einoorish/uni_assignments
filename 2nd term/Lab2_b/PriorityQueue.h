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
        void enqueue(T data, int priority){
            Node* node = new Node(data, priority);
            queueSize++;

            if(front == nullptr){// or length == 0
                front = rear = node;
                return;
            }

            //if new node's priority is higher than the front's...
            if (front->priority > priority || (front->priority == priority && front->data > data)) {
                // insert it as first (before head)
                node->next = front;
                front = node;
            }
            //if new node's priority is lower than the rear's...
            else if (rear->priority < priority|| (rear->priority == priority && rear->data < data)){
                // insert it as last (after rear)
                rear->next = node;
                rear = node;
            }
            //else it should be inserted somewhere in the middle
            else {
                Node* current = rear, *prev;
                while(current!= nullptr &&
                      current->priority < priority && current->data < data){
                    prev = current;
                    current = current->next;
                }
                node->next = current;
                prev->next = node;
            }

        }
        T dequeue() noexcept(false){
            if(isEmpty()) throw std::invalid_argument("Queue is empty\n");
            Node* temp = front;
            T data = temp->data;
            front = temp->next;

            if (front == nullptr) rear = nullptr;
            free(temp);
            queueSize--;
            return data;
        }
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
