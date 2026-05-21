#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "EventManager.h"
#include <iostream>
#include <limits>

using namespace std;

class ConsoleUI {
private:
    EventManager& mgr;
    
    // Helper to get input cleanly
    int getChoice(int min, int max) {
        int c;
        while (true) {
            cout << "\nChoice (" << min << "-" << max << "): ";
            if (cin >> c && c >= min && c <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return c;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

public:
    ConsoleUI(EventManager& m) : mgr(m) {}

    void run() {
        while (true) {
            if (!mgr.isLoggedIn()) {
                cout << "\n1. Login | 2. Register | 3. Exit\n";
                int c = getChoice(1, 3);
                if (c == 3) break;
                // ... handle auth ...
            } else {
                showMenu();
            }
        }
    }

    void showMenu() {
        cout << "\n--- DASHBOARD ---\n"
             << "1. Events (View/Search)\n"
             << "2. My Registrations\n"
             << "3. Admin/Faculty Tools\n"
             << "0. Logout\n";
        
        int c = getChoice(0, 3);
        switch(c) {
            case 1: handleEventActions(); break;
            case 2: /* viewMyRegistrations */ break;
            case 3: handleAdvancedActions(); break;
            case 0: mgr.logout(); break;
        }
    }

    void handleEventActions() {
        cout << "\n1. View Upcoming | 2. Register | 3. Search\n";
        int c = getChoice(1, 3);
        // Dispatch to manager functions...
    }

    void handleAdvancedActions() {
        // Only show if user is Admin or Faculty
        if (mgr.getCurrentUser()->role == STUDENT) {
            cout << "Access Denied!\n";
            return;
        }
        cout << "\n1. Create Event | 2. Add Venue | 3. Budget Report\n";
        int c = getChoice(1, 3);
        // Dispatch...
    }
};

#endif
