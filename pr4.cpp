#include <iostream>

using namespace std;





class PersonalWallet {
private:
    char idNum[30];
    char userName[40];
    double myCash;

public:
    PersonalWallet(const char* givenId, const char* givenName, double startMoney) {
       
        int i = 0;
        while (givenId[i] != '\0') {
            idNum[i] = givenId[i];
            i++;
        }
        idNum[i] = '\0';

        int j = 0;
        while (givenName[j] != '\0') {
            userName[j] = givenName[j];
            j++;
        }
        userName[j] = '\0';

        myCash = startMoney;
    }

 
    double getCurrentFunds() { 
        return myCash; 
    }

    void updateFunds(double newAmount) { 
        myCash = newAmount; 
    }

    void putMoney(double moneyIn) {
        if (moneyIn > 0) {
            myCash += moneyIn;
            cout << "-> Cash added: $" << moneyIn << endl;
        }
    }

   
    virtual void takeMoney(double moneyOut) {
        if (myCash >= moneyOut) {
            myCash -= moneyOut;
            cout << "-> Cash withdrawn: $" << moneyOut << endl;
        } else {
            cout << "-> Sorry, not enough cash in account!" << endl;
        }
    }

    virtual void printReceipt() {
        cout << "Acc: " << idNum << " | Name: " << userName << " | Total: $" << myCash;
    }

    virtual ~PersonalWallet() {}
};



class FixedSavings : public PersonalWallet {
public:
    FixedSavings(const char* id, const char* name, double cash) 
        : PersonalWallet(id, name, cash) {}

    void printReceipt() override {
        PersonalWallet::printReceipt();
        cout << " [Account Type: Savings]" << endl;
    }
};




class OverdraftPocket : public PersonalWallet {
private:
    double safetyLimit;

public:
    OverdraftPocket(const char* id, const char* name, double cash, double limit) 
        : PersonalWallet(id, name, cash), safetyLimit(limit) {}

    // फंक्शन ओवरराइडिंग (पॉलिमॉर्फिज्म)
    void takeMoney(double moneyOut) override {
        double totalAvailable = getCurrentFunds() + safetyLimit;

        if (totalAvailable >= moneyOut) {
            updateFunds(getCurrentFunds() - moneyOut);
            cout << "-> Withdrawn: $" << moneyOut << " (Overdraft limit was used)" << endl;
        } else {
            cout << "-> Error: Exceeded the allowed overdraft safety limit!" << endl;
        }
    }

    void printReceipt() override {
        PersonalWallet::printReceipt();
        cout << " [Account Type: Overdraft Pocket | Extra Limit: $" << safetyLimit << "]" << endl;
    }
};

