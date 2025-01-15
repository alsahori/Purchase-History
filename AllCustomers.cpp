#include "AllCustomers.h"
#include <fstream>
#include<iomanip>
#include <algorithm>

using namespace std;

//function to check if the input contains only numbers
bool isNumeric(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;  // If any character is not a digit, return false
        }
    }
    return true;  // All characters are digits
}

//function to check if the input string contains only alphabets
bool isAlpha(const string& input) {
    for (char c : input) {
        if (!isalpha(c)) {
            return false;  // If any character is not a letter, return false
        }
    }
    return true;  // All characters are alphabetic
}

//function to check if the input string contains only alphabets or spaces
bool isAlphaWithSpaces(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') { // Check if character is not a letter or space
            return false;
        }
    }
    return true;
}

//loading customers from file
void AllCustomers::LoadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;

    Customer temp;
    while (file >> temp.firstName >> temp.lastName >> temp.accountNumber >> temp.streetAddress >>
        temp.city >> temp.state >> temp.zipCode >> temp.phoneNumber) {
        customers.push_back(temp);
    }
    file.close();
}

//saves customers data to file
void AllCustomers::SaveToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& customer : customers) {
        file << customer.firstName << " " << customer.lastName << " " << customer.accountNumber
            << " " << customer.streetAddress << " " << customer.city << " " << customer.state
            << " " << customer.zipCode << " " << customer.phoneNumber << "\n";
    }
    file.close();
}

//prints all customers details
void AllCustomers::PrintAllCustomers() const {
    for (const auto& customer : customers) {
        cout << "Account Number: " << customer.accountNumber << "\n";
        cout << "Name: " << customer.firstName << " " << customer.lastName << "\n";
        cout << "Address: " << customer.streetAddress << ", "
            << customer.city << ", "
            << customer.state << ", "
            << customer.zipCode << "\n";
        cout << "Phone: " << customer.phoneNumber << "\n";
        cout << "-------------------------\n";
    }
}

//sorting and printing out customers list and details based on their last name
void AllCustomers::SortAndPrint() {
    int choice;
    bool validInput = false;

    // Loop until valid input is received
    while (!validInput) {
        // Prompt the user for sorting order
        cout << "---SORTING CUSTOMERS LIST---" << endl;
        cout << "Choose sorting order by LAST name:\n";
        cout << "1. Ascending (A-Z)\n";
        cout << "2. Descending (Z-A)\n";
        cout << "Enter your choice (1 or 2): ";

        // Check if the input is an integer
        if (cin >> choice) {
            // Check if the input is either 1 or 2
            if (choice == 1 || choice == 2) {
                validInput = true;  // Input is valid, exit the loop
            }
            else {
                cout << "\nInvalid input! Please enter 1 or 2.\n";
            }
        }
        else {
            // printing invalid if input is not an integer
            cout << "\nInvalid input! Please enter a valid number (1 or 2).\n";
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the line
        }
    }

    // Sorting based on last name
    if (choice == 1) {
        // Sort in ascending order (A-Z)
        sort(customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {
            return a.lastName < b.lastName;  // Ascending order based on last name
            });
    }
    else if (choice == 2) {
        // Sort in descending order (Z-A)
        sort(customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {
            return a.lastName > b.lastName;  // Descending order based on last name
            });
    }

    // Print the sorted list of customers
    PrintAllCustomers();
}

//function to print all customers with their purchases
void AllCustomers::PrintCustomerWithPurchases(const AllPurchases& purchases) const {
    string accountNumber;
    cout << "---PRINTING A CUSTOMER'S PURCHASES---\n";
    cout << "Enter account number: ";
    cin >> accountNumber;

    auto it = find_if(customers.begin(), customers.end(),
        [accountNumber](const Customer& c)
        { return c.accountNumber == accountNumber; });

    if (it != customers.end()) {
        cout << it->firstName << " " << it->lastName << ":\n";
        purchases.PrintPurchasesByAccount(accountNumber);
    }
    else {
        cout << "Customer not found.\n";
    }
}

//function to print total spending for a customer
void AllCustomers::PrintCustomerTotalSpend(const AllPurchases& purchases) const {
    string accountNumber;
    cout << "---PRINTING A CUSTOMER'S TOTAL SPENDING---" << endl;
    cout << "Enter account number: ";
    cin >> accountNumber;

    double totalSpend = purchases.GetTotalSpend(accountNumber);
    cout << "Total spend for account " << accountNumber << ": $"
        << fixed << setprecision(2) << totalSpend << "\n";
    cout << "-------------------------\n";
}

