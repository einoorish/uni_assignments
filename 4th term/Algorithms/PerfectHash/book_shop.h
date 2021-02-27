#include <string>
#include <vector>
#include <ctime>
#include <algorithm> // for generate_n
#include <functional> //for std::hash

std::string random_string(size_t length);

class Book {
    std::string name;
    size_t year;

public:

    Book(std::string name, std::size_t year) : name(name), year(year) {}

    std::string getName() { return name; }
    size_t getYear() { return year; }

    static std::vector<Book> generateBooks(size_t m);
};


class Author {
    std::string name = " None ";
    std::vector<Book> books;

public:
    Author() = default;
    Author(std::string name) : name(name) {}
    Author(std::string name, std::vector<Book> books) : name(name), books(books) {}

    std::string getName() { return name; }
    std::vector<Book> getBooks() { return books; }

    static std::vector<Author> generateAuthors(size_t m);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class HashTable {

private:

    const int p = 101; 

    struct HashSlot{
        unsigned int a = 1;
        unsigned int b = 22;
        unsigned int size = 0;

        Author* authors;
    };

    int universalHash(const std::string& key, int a, int b, int m);


public:

    HashSlot* hashTable;

    HashTable(int m){
        hashTable = new HashSlot[m];
    }

    HashSlot get(int i) {
        return hashTable[i];
    }

	void makePerfectHashTable(std::vector<Author>& performers);
    void search(std::string key, int m);
};