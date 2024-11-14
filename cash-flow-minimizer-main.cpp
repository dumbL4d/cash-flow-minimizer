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

using namespace std;
using namespace chrono;

class person {
public:
    string personUsername;    // TODO: make a function that takes input of username and read the whole file for the same username id if the id is found, print error else, write the data in the file also the username can't be same as the person name
    string nameOfPerson;
    array<char, 6> modesOfPayment;

    person() : nameOfPerson(""), modesOfPayment({'0', '0', '0', '0', '0', '0'}) {}

    // Serialize to binary format
    void writeToFile(ofstream& file) const {
        size_t nameLength = nameOfPerson.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));  // Write length of the name
        file.write(nameOfPerson.c_str(), nameLength);  // Write name string
        file.write(reinterpret_cast<const char*>(modesOfPayment.data()), modesOfPayment.size());  // Write payment modes
    }

    // Deserialize from binary format
    void readFromFile(ifstream& file) {
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
bool validateAmount(string amount);
void createNewParticipant();
void editParticipantPaymentModes();     // TODO: Edit the payment mode of the participant based on username
void recordTransaction();
void editTransactionAmount();
void deleteRecentTransaction();
void displayParticipants();
void displayParticipantsAlphabetical();
void displayTransactions();
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

    p.writeToFile(file);
    cout << "Participant details added successfully." << endl;

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
    displayParticipants();
    return 0;
}
