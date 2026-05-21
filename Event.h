#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Types.h"

using namespace std;

struct Event {
    string id, title, description, venueId;
    EventType type;
    EventStatus status;
    Date start, end;
    int maxCapacity, currentRegs;
    Budget budget;
    vector<RSVP> rsvpList;

    Event(string i = "", string t = "") 
        : id(i), title(t), type(OTHER), status(DRAFT), 
          maxCapacity(100), currentRegs(0) {}

    // --- Logic Functions ---

    bool registerUser(string userId, string userName) {
        if (currentRegs < maxCapacity) {
            RSVP r(userId, id, userName);
            r.status = CONFIRMED;
            rsvpList.push_back(r);
            currentRegs++;
            return true;
        }
        return false;
    }

    bool cancelRegistration(string userId) {
        for (size_t i = 0; i < rsvpList.size(); i++) {
            if (rsvpList[i].userId == userId) {
                rsvpList.erase(rsvpList.begin() + i);
                currentRegs--;
                return true;
            }
        }
        return false;
    }

    void display() const {
        cout << "\n--- Event: " << title << " ---\n"
             << "Status: " << status << " | Capacity: " << currentRegs << "/" << maxCapacity << endl;
    }

    void displayAttendees() const {
        cout << "\nAttendees for " << title << ":\n";
        for (const auto& r : rsvpList) {
            cout << "- " << r.userName << " (ID: " << r.userId << ")\n";
        }
    }
};

#endif
