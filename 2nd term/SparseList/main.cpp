
#include <iostream>

class List{

    struct Node {
        Node *next;
        int data;
        int index;
        Node(int data, int index){
            this->data = data;
            this->index = index;
            next = nullptr;
        }
    };

    Node *head, *tail;
    std::size_t length;
    public:

    List() {
            head = tail = nullptr;
            length = 0;
          }

            void push_back(int value) {
                if (value != 0){
                    Node *node = new Node(value, length);
                    if (head == nullptr) {
                        head = node;
                        tail = head;
                    }
                    tail->next = node;
                    tail = node;
                }
                length++;
            }

            void insert(int value,int index) {
                //if list doesn't contain any non-zero value yet
                if (head == nullptr && length != index) {
                    std::cout << "Wrong index" << std::endl;
                    return;
                } else if (head == nullptr) {
                    push_back(value);
                    return;
                }

                Node *current = head;
                //insert before head if new index is smaller
                if (index <= current->index) {
                    if (value != 0) {
                        Node *node = new Node(value, index);
                        head = node;
                        node->next = current;
                    }
                    length++;
                    while (current != nullptr) {
                        current->index++;
                        current = current->next;
                    }
                }
                //insert after tail if new index is bigger
                else if (tail->index < index) {
                    push_back(value);
                }
                //insert somewhere in the middle
                else {
                    //find proper position
                    while (current->next != nullptr && current->next->index < index)
                        current = current->next;

                    //new node doesn't get created if value == 0
                    if (value != 0) {
                        Node *node = new Node(value, index);
                        node->next = current->next;
                        current->next = node;
                    }
                    length++;
                    current = current->next->next;

                    //next nodes' index will be increased by 1
                    while (current != nullptr) {
                        current->index += 1;
                        current = current->next;
                    }
                }
            }

            int at(int index){
                if(index>length || index <0) return -1;

                Node* cur = head;
                while(cur->next!= nullptr && cur->next->index<=index)
                    cur=cur->next;

                if(cur->index == index) return cur->data; // found non-zero value
                else if(cur->next == nullptr && index !=  length-1) return -1; // not found any value
                else return 0;
            }

            void printList() {
                Node *current = head;
                while (current != nullptr) {
                    std::cout << "Data:" << current->data << ",";
                    std::cout << " Index:" << current->index << std::endl;
                    current = current->next;
                }
            }
};


int main(){
    List list = List();

    list.insert(1,0);

    for (int i = 0; i < 10; ++i) {
        if(i%2!=0 || i%3==0 || i%5==0){
            std::cout<<"0"<<" ";
            list.push_back(0);
        }else{
            list.push_back(i);
            std::cout<<i<<" ";
        }
    }
    std::cout << std::endl;
    list.printList();
    std::cout << std::endl;

    list.insert(3,3);
    list.printList();


    std::cout << std::endl;
    std::cout << list.at(5) << std::endl;//returns 2
    std::cout << list.at(4) << std::endl;//returns 0
    std::cout << list.at(11) << std::endl;//returns 0
    std::cout << list.at(-9) << std::endl;//returns -1

    return 0;
}
