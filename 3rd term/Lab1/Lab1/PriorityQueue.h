#pragma once
#include "Date.h"
#include <vector>
#include <iostream>

template <typename T>
class PriorityQueue {
public:
	virtual void push(T data, int priority) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
	virtual void print() = 0;
};


template <typename T>
class PriorityQueue_List : public PriorityQueue<T> {

private:
	struct Node {
		T value;
		int priority;
		Node* next = nullptr;
	};
	Node* front = nullptr, *rear = nullptr;

public:
	PriorityQueue_List() = default;
	void push(T data, int priority) override; 
	void pop() override;
	T top() override;
	void print() override;
};


template <typename T>
class PriorityQueue_Vector : public PriorityQueue<T> {
private:
	std::vector<std::pair<T, int>>  values;
public:
	PriorityQueue_Vector() = default;
	void push(T data, int priority) override;
	T top() override;
	void pop() override;
	void print() override;
};

template <typename T>
class PriorityQueue_Tree : public PriorityQueue<T> {
private:
	struct Node {
		std::pair<T, int> data;
		Node* right, * left;
	};

	Node* root = nullptr;

	void pushToRoot(Node*& root,std::pair<T, int>pair);
	void removeMax();
	T getMax();
	void print(Node* node);
public:
	void push(T data, int priority) override;
	T top() override;
	void pop() override;
	void print() override;
};

template <typename T>
class PriorityQueue_Heap : public PriorityQueue<T> {
private:
	std::vector<std::pair<int,T>> heap;

	int getParent(unsigned int index);
	void maxHeapify(int index);
	void heapifyUp(std::pair<T, int> pair);
	bool isLhsBigger(int index1, int index2);

public:
	void push(T data, int priority) override;
	T top() override;
	void pop() override;
	void print() override;
};

template <typename T>
class PriorityQueue_AVL : public PriorityQueue<T> {
};


#include "PriorityQueue_List.h"
#include "PriorityQueue_Vector.h"
#include "PriorityQueue_Tree.h"
#include "PriorityQueue_Heap.h"
