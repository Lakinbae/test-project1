#include "ConsoleUI.h"

int main() {
    // 1. Initialize the central Manager
    EventManager manager;
    
    // 2. Initialize the UI with the manager
    ConsoleUI ui(manager);

    // 3. Execution wrapper
    try {
        ui.run();
    }
    catch (const exception& e) {
        cerr << "Critical System Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
