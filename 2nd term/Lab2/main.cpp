#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <chrono>

void demoMode();
void interactiveMode();
void benchmark();

struct IPv4 {
    uint8_t octet1 = 0;
    uint8_t octet2 = 0;
    uint8_t octet3 = 0;
    uint8_t octet4 = 0;

    IPv4()= default;;
    IPv4(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4){
        this->octet1 = octet1;
        this->octet2 = octet2;
        this->octet3 = octet3;
        this->octet4 = octet4;
    };

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
        std::cout << unsigned(ip.octet1) << '.'  << unsigned(ip.octet2) << '.'
                  << unsigned(ip.octet3) << '.' << unsigned(ip.octet4);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        int octet;

        std::cin >> octet;
        ip.octet1 = unsigned(octet);

        std::cin >> octet;
        ip.octet2 = unsigned(octet);

        std::cin >> octet;
        ip.octet3 = unsigned(octet);

        std::cin >> octet;
        ip.octet4 = unsigned(octet);

        return is;
    }

};

template <typename T>
class Stack {
    public:
        virtual Stack* createEmpty() = 0;
        virtual bool isEmpty() const = 0;
        virtual T peek() const noexcept(false) = 0;
        virtual void push(T data)  = 0;
        virtual T pop() noexcept(false) = 0;
};

template <typename T>
class LinkedListStack : public Stack<T> {

    private:
            struct Node{
                T data;
                Node* next;

                explicit Node(const T& data){
                    this->data = data;
                }
            };
            Node* top = nullptr;

    public:
            LinkedListStack*  createEmpty() override {top = nullptr; return this;}
            bool isEmpty() const override{return top == nullptr;}
            T peek() const noexcept(false) override {if(!isEmpty()) return top->data; else throw std::invalid_argument("Stack is empty");}

            void push(T data) override{
                    Node* node = new Node(data);
                    node->next = top;
                    top = node;
            }

            T pop() override{
                if(!isEmpty()){
                    T data = top->data;
                    top = top->next; // не потрібно видаляти, так як немає new?
                    return data;
                } else throw std::invalid_argument("Stack is empty");
            }

            friend std::ostream& operator<<(std::ostream& os, const LinkedListStack& stack) {
                Node* current = stack.top;
                while(current != nullptr){
                    std::cout << current->data << "  ";
                    current=current->next;
                }
                return os;
            }
};

template <typename T>
class StaticArrayStack : public Stack<T>{

    public:
            explicit StaticArrayStack(size_t array_size) : capacity(array_size) {
                size = 0;
                array = new T[capacity];
            }

            StaticArrayStack* createEmpty() override {delete[] array; size = 0; return new StaticArrayStack(capacity);}

            bool isEmpty() const override{return size==0;}

            T peek() const noexcept(false) override {if(!isEmpty()) return array[size-1]; else throw std::invalid_argument("Stack is empty");}

            void push(T data) noexcept(false) override{
                if(size+1<capacity){
                    array[size++] = data;
                } else  throw std::invalid_argument("Stack is full");
            }

            T pop() noexcept(false) override{
                if(!isEmpty())
                    return array[--size];
                else throw std::invalid_argument("Stack is empty");
            }

            friend std::ostream& operator<<(std::ostream& os, const StaticArrayStack& stack) {
                for(int i = 0; i < stack.size; i++)
                    std::cout << stack.array[i] << "  ";

                return os;
            }

    private:
            T *array;
            size_t size;
            const size_t capacity;

};

template <typename T>
class DynamicArrayStack : public Stack<T> {

    private: std::vector<T> stack;

    public:
            DynamicArrayStack* createEmpty() override {stack.clear(); return this;}
            bool isEmpty() const override {return stack.empty();}

            T peek() const noexcept(false) override {
                if (!isEmpty()) {
                    return stack.back();
                } else throw std::invalid_argument("Stack is empty");
            }

            T pop() override {
                if (!isEmpty()) {
                    T temp = stack.back();
                    stack.pop_back();
                    return temp;
                } else throw std::invalid_argument("Stack is empty");
            }
            void push(T data) override {stack.push_back(data);}
};


int main() {
    int operation = 3;

    std::cout << "Choose mode: 1 - Interactive, 2 - Demo, 3 - Benchmark"<<std::endl;
    std::cin >> operation;

    switch (operation) {
        case 1: {
            interactiveMode();
            break;
        }
        case 2: {
            demoMode();
            break;
        }
        case 3: {
            benchmark();
            break;
        }
        default:
            break;
    }
    return 0;
}

