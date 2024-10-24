#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include "BankAccount.h"
#include "OtherAccountTypes.h"

using namespace std;

void processFile(ifstream& in, ofstream& err, vector<BankAccount*> &accounts);
void printReport(ofstream& out, vector<BankAccount*> accounts);
