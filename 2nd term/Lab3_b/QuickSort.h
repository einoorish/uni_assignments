#include "Item.h"


//1 field sort
void quickSort(Item* arr, int (*comparator)(Item&, Item&),  int start, int end);


//multiple field sort
void quickSort(Item* arr,
               int (*superComparator)(int (*comparators[])(Item&, Item&), int N, Item&, Item&),
               int (*comparators[])(Item&, Item&), int N,  int start, int end);
