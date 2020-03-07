#include <iostream>
#include "PriorityQueue.h"

void priorityQueue_test(){
    PriorityQueue<int> pq = PriorityQueue<int>();
    try{
        pq.dequeue();
    } catch (std::exception& e ){
        std::cout<< e.what();
    }
    pq.enqueue(4,1);
    pq.enqueue(5,2);
    pq.enqueue(6,3);
    pq.enqueue(7,0);

    pq.dequeue();
    pq.enqueue(2,1);
    std::cout<<pq.dequeue()<<std::endl;

    std::cout << pq;
}

int main() {

        priorityQueue_test();

    return 0;
}
