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
void systemHeading();

int main()
{
    // start the system
    mainInterface();

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

        system("pause");
    }
}
