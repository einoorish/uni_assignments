#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <algorithm>

class Heap {
private:
    int size;
    int capacity;
    int d;
    int* elements;

    // збалансуванн€ маcиву
    void heapify(int index)
	{
        while (true) {
            if (index == 0) {
                break;
            }
            int parent = (index - 1) / d;
            if (elements[index] > elements[parent]) {
                std::swap(elements[index], elements[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void heapify_d(int index)
	{
        int max_child,temporary;
        while (true) {
            if ((index * d + 1) >= size) {
                break;
            }
            max_child = -1;
            temporary = elements[index];
            for (int i = 1; i <= d; i++) {
                if (temporary < elements[index * d + i]) {
                    max_child = index * d + i;
                    temporary = elements[index * d + i];
                }
            }
            if (max_child != -1) {
                std::swap(elements[index], elements[max_child]);
                index = max_child;
            }
            else {
                break;
            }
        }
    }

public:
    Heap() = default;

    explicit Heap(int d) {
        this->d = d;
        size = 0;
        capacity = 1;
        elements = new int[capacity];
    }

    //вставити елемент
    void Insert(int data) {
        if (size == capacity) {
            int old_c = capacity;
            capacity *= 2;
            int* tmp = elements;
            elements = new int[capacity];
            std::copy(tmp, tmp + old_c, elements);
            delete[] tmp;
        }
        elements[size] = data;
        heapify(size);
        size++;
    }

    //"вит€гти" максимальний елемент
    int Extract_max()
	{
        if (size == 0) {
            return 0;
        }
        int res = elements[0];
        elements[0] = elements[size - 1];
        size--;
        heapify_d(0);
        return res;
    }

    //зб≥льшенн€ елементу за ключем
    void Increase_key(int key, int step, int index = 0)
        {
        if (elements[index] == key) {
            elements[index] += step;
            heapify(index);
            return;
        }
        for (int i = 1; i <= d; i++) {
            if (elements[index * d + i] >= key) {
                Increase_key(key, step, index * d + i);
            }
        }
    }
};
