#include <iostream>
#include "PriorityQueue.h"
#include "SkipList.h"
#include "SimpleSkipList.h"


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
    SimpleSkipList<int> list;

    for(int i = 0; i<30; i++){
        list.insert(rand()%200);
    }

    list.insert(30);
    list.insert(-40);
    list.insert(10);
    list.insert(50);
    list.insert(20);
    list.insert(999);

    std::cout << std::endl;
    list.printBottomLevel();

    std::cout << std::endl <<  list.find(10);// returns 1
    std::cout << std::endl <<  list.find(-40);// returns 1
    std::cout << std::endl <<  list.find(-99);// returns 0
    std::cout << std::endl <<  list.find(999);// returns 1
}

int main() {

    //priorityQueue_test();

    skipList_test();

    return 0;
}
