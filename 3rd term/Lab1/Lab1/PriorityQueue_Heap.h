#pragma once
#include "PriorityQueue.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

template<typename T>
int PriorityQueue_Heap<T>::getParent(unsigned int index) {
    if ((index > 0) && (index < heap.size())) {
        return index / 2;
    }
    return -1;
}

template<typename T>
bool PriorityQueue_Heap<T>::isLhsBigger(int index1, int index2) {
    return heap[index1].second > heap[index2].second ||
        (heap[index1].second == heap[index2].second && heap[index1].first < heap[index2].first);
}

template<typename T>
void PriorityQueue_Heap<T>::heapifyUp(std::pair<T, int> pair) {
    unsigned int index = heap.size()-1;
    heap[index] = pair;
    while (index > 0 && isLhsBigger(index, getParent(index))) {
       swap(heap[index], heap[getParent(index)]);
       if(2 * index + 1 < heap.size() && !isLhsBigger(2 * index, 2 * index + 1))
           swap(heap[2 * index], heap[2 * index+1]);
       index = getParent(index);
    }
}

template<typename T>
void PriorityQueue_Heap<T>::maxHeapify(int index){
    unsigned int largest = index;
    unsigned int left = 2 * index;
    unsigned int right = 2 * index + 1;
    
    if (left < heap.size() && isLhsBigger(left, index))
        largest = left;

    if (right < heap.size() && isLhsBigger(right, largest))
        largest = right;

    if (largest != index){
        swap(heap[index], heap[largest]);
        maxHeapify(largest);
    }
}

template<typename T>
T PriorityQueue_Heap<T>::top() {
    return heap[0].first;
}

template<typename T>
void  PriorityQueue_Heap<T>::pop() {
    if (heap.size() == 0) throw std::invalid_argument("Queue is empty\n");

    heap[0].first = heap[heap.size()-1].first;
    heap[0].second = heap[heap.size()-1].second;
    heap.pop_back();
    maxHeapify(0);
}


template<typename T>
void PriorityQueue_Heap<T>::push(T value, int priority) {
    heap.push_back(std::make_pair(INT_MAX, INT_MIN));
    heapifyUp(std::make_pair(value,priority));
}

template<typename T>
void PriorityQueue_Heap<T>::print() {
    for (unsigned int i = 0; i < heap.size(); i++)
        std::cout << '(' << heap[i].first << ", " << heap[i].second << ") " ;
}
