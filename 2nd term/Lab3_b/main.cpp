#include "QuickSort.h"
#include "CountingSort.h"
#include "RadixSort.h"
#include <ctime>
#include <fstream>

size_t ITEMS_COUNT_IN_DB = 0;
static const char letters[] = "abcdefghijklmnopqrstuvwxyz";

std::string getRandomString();
Item getRandomItem();

int compareByID(Item& a, Item& b) {
    if(a.getID() < b.getID()){
        return 1;
    } else if(a.getID() == b.getID())
        return 0;
    else return -1;
}

int compareByUnits(Item& a, Item& b) {
    if(a.getUnits() < b.getUnits()){
        return 1;
    } else if(a.getUnits() == b.getUnits())
        return 0;
    else return -1;
}

int compareByExpirationPeriod(Item& a, Item& b) {
    if(a.getExpirationPeriod() < b.getExpirationPeriod()){
        return 1;
    } else if(a.getExpirationPeriod() == b.getExpirationPeriod())
        return 0;
    else return -1;
}


int multipleFieldsComparator(int (*comparators[])(Item&, Item&), int N, Item& a, Item& b){
    for(int i = 0 ; i < N; i++){
        if(comparators[i](a,b) == 1) return 1;
        else if (comparators[i](a,b) == -1) return -1;
    }
    return 0;
}

void testSortings(int N, std::ofstream& fout);

void returnToTheOriginalArray(Item* arr, int N){
    quickSort(arr, compareByID, 0, N-1);
}


int main() {

    std::ofstream fout("benchmark_result", std::ios::out);

    testSortings(500, fout);
    testSortings(5000, fout);
    testSortings(20000, fout);

    fout.close();

    return 0;
}

void testSortings(int N, std::ofstream& fout){

    // 1. Generate random array
    Item* items = new Item[N];

    for(int i = 0; i < N; i++){items[i] = getRandomItem();}

    // 2.1. Sort by units

    unsigned int delta = clock();
    fout<< std::endl << "Sorting random array of " << N << " items by units with quickSort took: ";

    quickSort(items, compareByUnits, 0, N-1);

    delta = clock() - delta;
    fout<< (double) delta / CLOCKS_PER_SEC << std::endl;

    returnToTheOriginalArray(items,N);

    //

    delta = clock();
    fout<< "Sorting random array of " << N << " items by units with countingSort took: ";

    countingSort(items, N);

    delta = clock() - delta;
    fout<< (double) delta / CLOCKS_PER_SEC << std::endl;

    returnToTheOriginalArray(items,N);

    //2.2  by expiration period

    delta = clock();
    fout<< std::endl << "Sorting random array of " << N << " items by expiration period with quickSort took: ";

    quickSort(items, compareByExpirationPeriod, 0, N-1);

    delta = clock() - delta;
    fout<< (double) delta / CLOCKS_PER_SEC << std::endl;

    returnToTheOriginalArray(items,N);

    //

    delta = clock();
    fout<< "Sorting random array of " << N << " items by expiration period with radixSort took: ";

    radixSort(items, N);

    delta = clock() - delta;
    fout<< (double) delta / CLOCKS_PER_SEC << std::endl;

    returnToTheOriginalArray(items,N);

    //3. multiple-field sort

    delta = clock();
    fout<< std::endl <<  "Sorting random array of " << N << " items by units and expirationPeriod with quickSort took: ";

    const int comparatorsNumber = 2;
    int (*comparators[comparatorsNumber]) (Item& a, Item& b) = {compareByUnits, compareByExpirationPeriod};

    quickSort(items, multipleFieldsComparator, comparators, comparatorsNumber,  0, N-1);


    delta = clock() - delta;
    fout<< (double) delta / CLOCKS_PER_SEC << std::endl << std::endl;

    returnToTheOriginalArray(items,N);

}

std::string getRandomString(){
    std::string str;
    for(unsigned int i = 0; i < 3; ++i){
        str +=  letters[rand() % (sizeof(letters)-1)];
    }

    return str;
}

Item getRandomItem(){
    srand(time(0)+ITEMS_COUNT_IN_DB);

    std::string name = getRandomString();
    float quantity = rand()%5;
    int units_index = rand()%4, expiration = rand()%500;
    Date date = Date(rand()%30, rand()%12, rand()%3+2018, rand()%24, rand()%60);

    Item item;

    item.setID();
    item.setName(name);
    item.setQuantity(quantity);
    item.setUnits(units_index);
    item.setManufactureDate(date);
    item.setExpirationPeriod(expiration);

    ITEMS_COUNT_IN_DB++;
    return item;
}