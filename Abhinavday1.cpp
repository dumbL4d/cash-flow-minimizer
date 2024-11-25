#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// Clear Screen Function for Cross-Platform Compatibility
void clear_screen() {
    // Windows
    #ifdef _WIN32
        system("cls");
    #else
        // Unix-based (Linux/macOS)
        system("clear");
    #endif
}

// Cross-platform function to get console dimensions
void get_console_size(int& width, int& height) {
    #ifdef _WIN32
    // Windows specific code to get console screen size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.dwSize.X;
        height = csbi.dwSize.Y;
    }
    #else
    // Linux/macOS specific code to get console screen size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
    #endif
}

// INTRO SCREEN
void intro() {
    auto start = chrono::high_resolution_clock::now();

    cout << "\n\n\n\n\n\n" << endl;
    cout<<"                          ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄                                                              "<<endl; 
    cout<<"                         ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌▐░▌    ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░▌ ▐░▌   ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌  ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌   ▐░▌ ▐░▌                                                             "<<endl; 
    cout<<"                         ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌    ▐░▌▐░▌                                                             "<<endl; 
    cout<<"                         ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░▌     ▐░▐░▌                                                             "<<endl; 
    cout<<"                         ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌      ▐░░▌                                                             "<<endl; 
    cout<<"                          ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀        ▀▀                                                              "<<endl; 
    cout<<"                                                                                                                                          "<<endl; 
    cout<<"                                                             ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ "<<endl; 
    cout<<"                                                            ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌"<<endl; 
    cout<<"                                                            ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌"<<endl; 
    cout<<"                                                            ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌          ▐░▌          ▐░▌       ▐░▌"<<endl; 
    cout<<"                                                            ▐░▌          ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░▌ ▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌"<<endl; 
    cout<<"                                                            ▐░▌          ▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌▐░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌"<<endl; 
    cout<<"                                                            ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░▌       ▐░▌▐░▌ ▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀█░█▀▀ "<<endl; 
    cout<<"                                                            ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌          ▐░▌     ▐░▌  "<<endl; 
    cout<<"                                                            ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌      ▐░▌ "<<endl; 
    cout<<"                                                            ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌"<<endl; 
    cout<<"                                                             ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀ "<<endl; 
    cout<<"                                                                                                                                          "<<endl; 

    while (true) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
        if (duration >= 5) {
            clear_screen();
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// EXIT SCREEN
void exitscr() {
    auto start = chrono::high_resolution_clock::now();
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "                       ooooooooooooo ooooo   ooooo       .o.       ooooo      ooo oooo    oooo      oooooo   oooo   .oooooo.   ooooo     ooo \n";
    cout << "                       8'   888   `8 `888'   `888'      .888.      `888b.     `8' `888   .8P'        `888.   .8'   d8P'  `Y8b  `888'     `8' \n";
    cout << "                            888       888     888      .8\"888.      8 `88b.    8   888  d8'           `888. .8'   888      888  888       8  \n";
    cout << "                            888       888ooooo888     .8' `888.     8   `88b.  8   88888[              `888.8'    888      888  888       8  \n";
    cout << "                            888       888     888    .88ooo8888.    8     `88b.8   888`88b.             `888'     888      888  888       8  \n";
    cout << "                            888       888     888   .8'     `888.   8       `888   888  `88b.            888      `88b    d88'  `88.    .8'  \n";
    cout << "                           o888o     o888o   o888o o88o     o8888o o8o        `8  o888o  o888o          o888o      `Y8bood8P'     `YbodP'\n";
    cout << "                                                oooooooooooo   .oooooo.   ooooooooo.        ooooo     ooo  .oooooo..o ooooo ooooo      ooo   .oooooo.    \n";
    cout << "                                                `888'     `8  d8P'  `Y8b  `888   `Y88.      `888'     `8' d8P'    `Y8 `888' `888b.     `8'  d8P'  `Y8b   \n";
    cout << "                                                 888         888      888  888   .d88'       888       8  Y88bo.       888   8 `88b.    8  888           \n";
    cout << "                                                 888oooo8    888      888  888ooo88P'        888       8   `\"Y8888o.   888   8   `88b.  8  888           \n";
    cout << "                                                 888    \"    888      888  888`88b.          888       8       `\"Y88b  888   8     `88b.8  888     ooooo \n";
    cout << "                                                 888         `88b    d88'  888  `88b.        `88.    .8'  oo     .d8P  888   8       `888  `88.    .88'  \n";
    cout << "                                                o888o         `Y8bood8P'  o888o  o888o         `YbodP'    8\"\"88888P'  o888o o8o        `8   `Y8bood8P'\n";

    while (true) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
        if (duration >= 3) {
            clear_screen();
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    clear_screen();
    intro();
    exit(0);
}

void main_menu() {
    clear_screen();

    // Menu content
    string menu[] = {
        "+-------------------------------------+",
        "|             Main Menu:              |",
        "+-------------------------------------+",
        "| 1. Create New Participant           |",
        "|                                     |",
        "| 2. Record New Transaction           |",
        "|                                     |",
        "| 3. Display Participant Details      |",
        "|                                     |",
        "| 4. Display Sorted Participants      |",
        "|                                     |",
        "| 5. Display Transactions             |",
        "|                                     |",
        "| 6. Display Transactions Descending  |",
        "|                                     |",
        "| 7. Edit Participant Payment Modes   |",
        "|                                     |",
        "| 8. Edit Transaction Amount          |",
        "|                                     |",
        "| 9. Delete Recent Transaction        |",
        "|                                     |",
        "| 10. Minimize Cashflow               |",
        "|                                     |",
        "| 11. Exit                            |",
        "+-------------------------------------+"
    };

    // Get the dimensions of the console window
    int console_width, console_height;
    get_console_size(console_width, console_height);

    // Calculate where to start printing the menu (centered both vertically and horizontally)
    int menu_height = sizeof(menu) / sizeof(menu[0]);
    int start_row = (console_height - menu_height) / 2;
    int start_col = (console_width - menu[0].length()) / 2;

    // Move the cursor to the starting position (Linux/macOS: printing empty lines for positioning)
    #ifdef _WIN32
    COORD coord = {start_col, start_row};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #else
    // For Linux/macOS, print new lines to simulate cursor positioning
    for (int i = 0; i < start_row; ++i) {
        cout << endl;
    }
    #endif

    // Print the menu
    for (const string& line : menu) {
        // For Linux/macOS: print spaces to center horizontally
        #ifdef _WIN32
            // On Windows, it's already centered, no need for additional spaces
            cout << line << endl;
        #else
            // For Linux/macOS, print spaces before the menu lines to center horizontally
            cout << string(start_col, ' ') << line << endl;
        #endif
    }
}

class person {
public:
    string personUsername;
    string nameOfPerson;
    array<char, 6> modesOfPayment;

    person() : nameOfPerson(""), modesOfPayment({'0', '0', '0', '0', '0', '0'}) {}

    void writeToFile(ofstream& file) const {
        size_t usernameLength = personUsername.size();
        file.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));  // Write length of username
        file.write(personUsername.c_str(), usernameLength);  // Write username string

        size_t nameLength = nameOfPerson.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));  // Write length of the name
        file.write(nameOfPerson.c_str(), nameLength);  // Write name string
        file.write(reinterpret_cast<const char*>(modesOfPayment.data()), modesOfPayment.size());  // Write payment modes
    }

    void readFromFile(ifstream& file) {
        size_t usernameLength;
        file.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));
        personUsername.resize(usernameLength);
        file.read(&personUsername[0], usernameLength);

        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        nameOfPerson.resize(nameLength);
        file.read(&nameOfPerson[0], nameLength);

        file.read(reinterpret_cast<char*>(modesOfPayment.data()), modesOfPayment.size());
    }

    void display() const {
        cout << "Name: " << nameOfPerson << " (Username: " << personUsername << ")\n";
        cout << "Payment Modes: ";
        for (int i = 0; i < 6; ++i) {
            if (modesOfPayment[i] == '1') {
                switch (i) {
                    case 0: cout << "Cash\t"; break;
                    case 1: cout << "PayTM\t"; break;
                    case 2: cout << "GPay\t"; break;
                    case 3: cout << "PhonePe\t"; break;
                    case 4: cout << "Credit Card\t"; break;
                    case 5: cout << "Debit Card\t"; break;
                }
            }
        }
        cout << "\n" << endl;
    }
};

// Function to display participants alphabetically
void displayParticipantsAlphabetically() {
    ifstream file("participants.dat", ios::binary);

    if (!file.is_open()) {
        cout << "Error reading participants file." << endl;
        return;
    }

    vector<person> participants;
    person p;
    while (file) {
        p.readFromFile(file);
        if (file) { 
            participants.push_back(p);
        }
    }

    file.close();

    sort(participants.begin(), participants.end(), [](const person& a, const person& b) {
        return a.nameOfPerson < b.nameOfPerson;
    });

    for (const auto& p : participants) {
        p.display();
    }
}

int main() {
    intro();
    exitscr();
    // main_menu();
}