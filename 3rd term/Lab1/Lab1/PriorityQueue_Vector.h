#pragma once
#include "PriorityQueue.h"

template<typename T>
void PriorityQueue_Vector<T>::push(T data, int priority) {
    for (unsigned int i = 0; i < values.size(); i++) {
        if (priority > values[i].second || (priority == values[i].second && data < values[i].first)) {
            values.insert(values.begin() + i, std::pair<T, int>(data, priority));
            return;
        }
    }
    values.push_back(std::pair<T, int>(data, priority));
}

template<typename T>
T PriorityQueue_Vector<T>::top() {
    return values.front().first;
}

template<typename T>
void PriorityQueue_Vector<T>::pop() {
    values.erase(values.begin());
}

template<typename T>
void PriorityQueue_Vector<T>::print() {
    for (unsigned int i = 0; i < values.size(); i++) {
        std::cout << "(" << values[i].first << "," << values[i].second << ") ";
    }
}