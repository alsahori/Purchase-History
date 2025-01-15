#include <iostream>
#include "AllCustomers.h"
#include "AllPurchases.h"
using namespace std;

//displaying a menu for users to choose from
void DisplayMenu() {
    cout << "\n--- WELCOME TO AFNANS BAKERY ---\n";
    cout << "1. Print all customers\n";
    cout << "2. Sort and print customers\n";
    cout << "3. Print specific customer's account info and purchases\n";
    cout << "4. Print total spend for a customer\n";
    cout << "5. Add a new customer\n";
    cout << "6. Add multiple customers\n";
    cout << "7. Update customers information\n";
    cout << "8. Delete customers information\n";
    cout << "9. Add a new purchase for a customer\n";
    cout << "10. Add multiple purchases\n";
    cout << "11. Save data to file\n";
    cout << "0. Exit\n";
}

int main() {
    AllCustomers customers;
    AllPurchases purchases;

    customers.LoadFromFile("customer.txt");
    purchases.LoadFromFile("purchases.txt");

    int choice;
    do {
        DisplayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            customers.PrintAllCustomers();
            break;
        case 2:
            customers.SortAndPrint();
            break;
        case 3:
            customers.PrintCustomerWithPurchases(purchases);
            break;
        case 4:
            customers.PrintCustomerTotalSpend(purchases);
            break;
        case 5:
            customers.AddNewCustomer();
            break;
        case 6:
            customers.AddMultipleCustomers();
            break;
        case 7:
            customers.UpdateCustomerInfo();
            break;
        case 8:
            customers.DeleteCustomer();
            break;
        case 9:
            purchases.AddNewPurchase();
            break;
        case 10:
            purchases.AddMultiplePurchases();
            break;
        case 11:
            customers.SaveToFile("customer.txt");
            purchases.SaveToFile("purchases.txt");
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

