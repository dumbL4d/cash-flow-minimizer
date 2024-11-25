#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <string>
#include <cstring>
#include <chrono>
#include <array>
#include <thread>
#include <regex>

using namespace std;
using namespace chrono;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

class person {
public:
    string personUsername;
    string nameOfPerson;
    array<char, 6> modesOfPayment;

    person() : nameOfPerson(""), modesOfPayment({'0', '0', '0', '0', '0', '0'}) {}

    // Serialize to binary format
    void writeToFile(ofstream& file) const {
        size_t usernameLength = personUsername.size();
        file.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));  // Write length of username
        file.write(personUsername.c_str(), usernameLength);  // Write username string

        size_t nameLength = nameOfPerson.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));  // Write length of the name
        file.write(nameOfPerson.c_str(), nameLength);  // Write name string
        file.write(reinterpret_cast<const char*>(modesOfPayment.data()), modesOfPayment.size());  // Write payment modes
    }


    // Deserialize from binary format
    void readFromFile(ifstream& file) {
        size_t usernameLength;
        file.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));  // Read length of username
        personUsername.resize(usernameLength);
        file.read(&personUsername[0], usernameLength);  // Read username string
    
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));  // Read length of the name
        nameOfPerson.resize(nameLength);
        file.read(&nameOfPerson[0], nameLength);  // Read name string
        file.read(reinterpret_cast<char*>(modesOfPayment.data()), modesOfPayment.size());  // Read payment modes
    }


    bool setPaymentMode(const string& paymentMode) {
        static const array<string, 6> validModes = {"Cash", "PayTM", "GPay", "PhonePe", "Credit Card", "Debit Card"};

        for (int i = 0; i < validModes.size(); ++i) {
            if (paymentMode == validModes[i] && modesOfPayment[i] == '0') {
                modesOfPayment[i] = '1';  // Mark this payment mode as selected
                return true;
            }
        }
        return false;  // Invalid or already used payment mode
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

class transaction
{
public:
    string payee;
    string debtor;
    string amount;

    // Serialize to binary format
    void writeToFile(ofstream& file) const {
        // Write the lengths of the strings first
        size_t payeeLength = payee.size();
        size_t debtorLength = debtor.size();
        size_t amountLength = amount.size();

        file.write(reinterpret_cast<const char*>(&payeeLength), sizeof(payeeLength));
        file.write(payee.c_str(), payeeLength); //Write payee string

        file.write(reinterpret_cast<const char*>(&debtorLength), sizeof(debtorLength));
        file.write(debtor.c_str(), debtorLength); //Write debtor string

        file.write(reinterpret_cast<const char*>(&amountLength), sizeof(amountLength));
        file.write(amount.c_str(), amountLength); //Write amount string
    }

    // Deserialize to binary format
    void readFromFile(ifstream& file) {
        size_t payeeLength, debtorLength, amountLength;

        // Read the lengths of the strings
        file.read(reinterpret_cast<char*>(&payeeLength), sizeof(payeeLength));
        payee.resize(payeeLength);
        file.read(&payee[0], payeeLength);

        file.read(reinterpret_cast<char*>(&debtorLength), sizeof(debtorLength));
        debtor.resize(debtorLength);
        file.read(&debtor[0], debtorLength);

        file.read(reinterpret_cast<char*>(&amountLength), sizeof(amountLength));
        amount.resize(amountLength);
        file.read(&amount[0], amountLength);
    }
};

// ! ------------------------------------------------------- ALL FUNCTION DECLARATIONS -------------------------------------------------------
bool validateName(string fullName);
bool validateParticipantUserName(string userName);
bool validateTransactionUserName(string userName);
bool validateAmount(string amount);
void createNewParticipant();
void recordTransaction();
void displayTransactions();
void displayParticipants();
void editParticipantPaymentModes();     // TODO: Edit the payment mode of the participant based on username
void displayParticipantsAlphabetically();
void editTransactionAmount();
void deleteRecentTransaction();
void displayTransactionWithDescendingAmount();
void minimizeCashFlow();
void deleteParticipant();   // TODO: Deletes the participant's details based on username (THIS FUNCTION IS "OPTIONAL")
// ! ------------------------------------------------------------------------------------------------------------------------------------------

void createNewParticipant() {
    ofstream file("participants.dat", ios::binary | ios::app);

    person p;

    // Input person name
    cout << "Enter person name: ";
    getline(cin, p.nameOfPerson);

    // Input payment modes
    int n;
    do {
        cout << "Enter number of payment modes available: ";
        cin >> n;
        if(n > 6 || n <= 0) {
            cout << "Invalid Number of Payment Methods\n";
        }
    }while(n > 6 || n <= 0);
    cin.ignore();  // To discard the newline character left in the buffer

    string paymentMode;
    for (int i = 0; i < n; ++i) {
        bool validMode = false;
        do {
            cout << "Enter mode of payment " << i + 1 << ": ";
            getline(cin, paymentMode);
            validMode = p.setPaymentMode(paymentMode);
            if (!validMode) {
                cout << "Invalid or duplicate payment mode. Please try again.\n";
            }
        } while (!validMode);  // Keep asking until a valid payment mode is provided
    }
    cout << "Enter username: ";
    getline(cin, p.personUsername);

    if (validateParticipantUserName(p.personUsername) && validateParticipantUserName(p.nameOfPerson)) {
        p.writeToFile(file);
        cout << "Participant details added successfully." << endl;
    }else {
        cout << "Participant couldn't be added." << endl;
        cout << "Would you like to try again?(y/n): ";
        char ch;
        if(ch == 'y' || ch == 'Y') {
            createNewParticipant();
        }else {
            main_menu();
        }
    }

    this_thread::sleep_for(seconds(2));
    file.close();
}

void recordTransaction()
{
    ofstream file("transactions.dat", ios::binary | ios::app);

    transaction t;

    // Input payee username
    do
    {
        cout << "Enter payee username: ";
        getline(cin, t.payee);
    } while (!validateTransactionUserName(t.payee));

    // Input debtor username
    do
    {
        cout << "Enter debtor username: ";
        getline(cin, t.debtor);
    } while (!validateTransactionUserName(t.debtor));

    // Input amount
    do
    {
        cout << "Enter amount: ";
        getline(cin, t.amount);
    } while (!validateAmount(t.amount));

    if (!file.is_open())
    {
        cout << "Transaction not recorded." << endl;
        cout << "Would you like to try again?(y/n): ";
        char ch;
        if(ch == 'y' || ch == 'Y') {
            recordTransaction();
        }else {
            main_menu();
        }
    }
    else
    {
        t.writeToFile(file);
        cout << "Transaction recorded successfully. " << endl;
    }

    this_thread::sleep_for(seconds(2));
    file.close();
}

void displayParticipants() {
    ifstream file("participants.dat", ios::binary);

    if (!file.is_open()) {
        cout << "Error reading participants file." << endl;
        return;
    }

    person p;
    int count = 0;

    while (file) {
        p.readFromFile(file);
        if (file) {  // Check if we read a valid person object
            cout << "Name of person " << ++count << ": " << p.nameOfPerson << endl;
            cout << "UserName of person " << count << ": " << p.personUsername << endl;
            cout << "Payment Modes Available: ";

            // Loop through the payment modes and print those that are '1'
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

    if(!count){
        cout << "No participants found." << endl;
    }
    
    file.close();
}

void displayTransactions(){
    ifstream file("transactions.dat", ios::binary);

    if(!file.is_open()){
        cout << "Error reading transactions file." << endl;
        return;
    }

    transaction t;
    int count = 0;

    while (file) {
        t.readFromFile(file); 
        if (file) {  // Check if we read a valid transaction object
            cout << "Transaction " << ++count << ": " << endl;
            cout << "Username of Payee: " << t.payee << endl;
            cout << "Username of Debtor: " << t.debtor << endl; 
            cout << "Amount: " << t.amount << endl;  
            cout << "\n" << endl;
        }
    }

    if(!count){
        cout << "No transactions found." << endl;
    }
    
    file.close();
}

void editParticipantPaymentModes() {
    string username;
    cout << "Enter the username of the participant whose payment modes you want to edit: ";
    getline(cin, username);

    // Read all participants into a vector
    ifstream file("participants.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Error opening participants file." << endl;
        return;
    }

    vector<person> participants;
    person p;

    // Read all participants from file into the vector
    while (file) {
        p.readFromFile(file);
        if (file) {
            participants.push_back(p);  // Add the participant to the vector
        }
    }
    file.close();  // Close the file after reading

    // Search for the participant by username
    bool found = false;
    size_t participantIndex = 0;
    for (size_t i = 0; i < participants.size(); ++i) {
        if (participants[i].personUsername == username) {
            found = true;
            participantIndex = i;
            break;
        }
    }

    if (!found) {
        cout << "Participant with username " << username << " not found." << endl;
        return;
    }

    // Participant found, display current payment modes
    p = participants[participantIndex];  // Get the participant to edit
    cout << "Current payment modes for " << p.nameOfPerson << " (" << p.personUsername << "): ";
    for (int i = 0; i < 6; ++i) {
        if (p.modesOfPayment[i] == '1') {
            switch (i) {
                case 0: cout << "Cash "; break;
                case 1: cout << "PayTM "; break;
                case 2: cout << "GPay "; break;
                case 3: cout << "PhonePe "; break;
                case 4: cout << "Credit Card "; break;
                case 5: cout << "Debit Card "; break;
            }
        }
    }
    cout << endl;

    // Ask if user wants to add or delete a payment mode
    char actionChoice;
    cout << "Do you want to add (a) or delete (d) a payment mode? (a/d): ";
    cin >> actionChoice;
    cin.ignore();  // To ignore any leftover newline character from input buffer

    if (actionChoice == 'a') {
        // Allow user to add a new payment mode
        int modeChoice;
        cout << "Enter the payment mode to add (0: Cash, 1: PayTM, 2: GPay, 3: PhonePe, 4: Credit Card, 5: Debit Card): ";
        cin >> modeChoice;

        if (modeChoice >= 0 && modeChoice <= 5) {
            // Add the selected payment mode if it's not already added
            if (p.modesOfPayment[modeChoice] == '1') {
                cout << "This payment mode is already selected." << endl;
            } else {
                // Mark the selected mode as '1' (selected)
                p.modesOfPayment[modeChoice] = '1';  
                cout << "Payment mode added successfully." << endl;
            }
        } else {
            cout << "Invalid choice. Please enter a number between 0 and 5." << endl;
        }
    } else if (actionChoice == 'd') {
        // Allow user to delete an existing payment mode
        int modeChoice;
        cout << "Enter the payment mode to delete (0: Cash, 1: PayTM, 2: GPay, 3: PhonePe, 4: Credit Card, 5: Debit Card): ";
        cin >> modeChoice;

        if (modeChoice >= 0 && modeChoice <= 5) {
            if (p.modesOfPayment[modeChoice] == '0') {
                cout << "This payment mode is not selected." << endl;
            } else {
                // Set the selected mode to '0' (deleted)
                p.modesOfPayment[modeChoice] = '0';  
                cout << "Payment mode deleted successfully." << endl;
            }
        } else {
            cout << "Invalid choice. Please enter a number between 0 and 5." << endl;
        }
    } else {
        cout << "Invalid choice. Please enter 'a' to add or 'd' to delete." << endl;
        return;
    }

    // Update the participant in the vector with the updated data
    participants[participantIndex] = p;

    // Reopen the file for writing the updated list of participants
    ofstream outFile("participants.dat", ios::binary | ios::trunc);  // Open for writing and truncate the file
    if (!outFile.is_open()) {
        cout << "Error opening participants file for writing." << endl;
        return;
    }

    // Write all participants back to the file, including the updated one
    for (size_t i = 0; i < participants.size(); ++i) {
        participants[i].writeToFile(outFile);  // Write each participant's data to the file
    }

    outFile.close();  // Close the output file
}

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

bool validateName(string fullName)
{
    bool digitCheck = false;
    bool lengthCheck = false;
    bool specialCharCheck = false;
    int nameIndex;

    if (fullName.length() <= 40)
    {
        lengthCheck = true;
    }

    // Loop for Digit Check
    for (nameIndex = 0; nameIndex < fullName.length(); nameIndex++)
    {
        if (fullName[nameIndex] >= 48 && fullName[nameIndex] <= 57 && fullName[nameIndex] != 32)
        {
            digitCheck = true;
            break;
        }
    }

    // Loop for Special Character Check
    for (nameIndex = 0; nameIndex < fullName.length(); nameIndex++)
    {
        if ((fullName[nameIndex] < 65 || fullName[nameIndex] > 90) && (fullName[nameIndex] < 97 || fullName[nameIndex] > 122) && (fullName[nameIndex] < 48 || fullName[nameIndex] > 57) && fullName[nameIndex] != 32)
        {
            specialCharCheck = true;
            break;
        }
    }

    try
    {
        if (specialCharCheck || digitCheck)
        {
            throw "Invalid Name Exception";
        }
        else
        {
            return true;
        }
    }
    catch (const char *e)
    {
        cout << endl << "Exception Ocurred" << endl << e << endl;
        return false;
    }
}

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
        "+---------------------------------------------+",
        "|             Main Menu:                      |",
        "+---------------------------------------------+",
        "| 1. Create New Participant                   |",
        "|                                             |",
        "| 2. Record New Transaction                   |",
        "|                                             |",
        "| 3. Display Participant Details              |",
        "|                                             |",
        "| 4. Display Participants Alphabetically      |",
        "|                                             |",
        "| 5. Display Transactions                     |",
        "|                                             |",
        "| 6. Display Transactions Descending          |",
        "|                                             |",
        "| 7. Edit Participant Payment Modes           |",
        "|                                             |",
        "| 8. Edit Transaction Amount                  |",
        "|                                             |",
        "| 9. Delete Recent Transaction                |",
        "|                                             |",
        "| 10. Minimize Cashflow                       |",
        "|                                             |",
        "| 11. Exit                                    |",
        "+---------------------------------------------+"
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

bool validateParticipantUserName(string userName) 
{
    // !----------------------------------
    // 1. should not be longer than 15 characters
    // 2. should not contain any special character except underscore
    // 3. there should not be any two same usernames in the file
    // !----------------------------------

    // 1. Check if the username is longer than 15 characters
    if (userName.length() > 15) {
        cout << "Username cannot be longer than 15 characters." << endl;
        return false;
    }

    // 2. Check if the username contains only letters, digits, and underscores
    regex validUsernamePattern("^[a-zA-Z0-9_]+$");
    if (!regex_match(userName, validUsernamePattern)) {
        cout << "Username can only contain letters, digits, and underscores." << endl;
        return false;
    }

    // 3. Check if the username already exists in the file
    ifstream file("participants.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Error reading participants file." << endl;
        return false;
    }

    person p;
    while (file) {
        p.readFromFile(file);  // Read a person object from the file
        if (file) {  // Check if a valid person object is read
            if (p.personUsername == userName) {
                cout << "Username already exists. Please choose another username." << endl;
                file.close();
                return false;  // Username already exists in the file
            }
        }
    }

    // If no issues were found, the username is valid
    file.close();
    return true;
}

bool validateTransactionUserName(string userName) 
{
    //Check if the username already exists in the participants file
    ifstream file("participants.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Error reading participants file." << endl;
        return false;
    }

    person p;
    while (file) {
        p.readFromFile(file);  // Read a person object from the file
        if (file) {  // Check if a valid person object is read
            if (p.personUsername == userName) {
                file.close();
                return true;  // Username already exists in the file
            }
        }
    }

    // If username not found in participants file, return error
    cout << "Username not found" << endl;
    file.close();
    return false;
}

bool validateAmount(string amount)
{
    bool digitCheck = true;
    bool negativeCheck = true;
    int amountIndex;

    int length = amount.length();

    // Loop for checking that the amount doesn't have any other character than digits
    for (amountIndex = 0; amountIndex < length; amountIndex++)
    {
        if (amount[amountIndex] < 48 || amount[amountIndex] > 57)
        {
            digitCheck = false;
        }
    }

    // Checking that the amount is greater than zero
    if (stoi(amount) <= 0)
    {
        negativeCheck = false;
    }

    try
    {
        if (!(digitCheck && negativeCheck))
        {
            throw "Invalid Amount";
        }
        else
        {
            return true;
        }
    }
    catch (const char *e)
    {
        cout << endl << "Exception Ocurred" << endl << e << endl;
        return false;
    }
}

int main()
{
    // createNewParticipant();
    // createNewParticipant();
    // editParticipantPaymentModes();
    // displayParticipants();
    // displayParticipantsAlphabetically();
    return 0;
}
