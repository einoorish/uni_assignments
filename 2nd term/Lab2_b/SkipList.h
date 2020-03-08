#include <random>
const int MAX_LVL = 5;

template <typename T>
class SkipList{

    public: struct Node;
            Node* head = nullptr;

    private: void insertFirst(Node* node){
            head = node;

            //set max lvl
            for(int i = 0; i < MAX_LVL-1; i++){
                node->down = new Node(node->data);
                node = node->down;
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
                //the width of a higher level link is the sum of the component links below it
                //int width = 0;

                Node()= default;
                explicit Node(T data) : data(data){}
              //  Node(T data, Node* down) : data(data),  down(down){}

                /*Node* getDown(){
                    Node* temp = this;
                    if(down == nullptr) return temp;

                    temp = down;
                    while(temp->next == nullptr)
                        if (temp->down != nullptr) temp = down;
                        else return temp;
                }*/

            };

            Node* find(T value){
                //TODO: return by index

                Node* curr = head;

                while (curr != nullptr) {

                    while (curr->next != nullptr && curr->next->data < value) {
                        curr = curr->next;
                    }

                    if (curr->data == value) {
                        while (curr->data == value)
                            curr = curr->next;
                        return curr;
                    }

                    if(curr->down != nullptr){
                        curr = curr->down;
                    } else return curr;
                }

                return curr;
            }

            void insert(T value){

                Node* node = new Node(value);
                int how_many_lvls_from_top = getRandomLvl();

                if(head == nullptr) { insertFirst(node); return;}

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
                        /*
                        while(curr->down != nullptr) {
                            //there will be another node at a lvl lower
                            Node* lower_node = new Node(value);
                            node->down = lower_node;

                            while(curr->down->next!= nullptr && curr->down->next->data < lower_node->data)
                                curr->down = curr->down->next;
                            lower_node->next = curr->down->next;
                            curr->down->next= lower_node;
                            curr=curr->down;
                            node = lower_node;
                        }*/
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
                        std::cout << curr->data << " ";
                        curr = curr->next;
                    }
                    std::cout << curr->data;
                    std::cout<< std::endl;

                    curr = lvl_head->down;
                }
            }
};