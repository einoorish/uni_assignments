#include <random>
#include <iomanip>
#include <iostream>
extern const int MAX_LVL = 5;

template <typename T>
class SkipList {

public: struct Node;
    Node* head = nullptr;

private:
    int getRandomLvl(){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, MAX_LVL-1); // define the range

        return distr(eng);
    }
    int insertNodeAtLvls(Node* prev, Node* node){

        //we want to make sure prev is the max lesser element before calling another recursion
        int old_distance = prev->distance;

        //if new element should be placed right before previous - > all bottom lvls will have width = 1
        if(old_distance==1){
//                     if(prev->down==nullptr){
//                         node->distance = 1;
//                         node->next = prev->next;
//                         prev->next = node;
//                         return 1;
//                     }
            while(prev->down != nullptr){
                node->distance = 1;
                node->next = prev->next;
                prev->next = node;

                node->down = new Node(node->data);
                node = node->down;
                prev=prev->down;
            }
            node->distance = 1;
            node->next = prev->next;
            prev->next = node;
            return 1;
        }
        else {
            old_distance+=1;
            node->distance = old_distance;

            while(prev->next!= nullptr && prev->next->data <= node->data){
                //if(node->distance!=1)
                node->distance--;
                prev=prev->next;
            }
            node->distance++;
            prev->distance = old_distance-node->distance;

            node->next = prev->next;
            prev->next = node;

            if(prev->down == nullptr) return 1;

            Node* lower_node = new Node(node->data);
            node->down = lower_node;
            if(node->next == nullptr) {
                node->distance = old_distance-prev->distance+1;
                insertNodeAtLvls(prev->down, lower_node);
            }
            else node->distance = insertNodeAtLvls(prev->down, lower_node);
            return old_distance-lower_node->distance;

        }
    }
    void insertFirst(Node* node) {
        if(head!= nullptr) {
            Node *old_head = head;
            node->next = old_head;
            head = node;

            node->distance = 1;
            old_head = old_head->down;

            while(old_head!= nullptr) {
                Node* lower_node = new Node(node->data);
                node->down = lower_node;
                lower_node->next = old_head;
                old_head=old_head->down;
                node = lower_node;
            }
        } else {
            head = node;
            node->distance = 1;

            for(int i = 0; i<MAX_LVL-1; i++){
                node->down = new Node(node->data);
                node = node->down;
                node->distance = 1;

            }
        }
    }

    int insertAtThisAndBottomLvl(Node* prev, Node* node){
        //we want to make sure prev is the max lesser element before calling another recursion
        int old_distance = prev->distance + 1;
        node->distance = old_distance;

        while(prev->next!= nullptr && prev->next->data <= node->data){
            //if(node->distance!=1)
            node->distance--;
            prev=prev->next;
        }
        node->distance++;
        prev->distance = old_distance-node->distance;

        node->next = prev->next;
        prev->next = node;

        if(prev->down == nullptr) return 1;

        Node* lower_node = new Node(node->data);
        node->down = lower_node;
        if(node->next == nullptr) {
            node->distance = old_distance-prev->distance+1;
            insertNodeAtLvls(prev->down, lower_node);
        }
        else node->distance = insertNodeAtLvls(prev->down, lower_node);
        return old_distance-lower_node->distance;

    }

public: struct Node{
        T data;
        Node *next = nullptr;
        Node *down = nullptr;
        int distance = 1;

        Node()= default;
        explicit Node(T data) : data(data){}

    };

    void insert(T data){
        //creating new node with random lvl = MAX_LVL - how_many_lvls_from_top
        Node* node = new Node(data);
        int how_many_lvls_from_top = getRandomLvl();
        int node_lvl = how_many_lvls_from_top;

        // insert first if the list is empty or the head has lower value
        if(head == nullptr || head->data >= data) {
            insertFirst(node); return;
        }

        //else iterate through the list
        Node* curr = head;

        while(curr!= nullptr) {

            //move right until the proper interval is found
            while(curr->next!= nullptr && curr->next->data < node->data){
                curr=curr->next;
            }

            if(how_many_lvls_from_top==0){

                if(node_lvl == 0 || curr->distance==1) {
                    while (curr->down != nullptr) {
                        node->next = curr->next;
                        curr->next = node;

                        node->down =new Node(data);
                        curr->next = node;

                        node = node->down;
                        curr = curr->down;
                    }
                    node->next = curr->next;
                    curr->next = node;
                    return;
                }

                //to fix distance value at lvls higher than the curr
                Node* temp = head;
                int curr_width = curr->distance;

                //TODO:smth
                while(temp->data!=curr->data && temp->down!= nullptr) {
                    while (temp->next != nullptr && temp != curr) {
                        temp = temp->next;
                        curr_width--;
                    }
                    temp->distance += curr_width;
                    temp=temp->down;
                }

                insertAtThisAndBottomLvl(curr, node);
            } else {
                how_many_lvls_from_top--;
                curr->distance++;
            }


            curr = curr->down;

        }

    }




    void printAllLevels(){

        Node* curr = head;
        if(head== nullptr){
            std::cout << "List is empty."<<std::endl;
            return;
        }

        Node* lvl_head = head;

        while(curr!= nullptr) {

            lvl_head = curr;

            while (curr->next != nullptr) {
                std::cout << curr->data << "(" << curr->distance << ") ";

                curr = curr->next;
            }
            std::cout << curr->data << "(" << curr->distance << ") ";
            std::cout<<std::endl;

            curr = lvl_head->down;
        }

        std::cout << std::endl;


        curr = head;
        lvl_head = head;

        while(curr!= nullptr) {

            lvl_head = curr;

            while (curr->next != nullptr) {
                std::cout<<std::left << std::setw(8) << std::setfill(' ')  << curr->data;
                for(int i = 1; i<curr->distance; i++)
                    std::cout << "        ";
                // std::cout << curr->data << "(" << curr->distance << ") ";

                curr = curr->next;
            }
            std::cout<<std::left << std::setw(8) << std::setfill(' ')  << curr->data;
            //std::cout << curr->data << "(" << curr->distance << ") ";
            std::cout<<std::endl;

            curr = lvl_head->down;
        }
    }


};