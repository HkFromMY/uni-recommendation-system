#include "sort.h"

void sortFeedbackByDate(Node<Feedback>*) {

}



void merge_sort(int* arr, int left, int right) {
	// source geeksforgeeks - Merge Sort
	if (left >= right) {
		return;
	}
	
	int middle = left + (right - left) / 2;

	merge_sort(arr, left, middle);
	merge_sort(arr, middle + 1, right);
	merge(arr, left, middle, right);
}

void merge(int* arr, int left, int middle, int right) {
	// helper function for merge_sort

	int left_array_index = middle - left + 1;
	int right_array_index = right - middle;

	// create temporary sub-array
	int* left_subarray = new int[left_array_index];
	int* right_subarray = new int[right_array_index];

	// copy data to the array created
	for (int i = 0; i < left_array_index; i++) {
		left_subarray[i] = arr[left + i];
	}

	for (int j = 0; j < right_array_index; j++) {
		right_subarray[j] = arr[middle + j + 1];
	}

	// i is the left array ptr, while j is the right array ptr, k is the current index of merged array
	int i = 0, j = 0, k = left;

	while (i < left_array_index && j < right_array_index) {
		if (left_subarray[i] <= right_subarray[j]) {
			arr[k] = left_subarray[i];
			i++;
		}
		else {
			arr[k] = right_subarray[j];
			j++;
		}
		k++;
	}

	// copy the remaining elements to the merged array
	while (i < left_array_index) {
		arr[k] = left_subarray[i];
		i++;
		k++;
	}

	while (j < right_array_index) {
		arr[k] = right_subarray[j];
		j++;
		k++;
	}

	delete[] left_subarray;
	delete[] right_subarray;
}

void quick_sort(int* arr, int left, int right) {
	if (left < right) {
		int partition_index = partition(arr, left, right);

		quick_sort(arr, left, partition_index - 1);
		quick_sort(arr, partition_index + 1, right);
	}
}

int partition(int* arr, int left, int right) {
	int pivot = arr[right];
	int i = left - 1;

	for (int j = left; j <= right - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[right]);
	return i + 1;
}

void heap_sort(int* arr, int size) {
	// convert array to heap
	for (int i = size / 2 - 1; i >= 0; i--) {
		convert_heap(arr, size, i);
	}

	for (int i = size - 1; i > 0; i--) {
		swap(arr[0], arr[i]);

		convert_heap(arr, i, 0);
	}
}

void convert_heap(int* arr, int size, int index) {
	int root_node = index;
	int left_node = 2 * index + 1;
	int right_node = 2 * index + 2;

	if (left_node < size && arr[left_node] > arr[root_node]) {
		root_node = left_node;
	}

	if (right_node < size && arr[right_node] > arr[root_node]) {
		root_node = right_node;
	}

	if (root_node != index) {
		// swap the values between nodes if left or right node happens to be larger than root node
		swap(arr[index], arr[root_node]);

		// convert to max-heap for remaining sub-trees recursively
		convert_heap(arr, size, root_node);
	}

}


