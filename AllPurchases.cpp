#include "AllPurchases.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//function loading data from file
void AllPurchases::LoadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        Purchase temp;
        getline(ss, temp.accountNumber, ',');
        getline(ss, temp.itemName, ',');
        ss >> temp.amount;
        purchases.push_back(temp);
    }
    file.close();
}

//function to save infromation to file
void AllPurchases::SaveToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& purchase : purchases) {
        file << purchase.accountNumber << "," << purchase.itemName << "," << purchase.amount << "\n";
    }
    file.close();
}

//function to print purchases from account number
void AllPurchases::PrintPurchasesByAccount(const string& accountNumber) const {
    cout << "Purchases for Account " << accountNumber << ":\n";
    int count = 1;
    bool found = false;
    for (const auto& purchase : purchases) {
        if (purchase.accountNumber == accountNumber) {
            cout << "Purchase: " << purchase.itemName << " - $" << purchase.amount << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No purchases found for this account.\n";
    }
    cout << "------------------------------------\n";
}

//function that gets the total spending for a customer
double AllPurchases::GetTotalSpend(const string& accountNumber) const {
    double total = 0;
    for (const auto& purchase : purchases) {
        if (purchase.accountNumber == accountNumber) {
            total += purchase.amount;
        }
    }
    return total;
}

//function that adds new purchases for a customer
void AllPurchases::AddNewPurchase() {
    Purchase temp;
    cout << "Enter account number: ";
    cin >> temp.accountNumber;

    // Check if the account number exists
    bool accountFound = false;
    for (const auto& purchase : purchases) {
        if (purchase.accountNumber == temp.accountNumber) {
            accountFound = true;
            break;
        }
    }

    // If the account number isn't found, show an error and exit
    if (!accountFound) {
        cout << "Error: Account number not found. Please enter a valid account number.\n";
        return;  // Exit the function early
    }

   
    cout << "Enter item name: ";
    cin.ignore();
    getline(cin, temp.itemName);
    cout << "Enter amount of the item: ";
    cin >> temp.amount;

    purchases.push_back(temp);
}

//function that adds multiple purchases for a customer
void AllPurchases::AddMultiplePurchases() {
    char choice;
    do {
        AddNewPurchase();
        cout << "Add another purchase? (y/n): ";
        cin >> choice;
     while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        cout << "Invalid input. Please enter 'y' or 'n': ";
        cin >> choice;
    }
}while (choice != 'n' && choice != 'N');
}


