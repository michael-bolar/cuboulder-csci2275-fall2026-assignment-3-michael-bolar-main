/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() { 
    // Check if the list is empty, if so cout << NULL
    if (isEmpty()) {
        cout << "== CURRENT BROWSER HISTORY ==" << endl;
        cout << "Empty History" << endl;
        cout << "NULL" << endl;
        cout << "===" << endl;
    } else {
    // If it's not
        WebPage* page = head;
        int pageID;
        string pageURL;
        bool flag = true;
        cout << "== CURRENT BROWSER HISTORY ==" << endl;
     
        // Iterate through the Linked List
        while(flag == true) {
            if (page->next == nullptr) {
                flag = false;
            }
            // Stores the node's ID
            pageID = page->id;
            // Store each node's URL
            pageURL = page->url;
            // Print each node's ID and URL on the same line
            cout << "[ID:: " << pageID << "]" << "-" << "(URL::" << pageURL << ") -> ";
            // Move to the next pointer
            page = page->next;
        }
        // At the end of the Linked List print NULL
        cout << "NULL" << endl;
        cout << "===" << endl;

    }
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) { 
    if (previousPage == nullptr && head == nullptr) {
        head = newPage;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
    } else if (previousPage == nullptr && head != nullptr) {
        WebPage* temp = head;
        head = newPage;
        head->next = temp;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
    } else {
    // Store the previous pages next node into a temporary node
    WebPage* temp = previousPage->next;
    // Set new page to previous pages next attribute
    previousPage->next = newPage;
    // Set new pages next attribute to the temporary variable
    newPage->next = temp;
    cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
    }
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    addWebPage(nullptr, new WebPage{10, 0, "https://www.colorado.edu/", "", nullptr});
    addWebPage(head, new WebPage{11, 0, "https://www.wikipedia.org/", "", nullptr});
    addWebPage(head->next, new WebPage{12, 0, "https://brilliant.org/", "", nullptr});
    addWebPage(head->next->next, new WebPage{13, 0, "https://www.khanacademy.org/", "", nullptr});
    addWebPage(head->next->next->next, new WebPage{14, 0, "https://www.numberphile.com/", "", nullptr});
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) { 
    // Create a flag
    if (head == nullptr) {
        return nullptr;
    }
    bool flag = true;
    WebPage* page = head;
    // Iterate through the browser history
    while(flag) {
        // At each iteration, check if the input id matches the id of a node at each iteration
        if (id == page->id) {
            // If its found, return a pointer to the page
            flag = false;
            return page;
        } else {
        // Otherwise move to the next pointer
        page = page->next;
        }
        // If the page isn't found in the browser history return NULL
        if (page == nullptr) {
            flag = false;
            return nullptr;
        }
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) { 
    if (head == nullptr) {
        return nullptr;
    }
    bool flag = true;
    WebPage* page = head;
    // Iterate through the browser history
    while(flag) {
        // At each iteration, check if the input id matches the id of a node at each iteration
        if (url == page->url) {
            // If its found, return a pointer to the page
            flag = false;
            return page;
        } else {
        // Otherwise move to the next pointer
        page = page->next;
        }
        // If the page isn't found in the browser history return NULL
        if (page == nullptr) {
            flag = false;
            return nullptr;
        }
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage* page = searchPageByURL(url);
    if (page == nullptr) {
        cout << "Page not found\n";
        return;
    }
    page->owner = owner;
    cout << "The owner (" << owner << ") has been added for the ID - " << page->id << "\n";
}

void BrowserHistory::updateViews(string url) {
    WebPage* page = head;
    while (page != nullptr) {
        if (page->url == url) {
            page->views++;
        }
        page = page->next;
    }
}
