#include "search.h"
#include "sort.h"
#include "util.h"

#include "common_interface.h"
#include "login.h"

#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

void mainInterface();

int main()
{
    // start the system
    //mainInterface();
    LinkedList<Feedback>* feedback_list = loadFeedbackData("feedback.txt");
    sortFeedbackByDate(feedback_list->getFirstNode());
    feedback_list->displayNodesDetailsFromFront();

    return 0;
}

void mainInterface() {
    int selection = 0;
    while (selection != 3) {
        system("cls");
        systemHeading();
        
        cout << "Please select your action: " << endl;
        cout << "1. Login as Guest." << endl;
        cout << "2. Login as Registered User." << endl;
        cout << "3. Exit the system." << endl;
        cout << "Enter your selection here --> ";
        cin >> selection;

        // clear remaining string elements after extracting the int
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (selection) {
            case 1:
                cout << "Entering guest interface!" << endl;
                break;

            case 2:
                loginInterface();
                break;

            case 3:
                cout << "Exiting the system..." << endl;
                break;

            default:
                // recursion for asking new valid input
                cout << "Please choose a valid option!" << endl;
                system("pause");
                mainInterface();
        }
    }
}
