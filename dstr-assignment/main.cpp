#include "search.h"
#include "util.h"
#include "login.h"
#include "common_interface.h"
#include "feedback_model.h"
#include "favourite_model.h"
#include "university_model.h"
#include "input_validation.h"
#include "guest.h"
#include "HashMap.h"

#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

void mainInterface();

int main()
{
    // start the system
    mainInterface();

    return 0;
}

void mainInterface() {
    int selection = 0;

    // upon booting up of the program load all data required
    LinkedList<User>* userList = loadUserData();
    LinkedList<University>* uniList = loadUniversitiesData();
    LinkedList<Favourite>* favouriteList = loadFavouriteData();
    LinkedList<Feedback>* feedbackList = loadFeedbackData();

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
                guestInterface(userList, uniList);
                break;

            case 2:
                loginInterface(userList, uniList, feedbackList, favouriteList);
                break;

            case 3:
                cout << "Exiting the system..." << endl;
                break;

            default:
                // recursion for asking new valid input
                cout << "Please choose a valid option!" << endl;
                system("pause");
                return mainInterface();
        }
    }

    // update latest data structures on respective text file (uni data is read-only)
    updateLatestUserListOnFile(userList);
    updateLatestFeedbacksOnTextFile(feedbackList);
    updateLatestFavouritesOnTextFile(favouriteList);
}
