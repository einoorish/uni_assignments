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
    SkipList<int> list;

    for(int i = 0; i<15; i++){
        list.insert(rand()%300);
    }

    list.insert(100);
    list.insert(-40);
    list.insert(999);

    std::cout << "All lvls of the list:" << std::endl;
    list.printAllLevels();

    std::cout << "\nBottom lvl of the list:" << std::endl;
    list.printBottomLevel();

    std::cout << std::endl << "\nfind(100) returns " << list.find(100);
    std::cout << std::endl << "find(-40) returns " << list.find(-40);//returns 0
    std::cout << std::endl << "find(2000) returns " << list.find(2000);// returns -1
    std::cout << std::endl << "find(999) returns " << list.find(999);
}

int main() {

    //priorityQueue_test();

    skipList_test();

    return 0;
}
