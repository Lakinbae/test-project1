#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "User.h"
#include "Event.h"
#include "Venue.h"
#include "FileHandler.h"

using namespace std;

class EventManager {
private:
    vector<User> users;
    vector<Event> events;
    vector<Venue> venues;
    
    // Track current user by username (simpler than pointers)
    string currentUsername; 

public:
    EventManager() : currentUsername("") {}

    // Initialize with sample data if empty
    void initialize() {
        if (users.empty()) {
            users.push_back(User("admin", "admin", "admin123", "admin@uni.edu", ADMIN));
            venues.push_back(Venue("V1", "Main Hall", 500, 100.0));
        }
    }

    // --- Authentication ---
    bool login(string u, string p) {
        for (const auto& user : users) {
            if (user.username == u && user.password == p) {
                currentUsername = u;
                return true;
            }
        }
        return false;
    }

    void logout() { currentUsername = ""; }
    
    bool isLoggedIn() const { return !currentUsername.empty(); }

    // --- Core Management ---
    
    // Find a user by name
    User* findUser(string name) {
        for (auto& u : users) if (u.username == name) return &u;
        return nullptr;
    }

    // Add event
    void addEvent(Event e) {
        events.push_back(e);
    }

    // Search events (example of using STL algorithm)
    vector<Event> searchEvents(string keyword) {
        vector<Event> results;
        for (const auto& e : events) {
            if (e.title.find(keyword) != string::npos) {
                results.push_back(e);
            }
        }
        return results;
    }

    // --- Persistence ---
    void saveAll() {
        FileHandler::saveUsers("users.txt", users);
        FileHandler::saveEvents("events.txt", events);
    }
};

#endif
