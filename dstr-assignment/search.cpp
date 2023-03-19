#include "search.h"

int linear_search(int* arr, int size, int target) {
	for (int index = 0; index < size; index++) {
		if (arr[index] == target)
			return index;
	}

	return -1;
}

int binary_search(int* arr, int size, int target) {
	// source: https://www.geeksforgeeks.org/binary-search/

	int low = 0;
	int high = size - 1;
	int mid;

	while (low <= high) {
		mid = low + (high - 1) / 2;

		if (target == arr[mid]) {
			return mid;
		}
		else if (target > arr[mid]) { // x is on the right side
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	return -1;
}

int jump_search(int* arr, int size, int target) {
	int i = 0;
	int block = sqrt(size);

	while (arr[block] <= target && block < size) {
		i = block; // shift the block
		block += sqrt(size);
		if (block > size - 1) // if block size exceeds the array
			return -1;

	}

	for (int j = i; j < block; j++) {
		// perform linear search on the block
		if (arr[j] == target)
			return j;
	}

	return -1;
}