//function to add a new customer
void AllCustomers::AddNewCustomer() {
    Customer temp;
    cout << "--ADDING A NEW CUSTOMER--"<<endl;
    cout << "First and last name: ";
    while (true) {
        cin >> temp.firstName >> temp.lastName;
        if (isAlpha(temp.firstName) && isAlpha(temp.lastName)) {
            break;
        }
        else {
            cout << "Invalid input. Only letters are allowed for first and last name. Try again: ";
        }
    }


    cout << "Enter account number: ";
    while (true) {
        cin >> temp.accountNumber;
        if (isNumeric(temp.accountNumber)) {
            break;  // Exit loop if the input is valid
        }
        else {
            cout << "Invalid input. Enter numeric account number: ";
        }
    }

    cin.ignore(); 

    cout << "Enter street address: ";
    getline(cin, temp.streetAddress);

    cout << "Enter city: ";
    while (true) {
        getline(cin, temp.city);
        if (isAlphaWithSpaces(temp.city)) {
            break;
        }
        else {
            cout << "Invalid input. Only letters are allowed for city. Try again: ";
        }
    }


    cout << "Enter state (e.g., New York): ";
    while (true) {
        getline(cin, temp.state);
        if (isAlphaWithSpaces(temp.state)) {
            break;
        }
        else {
            cout << "Invalid input. Only letters are allowed for state. Try again: ";
        }
    }

    // Validate zip code (only numeric)
    cout << "Enter zip code: ";
    while (true) {
        cin >> temp.zipCode;
        if (isNumeric(temp.zipCode)) {
            break;  // Exit loop if the input is valid
        }
        else {
            cout << "Invalid input. Enter numeric zip code: ";
        }
    }

    // Validate phone number (only numeric)
    cout << "Enter phone number: ";
    while (true) {
        cin >> temp.phoneNumber;
        if (isNumeric(temp.phoneNumber)) {
            break;  // Exit loop if the input is valid
        }
        else {
            cout << "Invalid input. Enter numeric phone number: ";
        }
    }

    customers.push_back(temp);

    cout << "Customer added successfully!" << endl;
}

//function to add multiple customers 
void AllCustomers::AddMultipleCustomers() {
    char choice;
    do {

        AddNewCustomer();
        cout << "Add another customer? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            cout << "Invalid inpute. Please enter y/n.\n";
            cin >> choice;
        }
    } while (choice != 'n' && choice != 'N');
}

//function that updates a customers information
void AllCustomers::UpdateCustomerInfo() {
    string accountNumber;
    cout << "---UPDATING CUSTOMERS INFORMATION---\n";
    cout << "Enter account number: ";
    cin >> accountNumber;

    for (auto& customer : customers) {
        if (customer.accountNumber == accountNumber) {
            cout << "Updating details for customer: " << customer.firstName << " " << customer.lastName << "\n";

            cout << "First and last name: ";
            while (true) {
                cin >> customer.firstName >> customer.lastName;
                if (isAlpha(customer.firstName) && isAlpha(customer.lastName)) {
                    break;
                }
                else {
                    cout << "Invalid input. Only letters are allowed for first and last name. Try again: ";
                }
            }
            cout << "Enter account number: ";
            while (true) {
                cin >> customer.accountNumber;
                if (isNumeric(customer.accountNumber)) {
                    break;  // Exit loop if the input is valid
                }
                else {
                    cout << "Invalid input. Enter numeric account number: ";
                }
            }

            cin.ignore();  // To consume the newline left by cin

            cout << "Enter street address: ";
            getline(cin, customer.streetAddress);

            cout << "Enter city: ";
            // Allow only alphabetic input for city
            while (true) {
                getline(cin, customer.city);
                if (isAlphaWithSpaces(customer.city)) {
                    break;
                }
                else {
                    cout << "Invalid input. Only letters are allowed for city. Try again: ";
                }
            }

            cout << "Enter state (e.g., New York): ";
            while (true) {
                getline(cin, customer.state);
                if (isAlphaWithSpaces(customer.state)) {
                    break;
                }
                else {
                    cout << "Invalid input. Only letters are allowed for state. Try again: ";
                }
            }

            // Validate zip code (only numeric)
            cout << "Enter zip code: ";
            while (true) {
                cin >> customer.zipCode;
                if (isNumeric(customer.zipCode)) {
                    break;  // Exit loop if the input is valid
                }
                else {
                    cout << "Invalid input. Enter numeric zip code: ";
                }
            }

            // checking for numeric input
            cout << "Enter phone number: ";
            while (true) {
                cin >> customer.phoneNumber;
                if (isNumeric(customer.phoneNumber)) {
                    break;  // Exit loop if the input is valid
                }
                else {
                    cout << "Invalid input. Enter numeric phone number: ";
                }
            }

            cout << "Customer information updated successfully.\n";
            return;
        }
    }
    cout << "Customer with account number " << accountNumber << " not found.\n";

}

//function that deletes a customer from list
void AllCustomers::DeleteCustomer() {

    string accountNumber;
    cout << "---DELETING CUSTOMERS INFORMATION---\n";
    cout << "Enter account number of the customer to delete: ";
    cin >> accountNumber;


    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->accountNumber == accountNumber) {
            customers.erase(it);
            cout << "Customer with account number " << accountNumber << " was deleted successfully.\n";
            return;
        }
    }
    cout << "Customer with account number " << accountNumber << " not found.\n";

}


