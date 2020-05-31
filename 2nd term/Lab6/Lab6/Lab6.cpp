#include <iostream>
#include <thread>
#include <chrono>
#include "OrderedLinkedList.h"
#include "OrderedArrayList.h"

using namespace std;

void testLinkedList() {
	cout << "Created empty OrderedLinkedList" << endl;
	OrderedLinkedList ll = OrderedLinkedList::create_empty();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << "\nAdded 5 unordered objects:" << endl;
	ll.add({ 4, 2, 20 });
	ll.add({ 23, 1, 0 });
	ll.add({ 18, 1, -20 });
	ll.add({ 21, 10, 1, });
	ll.add({ 20, 21, 1 });
	ll.print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "\n\nRemoved object at index 2: " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	ll.remove(2);
	ll.print();


	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "\n\nSearch between (0, 0, 10) and (10,0,0): " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::vector<Ñoordinates*> res = ll.find({ 0, 0, 10 }, { 10,0,0 });
	for (auto it : res) {
		cout << *it << " ";
	}
}

void testArrayList() {
	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "Created empty OrderedArrayList" << endl;
	OrderedArrayList<10> al = OrderedArrayList<10>::create_empty();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	cout << "\nAdded 4 unordered objects:" << endl;
	al.add({ 1, 2, 4 });
	al.add({ 2, 2, 2 });
	al.add({ 2, 2, 2 });
	al.add({ 20, 1, 0 });
	al.print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "\nRemoved object at index 1: " << endl;
	al.remove(1);
	al.print();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "\nSearch between (0, 0, 10) and (10,0,0): " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::vector<Ñoordinates*> res = al.find({ 0, 0, 10 }, { 10,0,0 });
	for (auto it : res) {
		cout << *it << " ";
	}
}

int main() {
 
	testLinkedList();
	std::cout << std::endl << "\n-------------------------\n" << std::endl;
	testArrayList();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << std::endl;
}
