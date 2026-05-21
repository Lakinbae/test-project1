#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Types.h"

using namespace std;

struct User {
    string id, username, password, email, fullName, phone;
    UserRole role;
    bool isActive;

    User(string i = "", string u = "", string p = "", string e = "", UserRole r = GUEST) 
        : id(i), username(u), password(p), email(e), role(r), isActive(true) {}

    void display() const {
        cout << "User: " << fullName << " | Role: " << role << " | Active: " << (isActive ? "Yes" : "No") << endl;
    }
};

// Helper for saving records to a text file
void saveUsersToFile(const string& filename, const vector<User>& users) {
    ofstream file(filename);
    for (const auto& u : users) {
        file << u.id << "|" << u.username << "|" << u.password << "|" 
             << u.email << "|" << u.fullName << "|" << u.role << "|" 
             << (u.isActive ? "1" : "0") << "\n";
    }
}

#endif
