#pragma once
#ifndef favourite_model_h
#define favourite_model_h

#include <iostream>
#include <string>
#include "util.h"

#include "LinkedList.h"
#include "Node.h"
#include "Favourite.h"
#include "Counter.h"

#include "HashMap.h"

using namespace std;

// sort and filter
Node<Counter>* sortFavouritesByOccurrences(Node<Counter>*);
Node<Counter>* splitFavourites(Node<Counter>*);
Node<Counter>* mergeFavourites(Node<Counter>*, Node<Counter>*);

LinkedList<Favourite>* filterFavouriteByUser(LinkedList<Favourite>*, int);

LinkedList<Favourite>* loadFavouriteData();
HashMap<string, int>* loadFavouriteOccurrences();

#endif // !favourite_model_h
