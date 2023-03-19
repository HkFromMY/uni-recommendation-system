#include <iostream>

using namespace std;

// merge sort
void merge_sort(int*, int, int);
void merge(int*, int, int, int);

// quick sort
int partition(int*, int, int);
void quick_sort(int*, int, int);

// heap sort
void convert_heap(int*, int, int);
void heap_sort(int*, int);