#ifndef VENUE_H
#define VENUE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Types.h"

using namespace std;

struct Venue {
    string id, name, location;
    VenueType type;
    int capacity;
    double costPerHour;
    bool isAvailable;
    
    // STL Containers
    vector<string> facilities;
    vector<string> equipment;
    map<string, vector<string>> bookings; // Date key -> List of Event IDs

    Venue(string i = "", string n = "", int cap = 0, double cost = 0.0)
        : id(i), name(n), capacity(cap), costPerHour(cost), 
          type(CLASSROOM), isAvailable(true) {}

    // --- Logic Functions ---

    void addFacility(const string& f) {
        if (find(facilities.begin(), facilities.end(), f) == facilities.end()) {
            facilities.push_back(f);
        }
    }

    bool isAvailableOn(const string& dateKey) const {
        if (!isAvailable) return false;
        // If the date isn't in the map, it's free
        auto it = bookings.find(dateKey);
        return (it == bookings.end() || it->second.empty());
    }

    void bookVenue(const string& eventId, const string& dateKey) {
        bookings[dateKey].push_back(eventId);
    }

    void display() const {
        cout << "\n--- Venue: " << name << " (" << id << ") ---\n"
             << "Location: " << location << " | Capacity: " << capacity << "\n"
             << "Cost/Hr: $" << costPerHour << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

#endif
