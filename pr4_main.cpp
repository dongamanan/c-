#include"pr4.cpp"


#include <iostream>




using namespace std;

int main() {
    
    PersonalWallet* myAccounts[5]; 
    int totalCreated = 0;
    int userChoice;

    do {
        cout << "\n--- MY SIMPLE BANKING INTERFACE ---" << endl;
        cout << "1. Open Savings Account" << endl;
        cout << "2. Open Overdraft Account" << endl;
        cout << "3. Put Money (Deposit)" << endl;
        cout << "4. Take Money (Withdraw)" << endl;
        cout << "5. Show All My Accounts" << endl;
        cout << "6. Exit Program" << endl;
        cout << "Enter Choice: ";
        cin >> userChoice;

        if (userChoice == 1 || userChoice == 2) {
            if (totalCreated >= 5) {
                cout << "Array list full!" << endl;
                continue;
            }

            char inputId[30], inputName[40];
            double inputCash;

            cout << "Type Account ID: "; cin >> inputId;
            cout << "Type Owner Name: "; cin >> inputName;
            cout << "Type Initial Cash: "; cin >> inputCash;

            if (userChoice == 1) {
                myAccounts[totalCreated++] = new FixedSavings(inputId, inputName, inputCash);
            } else {
                double inputLimit;
                cout << "Type Overdraft Limit: "; cin >> inputLimit;
                myAccounts[totalCreated++] = new OverdraftPocket(inputId, inputName, inputCash, inputLimit);
            }
            cout << "Account registered successfully in memory!" << endl;
        }
        else if (userChoice == 3 || userChoice == 4) {
            if (totalCreated == 0) {
                cout << "Please create an account first!" << endl;
                continue;
            }

            int index;
            double amt;
            cout << "Enter account slot number (0 to " << totalCreated - 1 << "): "; 
            cin >> index;

            if (index >= 0 && index < totalCreated) {
                cout << "Enter money amount: "; 
                cin >> amt;
                
                if (userChoice == 3) {
                    myAccounts[index]->putMoney(amt);
                } else {
                    myAccounts[index]->takeMoney(amt); // रन-टाइम पॉलिमॉर्फिज्म काम करेगा
                }
            } else {
                cout << "Wrong slot number selected!" << endl;
            }
        }
        else if (userChoice == 5) {
            if (totalCreated == 0) {
                cout << "No accounts to display." << endl;
            } else {
                cout << "\n--- CURRENT ACCOUNT LIST ---" << endl;
                for (int i = 0; i < totalCreated; i++) {
                    cout << "Slot [" << i << "] -> ";
                    myAccounts[i]->printReceipt();
                }
            }
        }

    } while (userChoice != 6);

    // मैमोरी क्लीन करना (मेमोरी लीक रोकने के लिए)
    for (int i = 0; i < totalCreated; i++) {
        delete myAccounts[i];
    }

    cout << "\nProgram closed. Memory cleared." << endl;
    return 0;
}
