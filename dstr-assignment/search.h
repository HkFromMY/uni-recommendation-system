#include <iostream>
#include "User.h"
#include "LinkedList.h"
#include "Node.h"

using namespace std;

// search and delete actions for user records on linked list
Node<User>* searchUser(Node<User>*, int);
Node<User>* findMiddleUserNode(Node<User>*, Node<User>*);

int binary_search(int*, int, int);
int linear_search(int*, int, int);
int jump_search(int*, int, int);