void interactiveMode(){
    int command = 0;
    std::cout << "Choose stack implementation(1 - linked list based, 2 - static array, 3 - dynamic array): ";
    std::cin >> command;

    Stack<IPv4>* stack;

    switch (command) {
        case 1: {
            stack = new LinkedListStack<IPv4>();
            break;
        }
        case 2: {
            size_t size;
            std::cout << "enter stack size: ";
            std::cin >> size;
            stack = new StaticArrayStack<IPv4>(size);
            break;
        }
        case 3: {
            stack = new DynamicArrayStack<IPv4>();
            break;
        }
        default:
            break;
    }

    std::cout << "Available operations are 1 - create empty, 2 - check if empty, 3 - peek, 4 - pop, 5 - push, 0 - exit"<<std::endl;
    std::cin >> command;
    while(command != 0){

        switch (command) {
            case 1: {
                stack->createEmpty();
                break;
            }
            case 2: {
                std::cout << stack->isEmpty() << std::endl;
                break;
            }
            case 3: {
                try{
                    std::cout << stack->peek() << std::endl;
                } catch (std::invalid_argument& e) {std::cout << e.what() << std::endl;}
                break;
            }
            case 4: {
                try{
                    std::cout << stack->pop() << std::endl;
                } catch (std::invalid_argument& e) {std::cout << e.what() <<std::endl;}
                break;
            }
            case 5: {
                IPv4 ip;
                std::cout << "Enter IP adress (example input: 192 168 2 33): ";
                std::cin >> ip;
                try{
                    stack->push(ip);
                } catch (std::invalid_argument& e) {std::cout << e.what() << std::endl;}
                break;
            }
            default:
                break;
        }

        std::cout << "Available operations are 1 - create empty, 2 - check if empty, 3 - peek, 4 - pop, 5 - push, 0 - exit" << std::endl;
        std::cin >> command;
    }
}

void demoMode(){

    std::cout << "Demo for Stack made with Linked List-------------------------" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Creating empty linked List (call:  stack.createEmpty())" << std::endl;

    LinkedListStack<IPv4> stack;
    stack.createEmpty();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Checking if stack is empty (call:  stack.isEmpty())" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " << stack.isEmpty() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Adding 5 items of type IPv4 to stack (call: stack.push(...))" << std::endl;
    for(int i = 0; i < 5; i++){
        stack.push(IPv4(std::rand()%256,std::rand()%256,std::rand()%256,std::rand()%256));
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Items added: " << stack << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Checking if stack is empty (call:  stack.isEmpty())" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " << stack.isEmpty() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Fetching the top element (call:  stack.peek())" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " << stack.peek() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Fetching the top element and deleting it (call:  stack.pop())" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " << stack.pop() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Fetching the top element again (call:  stack.peek())" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " <<  stack.peek() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "----------------------------------------\nSimilarly for other implementations of Stack " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "End of Demo mode. " << std::endl;
}

#include <fstream>

void benchmark_helper(std::ofstream& results, Stack<int>*& stack, long& N){
    unsigned int delta = 0;
    for(int i = 0; i < N; i++){
        stack->push(1);
    }
    delta = clock() - delta;

    results << "Pushing "<<N<<" elements took " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;

    delta = 0;
    stack->peek();
    delta = clock() - delta;
    results << "Peeking the "<<N<<"th element took " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;

    delta = 0;
    for(int i = 0; i < N; i++){
        stack->pop();
    }
    delta = clock() - delta;
    results << "Popping "<<N<<" elements took " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;
}

void benchmark(){
    std::ofstream results("benchmark_results.txt", std::ios::trunc);
    long N = 50000000;

    results << "LINKED LIST STACK--------"<<std::endl;
    Stack<int>* stack = new LinkedListStack<int>();
    benchmark_helper(results, stack, N);

    results << "STATIC ARRAY STACK--------"<<std::endl;
    stack = new StaticArrayStack<int>(N+1);
    benchmark_helper(results, stack, N);

    results << "DYNAMIC ARRAY STACK--------"<<std::endl;
    stack = new DynamicArrayStack<int>();
    benchmark_helper(results, stack, N);

    results.close();

    std::cout << "Benchmark finished. See results in \"benchmark_results.txt\""<< std::endl;
}