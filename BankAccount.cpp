#include "BankAccount.h"

using namespace std;

// Default constructor
 

// Parameterized constructor
 
// Getters  
// Setters  
void BankAccount::calcInterestEarned() {
}
void BankAccount::processDeposit(int dep) {
    accountBalance += dep;
}

void BankAccount::processWithdrawal(int amt) {
    accountBalance -= amt;
}

void BankAccount::printDetails(ofstream &out) const {

    out  << setw(20) << left << accountNumber
         << setw(20) << left << accountType 
         << setw(20) << left << firstName
         << setw(15) << left << lastName
         << setw(10) << right << fixed << setprecision(2) << accountBalance
         << setw(15) << right << fixed << setprecision(2) << interestEarned << endl;

}

void BankAccount::setWithTaken(bool taken) {

}