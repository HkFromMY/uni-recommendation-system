#pragma once
#ifndef hashmap_h
#define hashmap_h

#include <iostream>
#include <string>

#include "LinkedList.h"
#include "Counter.h"

/*
* This HashMap data structure is built specifically to ease the process of recording the occurrences of university in user's favourites list
* Hence, although template declaration is used, but this data structure only accepts string-int mappings.
*/

using namespace std;

template <class KEY, class VALUE>
class HashNode {
	public: 
		KEY key;
		VALUE value;

		HashNode(KEY, VALUE);
};

template <class KEY, class VALUE>
HashNode<KEY, VALUE>::HashNode(KEY key, VALUE value) {
	this->key = key;
	this->value = value;
}

template <class KEY, class VALUE>
class HashMap {
	private: 
		HashNode<KEY, VALUE>** hash_arr;
		int capacity;
		int size;
		HashNode<KEY, VALUE>* dummy;

	public:
		HashMap(int);
		~HashMap();

		unsigned long int hashCode(string);
		void insertNode(KEY, VALUE);
		VALUE get(string);
		void incrementCount(string);
		int getSize();
		void displayAllHashNodes();
		LinkedList<Counter>* to_counters();
};

template <class KEY, class VALUE>
HashMap<KEY, VALUE>::HashMap(int capacity) {
	// initialization of a hash array
	this->capacity = capacity;
	this->size = 0;
	this->hash_arr = new HashNode<KEY, VALUE>* [capacity];

	for (int i = 0; i < capacity; i++) {
		this->hash_arr[i] = NULL;
	}
}

template <class KEY, class VALUE>
HashMap<KEY, VALUE>::~HashMap() {}

template <class KEY, class VALUE>
unsigned long HashMap<KEY, VALUE>::hashCode(string key) {
	// this function hash the key in string format, then returning a hash to search for element in hash array
			// algorithm source: https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f

			// only accepts string as key values
	unsigned long hash = 5381L;
	int c;
	for (int i = 0; i < key.length(); i++) {
		c = key[i];
		hash = ((hash << 5) + hash) + c; // shift the hash's values by bits then plus c
	}

	return hash % capacity;
}

template <class KEY, class VALUE>
void HashMap<KEY, VALUE>::insertNode(KEY key, VALUE value) {
	HashNode<KEY, VALUE>* temp = new HashNode<KEY, VALUE>(key, value);

	int hashIndex = hashCode(key);

	while (
		hash_arr[hashIndex] != NULL &&
		hash_arr[hashIndex]->key != key
		) {
		// simple mechanism by incermenting hash by 1 to insert duplicated hash (prevent hash collision problem)
		hashIndex++;
		hashIndex %= capacity;
	}

	if (
		hash_arr[hashIndex] == NULL
		) {
		size++;
	}
	hash_arr[hashIndex] = temp;
}

template <class KEY, class VALUE>
VALUE HashMap<KEY, VALUE>::get(string key) {
	int hashIndex = hashCode(key);
	int counter = 0;

	while (hash_arr[hashIndex] != NULL) {
		if (counter++ > capacity) return NULL;

		if (hash_arr[hashIndex]->key == key) return hash_arr[hashIndex]->value;

		// simple mechanism to trace back if the target is a duplicated hash (prevent hash collision problem)
		hashIndex++;
		hashIndex %= capacity;
	}

	return NULL;
}

template <class KEY, class VALUE>
void HashMap<KEY, VALUE>::incrementCount(string key) {
	/*
			This is a specialized function to keep track of the occurrences of a value such as University
			If the key does not exist in this hash table, then a new key with value of 1 is added to the hash table.
			*/
	int hashIndex = hashCode(key);
	int counter = 0;

	while (hash_arr[hashIndex] != NULL) {
		if (counter++ > capacity) return;

		if (hash_arr[hashIndex]->key == key) {
			hash_arr[hashIndex]->value += 1;
			return;
		}

		// simple mechanism to trace back if the target is a duplicated hash
		hashIndex++;
		hashIndex %= capacity;
	}

	// if the key does not exists, then add a new key and use 1 as initial value
	insertNode(key, 1);
}

template <class KEY, class VALUE>
int HashMap<KEY, VALUE>::getSize() {
	return size;
}

template <typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::displayAllHashNodes() {
	for (int i = 0; i < capacity; i++) {
		if (hash_arr[i] != NULL) {
			cout << "key = " << hash_arr[i]->key << "  value = " << hash_arr[i]->value << endl;
		}
	}
}

template <typename KEY, typename VALUE>
LinkedList<Counter>* HashMap<KEY, VALUE>::to_counters() {
	// this functions is to convert all the key-value pairs in this hash table to a list of Counter object
	// so that the occurrences can be sorted
	// time complexity - O(N)
	LinkedList<Counter>* counters = new LinkedList<Counter>();

	for (int i = 0; i < capacity; i++) {
		if (hash_arr[i] != NULL) {
			counters->appendNewNode(new Counter(
				hash_arr[i]->key,
				hash_arr[i]->value
			));
		}
	}

	return counters;
}

#endif // !hashmap_h
