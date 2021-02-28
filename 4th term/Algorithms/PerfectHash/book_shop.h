#include <string>
#include <vector>
#include <ctime>
#include <algorithm> // for generate_n
#include <functional> //for std::hash

std::string random_string(size_t length);

static const std::string author_names[] = {
    "RobertSingh", 
    "AkkithamNamboodri", 
    "MargaretAtwood", 
    "JokhaAlharthi", 
    "RichardPower", 
    "NarendraModi", 
    "SusanNinan"
};

static const std::string book_names[] = {
    "Politics of Opportunism",
    "Malayalam poetry",
    "The Testaments",
    "Celestial Bodies",
    "The Overstory",
    "The Braille edition of the book Exam Warriors",
    "Mind - Master"
};
 

class Book {
    std::string name;
    size_t year;

public:

    Book(std::string name, std::size_t year) : name(name), year(year) {}

    std::string getName() { return name; }
    size_t getYear() { return year; }

    static Book* getBook(int index);
};


class Author {
    std::string name = " None ";
    Book* book = nullptr;

public:
    Author() = default;
    Author(std::string name) : name(name) {}
    Author(std::string name, Book* book) : name(name), book(book) {}

    std::string getName() { return name; }
    Book* getBook() { return book; }

    static std::vector<Author> getAuthors();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class HashTable {

private:

    const int p = 101; 

    struct HashSlot{
        unsigned int a = 1;
        unsigned int b = 22;
        unsigned int size = 0;

        Author* authors = new Author[sizeof(author_names) / sizeof(author_names[0])];
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