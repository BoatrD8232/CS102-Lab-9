#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountType; // C = Checking, S = Savings, CD = Certificate of Deposit
    string firstName;
    string lastName;
    string transactionDate; // yyyy-mm-dd format
    string transactionType; // New, Withdrawal, Deposit, Transfer
    int transactionAmount;
    double accountBalance;
    double interestEarned;

public:
    // Constructors
    BankAccount() {
    }
    BankAccount(int accName, string accType, string fName, string lName, string transDate, string transType,
        int transAmt, double accBal) {
        accountNumber = accName;
        accountType = accType;
        firstName = fName;
        lastName = lName;
        transactionDate = transDate;
        transactionType = transType;
        transactionAmount = transAmt;
        accountBalance = accBal;
        interestEarned = 0;
    }
    // Getters
    int getAccNum() { return accountNumber; }
    string getAccType() { return accountType; }
    double getAccBal() { return accountBalance; }
    // Setters
 
    // Utility functions
    void virtual calcInterestEarned();
    void processDeposit(int amount);
    void virtual processWithdrawal(int amount);
    void printDetails(ofstream &out) const;
    void virtual setWithTaken(bool taken);
};
