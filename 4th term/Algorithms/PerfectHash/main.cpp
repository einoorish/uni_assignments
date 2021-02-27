#include <iostream>
#include "book_shop.h"
#include <random>


int main()
{
    int m = 3;
    std::cout << "How many authors? ";
    std::cin >> m;

    std::vector<Author> authors = Author::generateAuthors(m);
    std::cout << "\nSuccessfully generated " << m << " authors:\n";
    for (int i = 0; i < m; i++) {
        std::cout << authors[i].getName() << " ";
    }

    HashTable hashTable = HashTable(m);

    std::cout << "\n\nAfter hashing --------------\n";
    hashTable.makePerfectHashTable(authors);
    std::cout << "HashTable:\n";

    for (int i = 0; i < authors.size(); i++) {
        std::cout << i << ": ";
        if (hashTable.get(i).authors == nullptr)
            std::cout << "Empty hash\n";
        else {
            for (int j = 0; j < hashTable.get(i).size; j++)
                std::cout << " " << hashTable.get(i).authors[j].getName() << " "; 
            std::cout << '\n';
        }
    }

  
    std::cout << "\nEnter author name: ";
    std::string key;
    std::cin >> key;
    hashTable.search(key, m);

    system("pause");
}
