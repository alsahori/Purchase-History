#pragma once
#ifndef ALLPURCHASES_H
#define ALLPURCHASES_H

#include <string>
#include <vector>
using namespace std;
class AllPurchases {
public:
    void LoadFromFile(const string& filename);
    void SaveToFile(const string& filename) const;
    void PrintPurchasesByAccount(const string& accountNumber) const;
    double GetTotalSpend(const string& accountNumber) const;
    void AddNewPurchase();
    void AddMultiplePurchases();

private:
    struct Purchase {
        string accountNumber;
        string itemName;
        double amount;
    };

    vector<Purchase> purchases;
};

#endif
