#pragma once
#include "PriorityQueue.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <random>


class DemoMode {
private:

    void listDemo() {
        PriorityQueue<int>* queue = new PriorityQueue_List<int>();
        std::cout << "Pushing pairs(value, priority): (10,1), (8, 1), (12, 1), (2, 2), (3,0), (3,0)" << std::endl;
        queue->push(10, 1);
        queue->push(8, 1);
        queue->push(12, 1);
        queue->push(2, 2);
        queue->push(3, 0);
        queue->push(3, 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "Queue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }

public:

    void startDemoMode() {
        int queueType;

        std::cout << "Choose queue type: 1 - List" << std::endl;
        std::cin >> queueType;

        //TODO: check if input is valid; 

        switch (queueType) {
        case 1: {
            listDemo();
            break;
        }
        }

    }




};

