#include "search.h"
#include "LinkedList.h"
#include "User.h"

Node<User>* searchUser(Node<User>* headNode, int userId) {
	// O(log n) - binary search

	if (headNode == NULL) {
		return NULL;

	}
	else if (headNode->getData()->getUserId() == userId) {
		// return head node if the target is in first node
		return headNode;

	}
	else if (headNode->getPreviousAddress()->getData()->getUserId() == userId) {
		// return last node if the target is in last node as binary search cannot handle if the last node contains target (for doubly circular linked list)
		return headNode->getPreviousAddress();

	}

	// implements binary search on linkedlist
	Node<User>* first = headNode;
	Node<User>* end = headNode->getPreviousAddress();
	Node<User>* middleNode;

	while (first != end) {
		middleNode = findMiddleUserNode(first, end);

		User* user = middleNode->getData();
		if (user->getUserId() == userId) {
			return middleNode;

		}
		else if (user->getUserId() < userId) {
			first = middleNode->getNextAddress();

		}
		else if (user->getUserId() > userId) {
			end = middleNode->getPreviousAddress();

		}
	}

	return NULL; // no results found
}

Node<User>* findMiddleUserNode(Node<User>* first, Node<User>* last) {
	// find the middle node between the first node and last node.

	Node<User>* pointer_1 = first;
	Node<User>* pointer_2 = first->getNextAddress();

	while (pointer_2 != last && pointer_2->getNextAddress() != last) {
		pointer_1 = pointer_1->getNextAddress();
		pointer_2 = pointer_2->getNextAddress()->getNextAddress();
	}

	return pointer_1;
}

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
