#include <iostream>

#include "LinkedList.h"
#include "Feedback.h"
#include "Node.h"
#include "UserMenu.h"

using namespace std;

void sortFeedbackByDate(Node<Feedback>*);
Node<Feedback>* mergeFeedback(Node<Feedback>*, Node<Feedback>*);
void splitFeedback(Node<Feedback>*, Node<Feedback>*, Node<Feedback>*);

// merge sort
void merge_sort(int*, int, int);
void merge(int*, int, int, int);

// quick sort
int partition(int*, int, int);
void quick_sort(int*, int, int);

// heap sort
void convert_heap(int*, int, int);
void heap_sort(int*, int);