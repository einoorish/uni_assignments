#include "PriorityQueue.h"

template<typename T>
void PriorityQueue<T>::enqueue(T data, int priority) {
    Node* node = new Node(data, priority);

    if(front == nullptr){// or length == 0
        front = rear = node;
    }

    //if new node's priority is higher than the front node's
    if (rear->priority > priority) {
        // insert it before head
        node->next = rear;
        rear = node;
    } else {
        Node* current = rear, *prev;
        while(current!= nullptr &&
                current->priority < priority && current->data < data){
            prev = current;
            current = current->next;
        }
        node->next = current;
        prev->next = node;
    }

    queueSize++;
}

template<typename T>
T PriorityQueue<T>::dequeue() noexcept(false) {
    if(isEmpty()) throw std::invalid_argument("Queue is empty");
    Node* temp = front;
    T data = temp->data;
    front = temp->next;

    if (front == nullptr) rear = nullptr;
    free(temp);
    queueSize--;
    return data;
}
