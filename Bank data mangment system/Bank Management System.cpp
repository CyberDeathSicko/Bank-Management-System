#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <sstream>

using namespace std;

class BankAccount {
private:
    int accNo;
    string name;
    string fName;
    string cnic;
    string phoneNumber;
    string email;
    double balance;
    string password; 
    static int nextAccountNumber;

public:
    BankAccount() {
        accNo = nextAccountNumber++;
        balance = 0.0;
        password = generateRandomPassword(); 
    }

    void createAccount() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your father's name: ";
        getline(cin, fName);
        cout << "Enter your CNIC: ";
        getline(cin, cnic);
        cout << "Enter your phone number: ";
        getline(cin, phoneNumber);
        cout << "Enter your email: ";
        getline(cin, email);

        setPassword();

        ofstream file("bank_data.txt", ios::app);
        file << accNo << " " << name << " " << fName << " " << cnic << " " << phoneNumber << " " << email << " " << balance << " " << password << "\n";
        file.close();

        cout << "Account created successfully. Your account number is: " << accNo << endl;
    }

    void depositAmount() {
        string enteredPassword;
        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword != password) {
            cout << "Invalid password. Deposit operation aborted." << endl;
            return;
        }

        double amount;
        cout << "Enter the amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            updateAccountFile();
            cout << "Amount deposited successfully. Current balance: " << balance << endl;
        } else {
            cout << "Invalid amount. Please enter a positive value." << endl;
        }
    }

    void withdrawAmount() {
        string enteredPassword;
        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword != password) {
            cout << "Invalid password. Withdrawal operation aborted." << endl;
            return;
        }

        double amount;
        cout << "Enter the amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            updateAccountFile();
            cout << "Amount withdrawn successfully. Current balance: " << balance << endl;
        } else {
            cout << "Invalid amount or insufficient balance." << endl;
        }
    }

    void checkInfo() {
        string enteredPassword;
        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword != password) {
            cout << "Invalid password. Access to account information denied." << endl;
            return;
        }

        cout << "Account Number: " << accNo << endl;
        cout << "Name: " << name << endl;
        cout << "Father's Name: " << fName << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
    }

private:
    void updateAccountFile() {
        ifstream inFile("bank_data.txt");
        ofstream outFile("temp_data.txt");
        string line;

        while (getline(inFile, line)) {
            stringstream ss(line);
            int acc;
            string pass;
            ss >> acc;
            if (acc == accNo) {
                outFile << accNo << " " << name << " " << fName << " " << cnic << " " << phoneNumber << " " << email << " " << balance << " " << password << "\n";
            } else {
                outFile << line << "\n";
            }
        }

        inFile.close();
        outFile.close();

        remove("bank_data.txt");
        rename("temp_data.txt", "bank_data.txt");
    }

    string generateRandomPassword() {
        const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t passwordLength = 8;
        string password;
        for (size_t i = 0; i < passwordLength; i++) {
            password.push_back(charset[rand() % charset.length()]);
        }
        return password;
    }

    void setPassword() {
        cout << "Set a secure password for your account: ";
        cin >> password;
    }
};

int BankAccount::nextAccountNumber = 1;

int main() {
    char choice;
    map<int, BankAccount> accounts;

    srand(time(nullptr);

    cout << "\n\n\n\t\t......:::Banking System:::......";
    cout << "\n\t\t:: press 1 to Login to Account :: ";
    cout << "\n\t\t:: press 2 to Create Account    ::";
    cout << "\n\t\t:: press 0 to Exit              ::";
    cout << "\n\t\t:: ...........................   ::\n\t\t\t\t";
    cin >> choice;

    switch (choice) {
        case '1':
            int accountNumber;
            cout << "Enter your account number: ";
            cin >> accountNumber;

            auto accountIt = accounts.find(accountNumber);
            if (accountIt == accounts.end()) {
                cout << "Account not found. Please check your account number." << endl;
                return 1;
            }

            BankAccount& account = accountIt->second;

            while (true) {
                cout << "\n\n\n\t\t.......:::Banking System:::.......";
                cout << "\n\t\t:: press 1 to Deposit Amount    :: ";
                cout << "\n\t\t:: press 2 to Withdraw Amount   ::";
                cout << "\n\t\t:: press 3 to Check Info       ::";
                cout << "\n\t\t:: press 0 to Exit Menu        ::";
                cout << "\n\t\t:: ........................... ::\n\t\t\t\t";
                cin >> choice;

                switch (choice) {
                    case '1':
                        account.depositAmount();
                        break;
                    case '2':
                        account.withdrawAmount();
                        break;
                    case '3':
                        account.checkInfo();
                        break;
                    case '0':
                        return 0;
                    default:
                        cout << "Invalid Choice...!";
                }
                system("pause");
                system("cls");
            }
            break;
        case '2':
            BankAccount newAccount;
            newAccount.createAccount();
            accounts[newAccount.getAccountNumber()] = newAccount; // Store the new account in the map
            break;
        case '0':
            return 0;
        default:
            cout << "\n Invalid choice...! ";
    }
    return 0;
}