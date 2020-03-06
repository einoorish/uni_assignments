#include <iostream>
#include "PriorityQueue.h"

int main() {
    PriorityQueue<int> pq = PriorityQueue<int>();
    pq.enqueue(4,1);
    pq.enqueue(5,2);
    pq.enqueue(6,3);
    pq.enqueue(7,0);

    pq.dequeue();
    std::cout<<pq.dequeue()<<std::endl;

    std::cout << pq;

    return 0;
}
