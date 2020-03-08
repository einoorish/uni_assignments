#include <iostream>
#include "PriorityQueue.h"
#include "SkipList.h"

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

void skipList_test(){
    SkipList<int> list;

    list.insert(3);
    list.insert(63);
    list.insert(13);
    list.insert(33);
    list.insert(43);
    list.insert(56);
    list.insert(70);

    list.printAllLevels();

    std::cout << list.find(63)->data;
}

int main() {

    //priorityQueue_test();

    skipList_test();

    return 0;
}
