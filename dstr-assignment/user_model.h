#pragma once
#ifndef user_model_h
#define user_mode_h

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "User.h"
#include "Node.h"
#include "util.h"

using namespace std;

/*
This file contains all functions that interact with the text file of user
It also includes the search and sort operations.
*/

// search and delete actions for user records on linked list
Node<User>* searchUser(Node<User>*, int);
Node<User>* findMiddleUserNode(Node<User>*, Node<User>*);

LinkedList<User>* filterUsersByRole(LinkedList<User>*, int);

// file operations for users - CRUD
LinkedList<User>* loadUserData();
int generateUserId(LinkedList<User>*);
void addNewUserOnFile(User*);
void editUserOnFile(int, string, string, string, string);
void deleteUserOnFile(int);

string latestUserRecordInString(LinkedList<User>*);
void updateLatestUserListOnFile(LinkedList<User>*);

bool checkRecordUniqueness(LinkedList<User>*, string*, string*, string*);
bool checkRecordUniqueness(LinkedList<User>*, int, string*, string*, string*);

#endif