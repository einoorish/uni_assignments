#pragma once
#include "PriorityQueue.h"
#include <iostream>


template<typename T>
void PriorityQueue_List<T>::push(T data, int priority){
	std::cout << "push from _List\n";
}

template<typename T>
void PriorityQueue_List<T>::pop() {
	std::cout << "pop from _List\n";
}

template<typename T>
T PriorityQueue_List<T>::top() {
	std::cout << "top from _List\n";
	return head->value;
}

template<typename T>
void PriorityQueue_List<T>::print() {
	std::cout << "print from _List\n";
}


