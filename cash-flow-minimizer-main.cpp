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
};

class transaction
{
public:
    string payee;
    string debtor;
    string amount;
};

// ! ------------------------------------------------------- ALL FUNCTION DECLARATIONS -------------------------------------------------------
bool validateName(string fullName);
bool validateUserName(string userName);
bool validateAmount(string amount);
void createNewParticipant();
void recordTransaction();
void displayTransactions();
void displayParticipants();
void editParticipantPaymentModes();     // TODO: Edit the payment mode of the participant based on username
void editTransactionAmount();
void deleteRecentTransaction();
void displayParticipantsAlphabetical();
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

    if (validateUserName(p.personUsername) && validateName(p.nameOfPerson)) {
        p.writeToFile(file);
        cout << "Participant details added successfully." << endl;
    }else {
        cout << "Participant couldn't be added." << endl;
        cout << "Would you like to try again?(y/n): ";
        char ch;
        if(ch == 'y' || ch == 'Y') {
            createNewParticipant();
        }else {
            // ! MAIN MENU FUNCTION WILL BE CALLED HERE
        }
    }

    this_thread::sleep_for(seconds(2));
    file.close();
}

void recordTransaction()
{
    fstream file;

    transaction *t = new transaction;

    do
    {
        cout << "Enter payee name: ";
        getline(cin, t->payee);
    } while (!validateName(t->payee));

    do
    {
        cout << "Enter debtor name: ";
        getline(cin, t->debtor);
    } while (!validateName(t->debtor));

    do
    {
        cout << "Enter amount: ";
        getline(cin, t->amount);
    } while (!validateAmount(t->amount));

    file.open("transactions.dat", ios::binary | ios::in | ios::out | ios::app);

    if (!file.is_open())
    {
        cout << "Transaction not recorded." << endl;
    }
    else
    {
        file.write(reinterpret_cast<const char*>(&t), sizeof(transaction));
        cout << "Transaction recorded successfully. " << endl;
    }

    file.close();

    delete t;
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

    file.close();
}

void displayTransactions(){
    ifstream file;

    file.open("transactions.dat", ios::binary);

    if(!file.is_open()){
        cout << "Error reading transactions file." << endl;
        return;
    }

    transaction t;

    while (file.read(reinterpret_cast<char*>(&t), sizeof(transaction)))
    {
        cout << t.debtor << " owes " << t.amount << " to " << t.payee << endl;
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

bool validateUserName(string userName) 
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
    displayParticipants();
    return 0;
}
