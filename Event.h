#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Types.h"

using namespace std;

struct Event {
    string id, title;
    int maxCapacity;
    vector<RSVP> rsvpList; // STL vector: manages memory for you!

    Event(string i = "", string t = "") 
        : id(i), title(t), maxCapacity(100) {}

    // --- Logic Functions using STL ---

    bool registerUser(string userId, string userName) {
        if (rsvpList.size() < (size_t)maxCapacity) {
            RSVP r(userId, id, userName);
            r.status = CONFIRMED;
            rsvpList.push_back(r); // STL: adds to the end automatically
            return true;
        }
        return false;
    }

    bool cancelRegistration(string userId) {
        // STL: find the item and remove it cleanly
        auto it = remove_if(rsvpList.begin(), rsvpList.end(), 
                  [&](const RSVP& r) { return r.userId == userId; });
        
        if (it != rsvpList.end()) {
            rsvpList.erase(it, rsvpList.end());
            return true;
        }
        return false;
    }

    void displayAttendees() const {
        cout << "\nAttendees for " << title << ":\n";
        for (const auto& r : rsvpList) { // STL: range-based for loop
            cout << "- " << r.userName << " (ID: " << r.userId << ")\n";
        }
    }
};

#endif
