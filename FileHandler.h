#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Types.h"
#include <fstream>
#include <sys/stat.h>

class FileHandler {
private:
    string dataDir;

    // Helper to handle directory creation
    void ensureDir() const {
        struct stat st;
        if (stat(dataDir.c_str(), &st) != 0) {
#ifdef _WIN32
            _mkdir(dataDir.c_str());
#else
            mkdir(dataDir.c_str(), 0755);
#endif
        }
    }

    // Generic Template for Saving
    template <typename T>
    bool saveToFile(const string& filename, const Repository<T>& repo) {
        ensureDir();
        ofstream f(dataDir + "/" + filename);
        if (!f.is_open()) return false;
        for (auto& [key, item] : repo) f << item.serialize() << "\n";
        return true;
    }

    // Generic Template for Loading
    template <typename T>
    bool loadFromFile(const string& filename, Repository<T>& repo) {
        ifstream f(dataDir + "/" + filename);
        if (!f.is_open()) return false;
        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            T item = T::deserialize(line);
            repo.add(item.getKey(), item); // Ensure your objects have a getKey() method
        }
        return true;
    }

public:
    FileHandler(string dir = "data") : dataDir(dir) {}

    // Clean API
    bool saveUsers(Repository<User*>& r)   { return saveToFile("users.dat", r); }
    bool loadUsers(Repository<User*>& r)   { return loadFromFile("users.dat", r); }
    bool saveVenues(Repository<Venue>& r)  { return saveToFile("venues.dat", r); }
    bool loadVenues(Repository<Venue>& r)  { return loadFromFile("venues.dat", r); }
    bool saveEvents(Repository<Event>& r)  { return saveToFile("events.dat", r); }
    bool loadEvents(Repository<Event>& r)  { return loadFromFile("events.dat", r); }

    void logAction(string userId, string action) {
        ensureDir();
        ofstream f(dataDir + "/logs.txt", ios::app);
        if (f.is_open()) {
            time_t now = time(nullptr);
            f << "[" << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") 
              << "] User: " << userId << " - " << action << "\n";
        }
    }
    
    // ... keep your existing CSV export methods here ...
};

#endif
