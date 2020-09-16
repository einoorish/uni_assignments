#pragma once
#include "PriorityQueue.h"
#include <iostream>

 
template<typename T>
void PriorityQueue_List<T>::push(T data, int priority){
	if(!front) {
		front = rear = new Node{ data, priority };
		return;
	}

	Node* temp = front;
	if(front->priority < priority || (front->priority == priority && front->value >= data)) {
		front = new Node{ data, priority, front };
	}
	else if (rear->priority > priority || (rear->priority == priority && rear->value <= data)) {
		Node* newNode = new Node{ data, priority };
		rear->next = newNode;
		rear = newNode;
	} 
	else {
		while(temp->next && (priority < temp->next->priority || data > temp->next->value))
			temp = temp->next;

		temp->next = new Node{ data, priority, temp->next };
	}

}

template<typename T>
void PriorityQueue_List<T>::pop() {
	if (!front) throw std::invalid_argument("Queue is empty\n");
	Node* temp = front;
	front = temp->next;

	if (front == nullptr) rear = nullptr;
	free(temp);
}

template<typename T>
T PriorityQueue_List<T>::top() {
	if (front) {
		return front->value;
	}
	else throw std::underflow_error("Queue is empty");
}

template<typename T>
void PriorityQueue_List<T>::print() {
	Node* current = front;
	while (current != nullptr)
	{
		std::cout << "(" << current->value << "; " << current->priority << ")" << std::endl;
		current = current->next;
	}
}


