#pragma once
#include "PriorityQueue.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <random>


class DemoMode {
private:

    void _ListDemo() {
        PriorityQueue<int>* queue = new PriorityQueue_List<int>();
        std::cout << "Pushing pairs(value, priority): (10,1), (8, 1), (12, 1), (2, 2), (3,0), (3,0)" << std::endl;
        queue->push(10, 1);
        queue->push(8, 1);
        queue->push(12, 1);
        queue->push(2, 2);
        queue->push(3, 0);
        queue->push(3, 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }


    void _VectorDemo() {
        PriorityQueue<Date>* queue = new PriorityQueue_Vector<Date>();
        std::cout << "Pushing pairs(value, priority):  ({12,3,2005,3,25}, 1), ({1,5,1995,0,4}, 1), ({12,3,1789,3,25}, 1), ({2,7,998,1,15 }, 2), ({21,11,1544,18,40 }, 0), ({ 1,5,1995,10,4 }, 0) " << std::endl;
        queue->push(Date{12,3,2005,3,25}, 1);
        queue->push(Date{1,5,1995,0,4}, 1);
        queue->push(Date{12,3,1789,3,25}, 1);
        queue->push(Date{2,7,998,1,15}, 2);
        queue->push(Date{21,11,1544,18,40}, 0);
        queue->push(Date{ 1,5,1995,10,4 }, 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }

public:

    void startDemoMode() {
        int queueType;

        std::cout << "Choose queue type: 1 - List, 2 - Vector" << std::endl;
        std::cin >> queueType;

        //TODO: check if input is valid; 

        switch (queueType) {
        case 1: {
            _ListDemo();
            break;
        }
        case 2: {
            _VectorDemo();
            break;
        }
        }

    }




};

