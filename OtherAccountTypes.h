#pragma once
#include "BankAccount.h"

class Checking : public BankAccount {
public:
	// Constructor
	Checking(int accName, string accType, string fName, string lName, string transDate, string transType,
		int transAmt, double accBal
	) : BankAccount(accName, accType, fName, lName, transDate, transType, transAmt, accBal) {};
	void calcInterestEarned() {
		return;
	}
};


//*******************************************************
class Savings : public BankAccount {
public:
	// Constructor
	Savings(int accName, string accType, string fName, string lName, string transDate, string transType,
		int transAmt, double accBal
	) : BankAccount(accName, accType, fName, lName, transDate, transType, transAmt, accBal) {};

	void calcInterestEarned() {
		if (accountBalance >= 100 && accountBalance < 1000) {
			interestEarned += (5.0 / 365 * .05) * accountBalance;
			accountBalance += (5.0 / 365 * .05) * accountBalance;
		}
		else if (accountBalance >= 1000) {
			interestEarned += (5.0 / 365 * .075) * accountBalance;
			accountBalance += (5.0 / 365 * .075) * accountBalance;
		}
	}

};

//*******************************************************
class CD : public BankAccount {

private:
	bool withdrawalTaken = false;

public:
	// Constructor
	CD(int accName, string accType, string fName, string lName, string transDate, string transType,
		int transAmt, double accBal
	) : BankAccount(accName, accType, fName, lName, transDate, transType, transAmt, accBal) {};

	void calcInterestEarned() {
		if (withdrawalTaken) {
			interestEarned += (5.0 / 365 * .025) * accountBalance;
			accountBalance += (5.0 / 365 * .025) * accountBalance;
		}
		else {
			interestEarned += (5.0 / 365 * .1) * accountBalance;
			accountBalance += (5.0 / 365 * .1) * accountBalance;
		}
	}

	void processWithdrawal(int amount) {
		withdrawalTaken = true;
		accountBalance -= amount;
	}

	void setWithTaken(bool taken) { withdrawalTaken = taken; }
};

