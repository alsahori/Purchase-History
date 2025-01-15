#pragma once
#ifndef ALLCUSTOMERS_H
#define ALLCUSTOMERS_H

#include <iostream>
#include <vector>
#include <string>
#include "AllPurchases.h"
using namespace std;

class AllCustomers {
public:
    void LoadFromFile(const string& filename);
    void SaveToFile(const string& filename) const;
    void PrintAllCustomers() const;
    void SortAndPrint();
    void PrintCustomerWithPurchases(const AllPurchases& purchases) const;
    void PrintCustomerTotalSpend(const AllPurchases& purchases) const;
    void AddNewCustomer();
    void AddMultipleCustomers();
    void UpdateCustomerInfo();
    void DeleteCustomer();

private:
    struct Customer {
        string firstName;
        string lastName;
        string accountNumber;
        string streetAddress;
        string city;
        string state;
        string zipCode;
        string phoneNumber;
    };

    std::vector<Customer> customers;
};

#endif
