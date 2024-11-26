void displayTransactionsInDescendingOrder() {
    ifstream file("transactions.dat", ios::binary);

    if (!file.is_open()) {
        cout << "Error reading transactions file." << endl;
        return;
    }

    vector<transaction> transactions; 
    transaction t;

    while (file) {
        t.readFromFile(file);
        if (file) { 
            transactions.push_back(t);
        }
    }

    file.close();

    // Sort transactions in descending order by amount
    sort(transactions.begin(), transactions.end(), [](const transaction& a, const transaction& b) {
        return stod(a.amount) > stod(b.amount); // Convert string amount to double for comparison
    });

    // Display transactions
    if (transactions.empty()) {
        cout << "No transactions found." << endl;
        return;
    }

    int count = 0;
    for (const auto& tr : transactions) {
        cout << "Transaction " << ++count << ": " << endl;
        cout << "Username of Payee: " << tr.payee << endl;
        cout << "Username of Debtor: " << tr.debtor << endl;
        cout << "Amount: " << tr.amount << endl;
        cout << "\n" << endl;
    }
}
