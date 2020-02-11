#include <iostream>
#include <cassert>
using namespace std;

void insertion_test();
void deletion_test();

template <typename T>
class List {

    //should it check T for copy_assignable?

    private:
        struct Node{
            T data;
            Node* next;
            Node* prev;

            explicit Node(const T& data){
                this->data = data;
                prev = next = nullptr;
            }
        };

        size_t length;
        Node* head;
        Node* tail;

        Node* get_Node_at_index(size_t index) const {
            assert(index < length);
            Node* result;

            if(index<length/2){
                result = head;
                int counter = 0;

                while (counter!=index){
                    result = result->next;
                    ++counter;
                }

            } else {
                result = tail;
                int counter = length-1;

                while (counter!=index){
                    result = result->prev;
                    --counter;
                }
            }
            return result;
        }


    public:
        List(){
                head = tail = nullptr;
                length = 0;
        }

        void push_back(const T& value);
        void push_front(const T& value);
        void delete_value(const T& value);
        void delete_index(size_t index);
        void add_value_at_index(const T& value, int index);
        T get_value_at_index(size_t index) const{
            return get_Node_at_index(index)->data;
        }

        size_t size() const{
            return length;
        }

        void printList(){
                Node *current = head;
                while(current!= nullptr){
                    cout << current->data << " ";
                    current = current->next;
                }cout << endl;
        }

};

int main() {
    insertion_test();
    deletion_test();

    return 0;
}

template <typename T>
void List<T>::push_back(const T& value){
    Node* node = new Node(value);
    node->prev = tail;

    if(head == nullptr){// or length == 0
        head = node;
        tail = head;
    }

    tail->next = node;
    tail = node;

    length++;
}

template <typename T>
void List<T>::push_front(const T& value){
    Node* node = new Node(value);
    ++length;

    if(head == nullptr){
        head = node;
        tail = head;
        return;
    }

    node->next = head;

    head->prev = node;
    head = node;
}

template <typename T>
void List<T>::delete_value(const T& value){
    Node *current = head;
    Node *next = current;
    size_t index = 0;

    while(current!= nullptr){

        next = current->next;

        if(value == current->data){
            --length;

            if (index == length){
                tail = current->prev;
                tail->next = nullptr;
                delete current;
                return;
            }

            if(index == 0){
                head=current->next;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            --index;
        }
        current = next;
        index++;
    }
}

template <typename T>
void List<T>::delete_index(size_t index){

    Node *current = get_Node_at_index(index);

    if (index == length-1){
        tail = current->prev;
        tail->next = nullptr;
        delete current;
        --length;
        return;
    }

    --length;

    if(index == 0){
        head=current->next;
        delete current;
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;
}

template <typename T>
void List<T>::add_value_at_index(const T& value, int index){
    assert(index <= length);
    if(index == length) {
        push_back(value);
        return;
    }
    if(index == 0){
        push_front(value);
        return;
    }

    Node *new_node = new Node(value);

    Node *current = get_Node_at_index(index);

    new_node->prev = current->prev;
    current->prev = new_node;
    new_node->next = current;
    new_node->prev->next = new_node;

    length++;
}

void insertion_test(){
    List<int> *list = new List<int>();
    cout << "1. \n \tShould return: 120 333 10 12 555 5 14 12 \n \t\t  Returns: ";

    list->push_back(10);
    list->push_back(12);
    list->add_value_at_index(555,2);
    list->push_back(14);
    list->push_back(12);
    list->add_value_at_index(5,3);
    list->push_front(333);
    list->add_value_at_index(120,0);

    list->printList();
}

void deletion_test(){
    List<char> *list = new List<char>;
    for(int i = 0; i < 5; i++){
        list->push_front(rand() % 15 + 70);
    }

    list->push_back('H');
    list->push_back('H');

    cout << "2. \n \tIn: "; list->printList();
    cout << "\n\tValue at 1:" << list->get_value_at_index(1)<<
         "\n\tValue at 0:" << list->get_value_at_index(0)<<
         "\n\tValue at "<<list->size()-1<<"(size-1): "<<list->get_value_at_index(list->size()-1)<<endl;


    int index = rand() % 3+1;
    cout << "\n\tDeleting value at "<<index<<"\n\tResult: ";
    list->delete_index(index);
    list->printList();

    cout << "\n\tDeleting value at 0"<<"\n\tResult: ";
    list->delete_index(0);
    list->printList();

    cout << "\n\tDeleting value at "<<list->size()-1<<"(size-1)\n\tResult: ";
    list->delete_index(list->size()-1);
    list->printList();

    cout << "\n\tDeleting value 'A' \n\tResult: ";
    list->delete_value('A');
    list->printList();

    cout << "\n\tDeleting value 'H' \n\tResult: ";
    list->delete_value('H');
    list->printList();

}
