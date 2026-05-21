#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ========== ENUMS ==========
// Keep these for internal logic, but we won't need big conversion functions
enum EventType { ACADEMIC, CULTURAL, SPORTS, WORKSHOP, OTHER };
enum VenueType { AUDITORIUM, CLASSROOM, LABORATORY, OUTDOOR, OTHER_VENUE };
enum RSVPStatus { CONFIRMED, PENDING, CANCELLED, ATTENDED };

// ========== DATE STRUCT ==========
// Just the basics. Simple to set and print.
struct Date {
    int day, month, year;
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
};

// ========== BUDGET STRUCT ==========
// Core financial logic only.
struct Budget {
    double expenses, revenue, ticketPrice;
    int attendees;

    Budget() : expenses(0), revenue(0), ticketPrice(0), attendees(0) {}

    double getNet() const { return (ticketPrice * attendees) - expenses; }
};

// ========== RSVP STRUCT ==========
struct RSVP {
    string userId, eventId;
    RSVPStatus status;
    Date regDate;

    RSVP(string u, string e) : userId(u), eventId(e), status(PENDING) {}
};

// ========== SEARCH FILTER STRUCT ==========
struct SearchFilter {
    string keyword;
    int typeIndex; // Just store the user's choice as an integer
    bool isActive;

    SearchFilter() : typeIndex(0), isActive(false) {}
};

#endif
