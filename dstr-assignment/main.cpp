#include "search.h"
#include "sort.h"
#include "LinkedList.h"
#include "Date.h"

#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace chrono;

int main()
{

    // can play around for bug hunting
    LinkedList* newList = new LinkedList();
    newList->appendNewNode(new University(1, "University 1"));
    newList->appendNewNode(new University(2, "University 2"));
    newList->appendNewNode(new University(3, "University 3"));
    newList->appendNewNode(new University(4, "University 4"));

    newList->insertNodeAt(new University(5, "University 5"), 2);

    newList->deleteNodeAt(2);

    newList->displayNodesDetails();
}
