#include "Functions.h"

bool isDigits(string str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

int accountPos(int acctNumber, vector<BankAccount*>& accounts) {
    return -1;
}

int validDate(string date) {
    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    string day = date.substr(8, 2);
    if (isDigits(year) && isDigits(month) && isDigits(day)) {
        int y = stoi(year);
        int m = stoi(month);
        int d = stoi(day);
        if (y < 1900 || y > 2024)
            return -1;
        else if (m < 1 || m > 12)
            return -1;
        else if (d < 1 || d > 31)
            return -1;
    }
    return 1;
}

void applyInterest(vector<BankAccount*>& accounts) { 
    for (auto i : accounts) {
        i->calcInterestEarned();
        if (i->getAccType() == "CD") {
            i->setWithTaken(false);
        }
    }
}

bool validAccountInfo(vector<string> tokens, ofstream& err, string inRecord) {
    if (!isDigits(tokens.at(0)) || validDate(tokens.at(4)) == -1 || stoi(tokens.at(6)) < 0 || floor(stof(tokens.at(6)) != floor(stof(tokens.at(6))))) {
        return false;
    }
    return true;
}

void processNewAccount(vector<string> tokens, ofstream &err, string inRecord, vector<BankAccount*>& accounts) {

    if (!validAccountInfo(tokens, err, inRecord)) {
        err << setw(40) << "Account data is Invalid:" << inRecord << endl;
        return;
    }
    
    try {
         //ACCT #,TYPE,FIRST NAME,LAST NAME,DATE,TYPE,AMOUNT
        BankAccount* tempAcc;
        if (tokens.at(1) == "C") {
            tempAcc = new Checking(stoi(tokens.at(0)), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4), tokens.at(5), 0, stof(tokens.at(6)));
        }
        else if (tokens.at(1) == "S") {
            tempAcc = new Savings(stoi(tokens.at(0)), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4), tokens.at(5), 0, stof(tokens.at(6)));
        }
        else if (tokens.at(1) == "CD") {
            tempAcc = new CD(stoi(tokens.at(0)), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4), tokens.at(5), 0, stof(tokens.at(6)));
        }
        else {
            throw invalid_argument("Not valid type");
        }
        accounts.push_back(tempAcc);
    }
    catch (...) {
        err << left << setw(40) << "Input Record is Invalid:" << inRecord << endl;
        return;
    }
}

void processTransfer(vector<string> tokens, ofstream& err, string inRecord, vector<BankAccount*>& accounts) {
    if (!validAccountInfo(tokens, err, inRecord) || !isDigits(tokens.at(1))) {
        err << setw(40) << "Transfer data is Invalid:" << inRecord << endl;
        return;
    }
    int amount = stoi(tokens.at(6));
    for (auto i : accounts) {
        if (i->getAccNum() == stoi(tokens.at(0))) {
            for (auto j : accounts) {
                if (j->getAccNum() == stoi(tokens.at(1))) {
                    if (amount < i->getAccBal()) {
                        i->processWithdrawal(amount);
                        j->processDeposit(amount);
                        return;
                    }
                    else {
                        err << setw(40) << "Insufficient funds:" << inRecord << endl;
                        return;
                    }
                }
            }
        }
    }
    err << left << setw(40) << "Id not found:" << inRecord << endl;
}

void processWithdrawal(vector<string> tokens, ofstream& err, string inRecord, vector<BankAccount*>& accounts) {
    int amount = stoi(tokens.at(6));
    if (!validAccountInfo(tokens, err, inRecord)) {
        err << setw(40) << "Withdrawal data is Invalid:" << inRecord << endl;
        return;
    }
    for (auto i : accounts) {
        if (stoi(tokens.at(0)) == i->getAccNum()) {
            if (amount < i->getAccBal()) {
                i->processWithdrawal(amount);
                //if (i->getAccType() == "CD") {
                //    //i->setWithTaken(true);
                //}
                return;
            }
            else {
                err << setw(40) << "Insufficient funds:" << inRecord << endl;
                return;
            }
        }
    }
    err << setw(40) << "Account number not found:" << inRecord << endl;
}

void processDeposit(vector<string> tokens, ofstream& err, string inRecord, vector<BankAccount*>& accounts) {
    if (validDate(tokens.at(4)) == -1) {
        err << setw(40) << "Transaction Date is Invalid:" << inRecord << endl;
        return;
    }
    if (!validAccountInfo(tokens, err, inRecord)) {
        err << setw(40) << "Deposit data is Invalid:" << inRecord << endl;
        return;
    }
    // Check Account type?
    for (auto i : accounts) {
        if (stoi(tokens.at(0)) == i->getAccNum()) {
            i->processDeposit(stof(tokens.at(6)));
            return;
        }
    }
    err << setw(40) << "Account number not found:" << inRecord << endl;
}

void processFile(ifstream& in, ofstream& err, vector<BankAccount*>& accounts) {
   // read the input record
   // verify the type of transaction
   // verify the account number(s) are valid (exist in the current vector)
   // if amounts

    int validAcctIdx1, validAcctIdx2, acctNumber, acctNumber2, transAmount;
    string inRecord, token;
    vector<string> tokens;

    while (getline(in, inRecord)) {
        stringstream inSS(inRecord);
        tokens.clear();
        while (getline(inSS, token, ','))
            tokens.push_back(token);

        cout << "TOKENS FOUND: " << tokens.size() << " : " << inRecord << endl;

        if (tokens.at(5) == "INTEREST") {
            if (validDate(tokens.at(4)) == -1) {
                err << setw(40) << "Transaction Date is Invalid:" << inRecord << endl;
                continue;
            }
            applyInterest(accounts);
            continue;
        }
        else if (tokens.at(5) == "NEW") {
            processNewAccount(tokens, err, inRecord, accounts);
            continue;
        }
        else if (tokens.at(5) == "TRANSFER") {
            processTransfer(tokens, err, inRecord, accounts);
            continue;
        }
        else if (tokens.at(5) == "WITHDRAWAL") {
            processWithdrawal(tokens, err, inRecord, accounts);
            continue;
        }
        else if (tokens.at(5) == "DEPOSIT") {
            processDeposit(tokens, err, inRecord, accounts);
            continue;
        }
        else {
            err << left << setw(40) << "Transaction Type is Invalid:" << inRecord << endl;
            continue;
        }
    }
}


void printReport(ofstream& reportFile, vector<BankAccount*> accounts) {
    reportFile << "-----------------------------------" << endl;
    reportFile << "           Account Report          " << endl;
    reportFile << "-----------------------------------" << endl;
    reportFile << setw(20) << left << "Account Number: "
        << setw(20) << left << "Account Type: "
        << setw(20) << left << "First Name: "
        << setw(15) << left << "Last Name: "
        << setw(18) << left << "Account Balance: "
        << setw(15) << left << "Interest Earned: " << endl;

    //add sort for account numbers
    bool swapped;

    for (int i = 0; i < accounts.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < accounts.size() - i - 1; j++) {
            if (accounts[j]->getAccNum() > accounts[j + 1]->getAccNum()) {
                swap(accounts[j], accounts[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }

    for (int i = 0; i < accounts.size(); i++)
        accounts.at(i)->printDetails(reportFile);

}
