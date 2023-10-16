#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
protected:
    long long accountNumber;
    int pin;
    double balance;

public:
    Account(long long accNumber, int pin, double balance)
        : accountNumber(accNumber), pin(pin), balance(balance) {}

    bool checkPin(int enteredPin) {
        return pin == enteredPin;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    // Method Overloading: Different parameter lists
    /*In this application method overloading is used for withdraw method. Initially withdraw method accepts input
    of type int. To allow transactions of large amounts int as a parameter is not supported. Thus method overloading
    is performed on the same method to allow transactions of large amounts*/

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }

    void withdraw(int amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }

    long long getAccountNumber(){
        return accountNumber;
    }
};

//Inheritance -> PremiumAccount extends Account class
class PremiumAccount : public Account {
public:
    PremiumAccount(long long accNumber, int pin, double balance)
        : Account(accNumber, pin, balance) {}

    // Method Overriding: Providing a specific implementation in the subclass
    void withdraw(double amount) override {
        if (amount <= getBalance()) {
            double fee = amount * 0.02;  // 2% withdrawal fee for premium accounts
            balance -= (amount + fee);
        }
    }
};

class ATM {
private:
    vector<Account> accounts;
    Account* currentAccount;

public:
    ATM() : currentAccount(nullptr) {
        // For demonstration purposes, let's create a few initial accounts
        accounts.push_back(Account(12345, 1234, 1000.0));
        accounts.push_back(PremiumAccount(54321, 4321, 15000.0));
    }

    void registerAccount(long long accNumber, int pin, double initialBalance) {
        // Check if the account number is already in use
        for (Account& acc : accounts) {
            if (acc.getAccountNumber() == accNumber) {
                cout << "Account number already in use. Please choose another.\n";
                return;
            }
        }

        // Create a new account and add it to the accounts vector
        if(initialBalance > 10000) accounts.push_back(PremiumAccount(accNumber, pin, initialBalance)); 
        else accounts.push_back(Account(accNumber, pin, initialBalance));
        cout << "Account registration successful!\n";
    }

    void login(long long accNumber, int pin) {
        if (currentAccount == nullptr) {
            for (Account& acc : accounts) {
                if (acc.getAccountNumber() == accNumber && acc.checkPin(pin)) {
                    currentAccount = &acc;
                    cout << "Login successful!\n";
                    return;
                }
            }
            cout << "Login failed. Please try again.\n";
        } else {
            cout << "You are already logged in. Please log out to use another account.\n";
        }
    }

    void logout() {
        currentAccount = nullptr;
        cout << "Logged out.\n";
    }

    void checkBalance() {
        if (currentAccount) {
            cout << "Balance: $" << currentAccount->getBalance() << endl;
        } else {
            cout << "Please log in first.\n";
        }
    }

    void deposit(double amount) {
        if (currentAccount) {
            currentAccount->deposit(amount);
            cout << "Deposit successful. New balance: $" << currentAccount->getBalance() << endl;
        } else {
            cout << "Please log in first.\n";
        }
    }

    void withdraw(double amount) {
        if (currentAccount) {
            currentAccount->withdraw(amount);
            cout << "Withdrawal successful. New balance: $" << currentAccount->getBalance() << endl;
        } else {
            cout << "Please log in first.\n";
        }
    }

    ~ATM() {
        if (currentAccount) {
            delete currentAccount;
        }
    }
};

int main() {
    ATM atm;
    int choice;
    bool running = true;

    while (running) {
        cout << "ATM Menu:\n";
        cout << "1. Register\n2. Login\n3. Logout\n4. Check Balance\n5. Deposit\n6. Withdraw\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                long long accNumber;
                int pin;
                double initialBalance;
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter PIN: ";
                cin >> pin;
                cout << "Enter initial balance: $";
                cin >> initialBalance;
                atm.registerAccount(accNumber, pin, initialBalance);
                break;

            case 2:
                long long loginAccNumber;
                int loginPin;
                cout << "Enter account number: ";
                cin >> loginAccNumber;
                cout << "Enter PIN: ";
                cin >> loginPin;
                atm.login(loginAccNumber, loginPin);
                break;

            case 3:
                atm.logout();
                break;

            case 4:
                atm.checkBalance();
                break;

            case 5:
                double depositAmount;
                cout << "Enter amount to deposit: $";
                cin >> depositAmount;
                atm.deposit(depositAmount);
                break;

            case 6:
                double withdrawAmount;
                cout << "Enter amount to withdraw: $";
                cin >> withdrawAmount;
                atm.withdraw(withdrawAmount);
                break;

            case 7:
                running = false;
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

/*
**Inheritance and Polymorphism -> compile-time, run-time, virtual(keyword)**
Account testAccount = new Account(); -> Possible: base class obj pointing to base class
PremiumAccount testAccount = new PremiumAccount(); -> Possible: derived class obj pointing to derived class
Account testAccount = new PremiumAccount(); -> Possible: base class obj pointing to derived class
PremiumAccount testAccount = new Account(); -> NotPossible: vice-versa not possible!

**Method Overloading(no. & type of parameters), Method Overriding(when derived class inherits properties and
functions from base class it overwrites the functions from base class)**

**Encapsulation**
Clubbing of data 
*/