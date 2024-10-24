// CS201L-Lab9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Functions.h"
#include "BankAccount.h"
#include "OtherAccountTypes.h"

int main()
{
    ifstream inFile;
    ofstream reportFile, errFile;

    inFile.open("BankInfo.csv");
    reportFile.open("report.txt");
    errFile.open("error.txt");

    if (!inFile.good() || !reportFile.good() || !errFile.good()) {
        cout << "Unable to open files for processing\n";
        return 0;
    }

    vector<BankAccount*> accounts;

    processFile(inFile, errFile, accounts);
    printReport(reportFile, accounts);

    inFile.close();
    reportFile.close();
    errFile.close();
}