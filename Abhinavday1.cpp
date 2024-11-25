#include <bits/stdc++.h>
using namesapce std;
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
