#include <random>
#include <iomanip>
#include <iostream>
const int MAX_LVL = 5;

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

    int insertAtThisAndBottomLvl(Node* prev, Node* node) {
        int distance = 0;

        while(prev->next!= nullptr && prev->next->data < node->data){
            distance+=prev->distance;
            prev=prev->next;
        }

        node->next = prev->next;
        prev->next = node;

        if(prev->down!= nullptr){
            Node* lower = new Node(node->data);
            node->down = lower;
            int old_distance = prev->distance;

            prev->distance = insertAtThisAndBottomLvl(prev->down, node->down);
            if(old_distance!=1)
                node->distance = old_distance - prev->distance + 1;
        }


        return distance + prev->distance;
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

        // insert first if the list is empty or the head has lower value
        if(head == nullptr || head->data >= data) {
            insertFirst(node); return;
        }

        Node* curr = head;
        Node* temp = head;

        //else iterate through the list
        while(curr!= nullptr) {

            //move right until the proper interval is found
            while(curr->next!= nullptr && curr->next->data < node->data){
                curr=curr->next;
            }

            if(how_many_lvls_from_top==0){
                insertAtThisAndBottomLvl(curr, node);
                return;
            } else {
                how_many_lvls_from_top--;
                curr->distance++;

                curr = curr->down;
            }
        }
    }

    int find(T value){

        Node* curr = head;
        int index = 0;

        while (curr != nullptr) {

            while (curr->next != nullptr && curr->next->data <= value) {
                index+=curr->distance;
                curr = curr->next;
            }

            if (curr->data == value) {
                // while (curr->data == value)
                //     curr = curr->next;
                return index;
            } else if (curr->down != nullptr){
                curr = curr->down;
            } else  if (curr->down == nullptr && curr->data != value){
                return -1;
            }
        }

        return -1;
    }

    void printBottomLevel() {
        if(head== nullptr){
            std::cout << "List is empty."<<std::endl;
            return;
        }

        Node* curr = head;
        while(curr->down!= nullptr)
            curr=curr->down;

        while(curr!= nullptr){
            std::cout << curr->data << " ";
            curr=curr->next;
        }
    }

    void printAllLevels(){
        if(head== nullptr){
            std::cout << "List is empty."<<std::endl;
            return;
        }

        Node* curr = head;

        Node* lvl_head = head;

        while(curr!= nullptr) {
            lvl_head = curr;

            while (curr->next != nullptr) {
                std::cout<<std::left << std::setw(8) << std::setfill(' ')  << curr->data;
                for(int i = 1; i<curr->distance; i++)
                    std::cout << "        ";

                curr = curr->next;
            }
            std::cout<<std::left << std::setw(8) << std::setfill(' ')  << curr->data;
            std::cout<<std::endl;

            curr = lvl_head->down;
        }
    }
};