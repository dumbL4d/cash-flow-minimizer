#include<iostream>
#include<stdlib.h>
#include<stdexcept>
#include<string>
#include<conio.h>
#include<windows.h>
#include<limits>

// Time Libraries
#include<chrono>
#include<thread>
using namesapce std;

void main_page();
// Clear Screen Function
void clearscreen() {
    system("cls");
}

//INTRO SCREEN
void intro() {
    // Get the start time
    auto start = chrono::high_resolution_clock::now();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n\n\n\n\n\n" << endl;
    cout<<" ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄                                                              "<<endl; 
    cout<<"▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌▐░▌    ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░▌ ▐░▌   ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌  ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌   ▐░▌ ▐░▌                                                             "<<endl; 
    cout<<"▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌    ▐░▌▐░▌                                                             "<<endl; 
    cout<<"▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░▌     ▐░▐░▌                                                             "<<endl; 
    cout<<"▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌      ▐░░▌                                                             "<<endl; 
    cout<<" ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀        ▀▀                                                              "<<endl; 
    cout<<"                                                                                                                 "<<endl; 
    cout<<"                                    ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ "<<endl; 
    cout<<"                                   ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌"<<endl; 
    cout<<"                                   ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌"<<endl; 
    cout<<"                                   ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌          ▐░▌          ▐░▌       ▐░▌"<<endl; 
    cout<<"                                   ▐░▌          ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░▌ ▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌"<<endl; 
    cout<<"                                   ▐░▌          ▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌▐░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌"<<endl; 
    cout<<"                                   ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░▌       ▐░▌▐░▌ ▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀█░█▀▀ "<<endl; 
    cout<<"                                   ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌          ▐░▌     ▐░▌  "<<endl; 
    cout<<"                                   ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌      ▐░▌ "<<endl; 
    cout<<"                                   ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌"<<endl; 
    cout<<"                                    ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀ "<<endl; 
    cout<<"                                                                                                                 "<<endl; 
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    while (true) {
        // Get the current time
        auto end = chrono::high_resolution_clock::now();

        // Calculate the difference in time
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (duration >= 5) {
            system("cls");
            break;
        }

        // Sleep for a while to prevent high CPU usage
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return;
}

//EXIT SCREEN
void exitscr() {
    auto start = chrono::high_resolution_clock::now();
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "ooooooooooooo ooooo   ooooo       .o.       ooooo      ooo oooo    oooo      oooooo   oooo   .oooooo.   ooooo     ooo \n";
    cout << "8'   888   `8 `888'   `888'      .888.      `888b.     `8' `888   .8P'        `888.   .8'   d8P'  `Y8b  `888'     `8' \n";
    cout << "     888       888     888      .8\"888.      8 `88b.    8   888  d8'           `888. .8'   888      888  888       8  \n";
    cout << "     888       888ooooo888     .8' `888.     8   `88b.  8   88888[              `888.8'    888      888  888       8  \n";
    cout << "     888       888     888    .88ooo8888.    8     `88b.8   888`88b.             `888'     888      888  888       8  \n";
    cout << "     888       888     888   .8'     `888.   8       `888   888  `88b.            888      `88b    d88'  `88.    .8'  \n";
    cout << "    o888o     o888o   o888o o88o     o8888o o8o        `8  o888o  o888o          o888o      `Y8bood8P'     `YbodP'\n";
    cout << "                         oooooooooooo   .oooooo.   ooooooooo.        ooooo     ooo  .oooooo..o ooooo ooooo      ooo   .oooooo.    \n";
    cout << "                         `888'     `8  d8P'  `Y8b  `888   `Y88.      `888'     `8' d8P'    `Y8 `888' `888b.     `8'  d8P'  `Y8b   \n";
    cout << "                          888         888      888  888   .d88'       888       8  Y88bo.       888   8 `88b.    8  888           \n";
    cout << "                          888oooo8    888      888  888ooo88P'        888       8   `\"Y8888o.   888   8   `88b.  8  888           \n";
    cout << "                          888    \"    888      888  888`88b.          888       8       `\"Y88b  888   8     `88b.8  888     ooooo \n";
    cout << "                          888         `88b    d88'  888  `88b.        `88.    .8'  oo     .d8P  888   8       `888  `88.    .88'  \n";
    cout << "                         o888o         `Y8bood8P'  o888o  o888o         `YbodP'    8\"\"88888P'  o888o o8o        `8   `Y8bood8P'\n";
    while (true) {
        // Get the current time
        auto end = chrono::high_resolution_clock::now();

        // Calculate the difference in time
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (duration >= 3) {
            system("cls");
            break;
        }

        // Sleep for a while to prevent high CPU usage
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    clearscreen();
    intro();
    exit(0);
}

void main_menu() {
    cout << "                                                     +-------------------------------------+" << endl;
    cout << "                                                     |        Main Menu:                   |" << endl;
    cout << "                                                     +-------------------------------------+" << endl;
    cout << "                                                     | 1.Create New Participant            |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 2. Record New Transaction           |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 3. display participant details      |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 4. display participant details      |" << endl;
    cout << "                                                     | in sorted order                     |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 5. display transactions             |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 6. display tansactions with         |" << endl;
    cout << "                                                     | descending amount                   |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 7. edit participant payment         |" << endl;
    cout << "                                                     | modes                               |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 8.edit transaction amount           |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 9.delete recent transaction         |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 10.Minimize cashflow                |" << endl;
    cout << "                                                     |                                     |" << endl;
    cout << "                                                     | 11. Exit                            |" << endl;
    cout << "                                                     +-------------------------------------+" << endl;
    return;
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
        return string(a.nameOfPerson) < string(b.nameOfPerson);
    });

    
    int count = 0;
    for (const auto& p : participants) {
        cout << "Name of person " << ++count << ": " << p.nameOfPerson << endl;
        cout << "UserName of person " << count << ": " << p.personUsername << endl;
        cout << "Payment Modes Available: ";

       
        for (int i = 0; i < 6; ++i) {
            if (p.modesOfPayment[i] == '1') {
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
}
