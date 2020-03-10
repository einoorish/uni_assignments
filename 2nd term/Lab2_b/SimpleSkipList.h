#include <random>
const int MAX_LVL = 5;

template <typename T>
class SimpleSkipList{

public: struct Node;
    Node* head = nullptr;

private: void insertFirst(Node* node){
        if(head!= nullptr){
            Node* old_head = head;
            node->next = old_head;
            head = node;

            old_head = old_head->down;

            while(old_head!= nullptr){
                Node* lower_node = new Node(node->data);
                node->down = lower_node;
                lower_node->next = old_head;
                old_head=old_head->down;
                node = lower_node;
            }

        }
        else {
            head = node;

            for(int i = 0; i<MAX_LVL-1; i++){
                node->down = new Node(node->data);
                node = node->down;
            }
        }
    }
    int getRandomLvl(){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, MAX_LVL-1); // define the range

        return distr(eng);
    }
    void insertAtBottomLvls(Node* node, Node* prev){
        while(prev != nullptr) {
            //there will be another node at a lvl lower
            Node* lower_node = new Node(node->data);
            node->down = lower_node;

            while(prev->next!=nullptr && prev->next->data < lower_node->data){
                //there might be lesser values...
                prev=prev->next;
            }

            lower_node->next = prev->next;
            prev->next = lower_node;

            prev = prev->down;
            node=lower_node;
        }
    }

public: struct Node{
        T data;
        Node *next = nullptr;
        Node *down = nullptr;

        Node()= default;
        explicit Node(T data) : data(data){}

        Node* getDown(){
            Node* temp = this;
            while(temp->down != nullptr)
                temp = temp->down;
            return temp;
        }

    };

    bool find(T value){

        Node* curr = head;

        while (curr != nullptr) {

            while (curr->next != nullptr && curr->next->data <= value) {
                curr = curr->next;
            }

            if (curr->data == value) {
               // while (curr->data == value)
               //     curr = curr->next;
                return true;
            } else if (curr->down != nullptr){
                curr = curr->down;
            } else  if (curr->down == nullptr && curr->data != value){
                return false;
            }
        }

        return false;
    }

    void insert(T value){

        Node* node = new Node(value);
        int how_many_lvls_from_top = getRandomLvl();

        if(head == nullptr || value < head->data) { insertFirst(node); return;}

        Node* curr = head;

        while(curr!= nullptr){

            //move right until the proper interval is found
            while(curr->next!= nullptr && curr->next->data < node->data){
                curr=curr->next;
            }

            if(how_many_lvls_from_top==0){
                node->next = curr->next;
                curr->next = node;

                curr=curr->down;
                insertAtBottomLvls(node, curr);
                return;
            } else how_many_lvls_from_top--;

            curr = curr->down;
        }
        /*

        if(head == nullptr) {
            head = node;

            //set max lvl
            for(int i = 0; i < MAX_LVL-1; i++){
                node->down = new Node(node->data);
                node = node->down;
            }
            return;
        }


        Node* current = find(value);
        //node = node->getDown();

        int random_lvl = getRandomLvl();
        for(int i = 0; i < MAX_LVL-random_lvl; i++){
            this->down = new Node(this->data);
        }

        while(current!= nullptr){
            if(current->next!= nullptr){
                node->next = current->next;
                current->next = node;
            } else {
                current->next = node;
            }
            current=current->down;
        }
        */
    }

    void printBottomLevel(){

        Node* curr = head;
        if(head== nullptr){
            std::cout << "List is empty."<<std::endl;
            return;
        }

        Node* bottom_head = head->getDown();

        while(bottom_head!= nullptr) {
            std::cout<<bottom_head->data<<" ";
            bottom_head=bottom_head->next;
        }
    }
};