#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    BrowserHistory history;

    int option;
    while (true) {
        displayMenu();
        if (!(cin >> option)) {
            break;
        }
        cin.ignore(10000, '\n');

        switch (option) {
            case 1:
                history.buildBrowserHistory();
                history.displayHistory();
                break;

            case 2:
                history.displayHistory();
                break;

            case 3: {
                string url;
                int id;
                string previousURL;

                cout << "Enter the new web page's url:" << endl;
                getline(cin, url);

                cout << "Enter the new web page's id:" << endl;
                while (!(cin >> id) || (!history.isEmpty() && history.searchPageByID(id) != nullptr)) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cout << "This ID already exists. Try again." << endl;
                    cout << "Enter the new web page's id:" << endl;
                }
                cin.ignore(10000, '\n');

                WebPage* previousPage = nullptr;
                cout << "Enter the previous page's url (or First):" << endl;
                getline(cin, previousURL);
                while (previousURL != "First") {
                    previousPage = history.isEmpty() ? nullptr : history.searchPageByURL(previousURL);
                    if (previousPage != nullptr) {
                        break;
                    }
                    cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                    cout << "Enter the previous page's url (or First):" << endl;
                    getline(cin, previousURL);
                }

                WebPage* newPage = new WebPage{id, 0, url, "", nullptr};
                history.addWebPage(previousURL == "First" ? nullptr : previousPage, newPage);
                history.updateViews(url);
                break;
            }

            case 4: {
                string url;
                string owner;
                WebPage* page = nullptr;
                while (page == nullptr) {
                    cout << "Enter url of the web page to add the owner:" << endl;
                    getline(cin, url);
                    page = history.isEmpty() ? nullptr : history.searchPageByURL(url);
                    if (page == nullptr) {
                        cout << "Page not found. Try again." << endl;
                    }
                }
                cout << "Enter the owner:";
                getline(cin, owner);
                history.addOwner(url, owner);
                break;
            }

            case 5: {
                string url;
                WebPage* page = nullptr;
                while (page == nullptr) {
                    cout << "Enter url of the web page to check the view count: " << endl;
                    getline(cin, url);
                    page = history.isEmpty() ? nullptr : history.searchPageByURL(url);
                    if (page == nullptr) {
                        cout << "Page not found. Try again." << endl;
                    }
                }
                cout << "View count for URL - " << url << " is " << page->views << endl;
                break;
            }

            case 6:
                cout << "Quitting...Goodbye!\n";
                return 0;
        }
    }

    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
