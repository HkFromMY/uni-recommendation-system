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
Node<Favourite>* searchFavourite(LinkedList<Favourite>*, int);
Node<Favourite>* findMiddleFavouriteNode(Node<Favourite>*, Node<Favourite>*);

LinkedList<Favourite>* loadFavouriteData();
HashMap<string, int>* loadFavouriteOccurrences(LinkedList<Favourite>*);
int generateFavouriteId(LinkedList<Favourite>*);
void addNewFavouriteOnFile(int, Favourite*);
void deleteFavouriteOnFile(int);
string latestFavouritesInString(LinkedList<Favourite>*);
void updateLatestFavouritesOnTextFile(LinkedList<Favourite>*);

#endif // !favourite_model_h
