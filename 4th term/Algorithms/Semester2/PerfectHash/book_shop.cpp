#include "book_shop.h"
#include <iostream>
#include <random>

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

int strHash(const std::string& str) {
    int result = 0;
    int m = 1, k = 31, mod = 137;
    for (int i = 0; i < str.size(); i++) {
        result += ((int)str[i] * m) % mod;
        m = (m * k) % mod;
    }
    return result;
}

int HashTable::universalHash(const std::string& key, int a, int b, int m) {
	/*  
        n ключів хешуються в m комірок за допомогою універсальної хеш-функції h
	    h(k)=((a⋅k+b)modp)modm
    */

	int stringHash = strHash(key);
	return ((abs(a * stringHash + b)) % p) % m;
}

void HashTable::makePerfectHashTable(std::vector<Author>& authors) {
    /*
        для кожної комірки своя вторинна хеш-таблиця зі своєю універсальною хеш-функцією,
        вибраною так, щоб уникнути колізій; її розмір – квадрат кількості ключів,
        захешованих в комірку.
    */

    std::vector<std::vector<Author>> universal_hashes;
    universal_hashes.resize(authors.size());

    //Первинна (універсальна) таблиця
    for (int i = 0; i < authors.size(); i++) {
        int hash = universalHash(authors[i].getName(), 1, 22, authors.size());
        universal_hashes[hash].push_back(authors[i]);
    }

    for (int i = 0; i < authors.size(); i++) {

        int m = universal_hashes[i].size();
        hashTable[i].size = m*m;
        hashTable[i].authors = new Author[m*m];

        if (m == 1) {
            hashTable[i].authors[0] = universal_hashes[i][0];
            hashTable[i].a = 1;
            hashTable[i].b = 22;
            continue;
        }

        bool* occupied = new bool[m * m];

        bool flag = false;
        while (!flag) {
            for (int j = 0; j < m * m; j++)
                occupied[j] = false;

            hashTable[i].a = rand_int(0, p);
            hashTable[i].b = rand_int(1, p);

            flag = true;
            for (int j = 0; j < m; j++) {

                int hash = universalHash(universal_hashes[i][j].getName(), hashTable[i].a, hashTable[i].b, authors.size());
                if (occupied[hash]) {
                    flag = false;
                    //Колізія
                    hashTable[i].a = rand_int(0, p);
                    hashTable[i].b = rand_int(1, p);
                    continue;
                }
                occupied[hash] = true;
                for (int j = 0; j < m*m; j++)
                    hashTable[i].authors[j] = Author();

                for (int j = 0; j < m; j++) {
                    int hash = universalHash(universal_hashes[i][j].getName(), hashTable[i].a, hashTable[i].b, hashTable[i].size);
                    hashTable[i].authors[hash] = universal_hashes[i][j];
                }
            }

        }
    
    }

}

void HashTable::search(std::string key, int m){
    
    int hash = universalHash(key, 1, 22, m);
    int hash2 = universalHash(key, hashTable[hash].a, hashTable[hash].b, hashTable[hash].size);
    
    
    Book* book = hashTable[hash].authors[hash2].getBook();
    std::cout << book->getYear() << " - " << book->getName() << std::endl;
}

std::vector<Author> Author::getAuthors() {
    srand((unsigned)time(0));
    std::vector<Author> authors;
    for (int i = 0; i < sizeof(author_names) / sizeof(author_names[0]); i++) {
        authors.push_back(Author(author_names[i], Book::getBook(i)));
    }
    return authors;
}

Book* Book::getBook(int index) {
    Book* book = new Book(book_names[index], (rand() % 2020));
    return book;
}

std::string random_string(size_t length){
    auto randchar = []() -> char {
        const char charset[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}