#include <iostream>
#include<iomanip>
#include <string>
#include<vector>
#include<fstream>
using namespace std;


string fileName = "myfile.txt";
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};
void GoBackToMainMenue();
void PrintClientRecord(sClient Client) {
    cout << "\n\nThe following is the extracted client record:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
vector<string> splitString(string s, string delim = " ") {
    vector<string>vstring;
    string word;
    int pos;
    while ((pos = s.find(delim)) != std::string::npos) {
        word = s.substr(0, pos);
        if (word != "") {
            vstring.push_back(word);
        }
        s.erase(0, pos + delim.length());
    }
    if (s != "") {
        vstring.push_back(s);
    }
    return vstring;
}
string convertRecordtoLine(sClient Client, string Seperator = "#//#") {

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;


}
sClient convertLineToRecord(string line, string Seperator = "#//#") {
    vector<string>vClientData = splitString(line, "#//#");
    sClient Client;
    if (vClientData.size() >= 5) {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }
    else {
        cout << "Error: Incomplete client record in file.\n";
    }
    return Client;
}
void addRecordToFile(string fileName, string record) {
    fstream file;
    file.open(fileName, ios::out | ios::app);
    if (file.is_open()) {
        file << record << endl;
    }
    file.close();
}
vector<sClient> loadClientsFromFile(string fileName) {
    vector<sClient>vClient;
    fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {
        string line;
        sClient client;
        while (getline(file, line)) {
            client = convertLineToRecord(line);
            vClient.push_back(client);
        }
        file.close();
    }
    return vClient;
}
bool checkclientsinfile(vector<sClient>v, sClient newClient) {
    for (sClient n : v) {
        if (n.AccountNumber == newClient.AccountNumber)
            return true;
    }
    return false;
}
void clinetInformation(sClient s) {
    cout << "\nthe following are client details : \n";
    cout << "----------------------------------------\n";
    cout << "Account number : " << s.AccountNumber << endl;
    cout << "Pin Code       : " << s.PinCode << endl;
    cout << "Name           :" << s.Name << endl;
    cout << "phone          :" << s.Phone << endl;
    cout << "Account balance:" << s.AccountBalance << endl;
    cout << "----------------------------------------\n";
}
void printClient(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << to_string(Client.AccountBalance);
}
void ShowClients(vector<sClient> vClients) {

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________________________\n" << endl;
    for (sClient client : vClients) {
        printClient(client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________________________\n" << endl;
}
bool findClient(string accountNumber, string fileName) {
    vector<sClient>vClient = loadClientsFromFile(fileName);
    for (sClient& n : vClient) {
        if (n.AccountNumber == accountNumber) {
            clinetInformation(n);

            return true;
        }
    }

    cout << "the client is not exits \n";
    return false;
}
string readAccountName() {
    string client;
    cout << "inter your client number : ";
    getline(cin >> ws, client);
    return client;
}
bool deleteClientFromFile(string fileName, string AccountNumber) {
    vector<sClient> vClient = loadClientsFromFile(fileName);
    vector<sClient>::iterator iter;

    bool clientDeleted = false;
    char AreYouSure = 'y';

    for (iter = vClient.begin(); iter != vClient.end(); ++iter) {
        if (iter->AccountNumber == AccountNumber) {
            clinetInformation(*iter);
            cout << "\nare you sure to delete this account (Y/N) ? ";
            cin >> AreYouSure;
            if (AreYouSure == 'y' || AreYouSure == 'Y') {
                vClient.erase(iter);
            }
            clientDeleted = true;
            break;
        }
    }

    if (clientDeleted) {


        ofstream file(fileName);
        if (file.is_open()) {
            for (const sClient& client : vClient) {
                file << convertRecordtoLine(client) << endl;
            }
            file.close();
        }
        cout << "the account deleted successfully ";
        return true;

    }
    cout << "this account does not exits :(";
    return false;
}
void confireTheDeletion() {
    char check;
    cout << "do you want to delete A Client (y/n) : ";
    cin >> check;
    if (toupper(check) == 'Y') {
        string accountNumber;
        cout << "inter the account number  : ";
        cin >> accountNumber;
        if (deleteClientFromFile(fileName, accountNumber)) {
            cout << "The client deleted successfully.\n";
        }
        else {
            cout << "Client not found.\n";
        }

    }
}
sClient updateClient(sClient& c) {
    cout << "update your Client : \n";
    cout << "Enter PinCode? ";
    getline(cin >> ws, c.PinCode);

    cout << "Enter Name? ";
    getline(cin, c.Name);

    cout << "Enter Phone? ";
    getline(cin, c.Phone);

    cout << "Enter AccountBalance? ";
    cin >> c.AccountBalance;

    return c;



}
bool updateclientinfile(string fileName, string clientnumber) {

    vector<sClient> vClient = loadClientsFromFile(fileName);
    vector<sClient>::iterator iter;
    char AreYouSure = 'n';
    bool clientupdated = false;

    for (iter = vClient.begin(); iter != vClient.end(); ++iter) {
        if (iter->AccountNumber == clientnumber) {
            clinetInformation(*iter);
            cout << "\nare you sure to update this account (Y/N) ? ";
            cin >> AreYouSure;
            if (AreYouSure == 'y' || AreYouSure == 'Y') {
                *iter = updateClient(*iter);
            }

            clientupdated = true;
            break;
        }
    }

    if (clientupdated) {

        ofstream file(fileName);
        if (file.is_open()) {
            for (const sClient& client : vClient) {
                file << convertRecordtoLine(client) << endl;
            }
            file.close();
        }
        return true;

    }

    return false;
}
void confireTheupdate() {
    char check;
    cout << "do you want to update A Client (y/n) : ";
    cin >> check;
    if (toupper(check) == 'Y') {
        string clientnumber = readAccountName();
        if (updateclientinfile(fileName, clientnumber)) {
            cout << "The client updaated successfully.\n";
        }
        else {
            cout << "Client not found.\n";
        }

    }
}
sClient readClient() {
    sClient newClient;
    char answer = 'y';
    vector<sClient>vec = loadClientsFromFile(fileName);
    while (answer == 'y' || answer == 'Y') {
        cout << "Enter Account Number? ";
        getline(cin >> ws, newClient.AccountNumber);
        while (checkclientsinfile(vec, newClient)) {
            cout << "the client already exist :) \n";
            cout << "inter your client Agian : \n";
            getline(cin, newClient.AccountNumber);
        }

        cout << "Enter Name? ";
        getline(cin, newClient.Name);

        cout << "Enter PinCode? ";
        getline(cin, newClient.PinCode);



        cout << "Enter Phone? ";
        getline(cin, newClient.Phone);

        cout << "Enter AccountBalance? ";
        cin >> newClient.AccountBalance;


        string newRecord = convertRecordtoLine(newClient);
        addRecordToFile(fileName, newRecord);
        cout << "\n\n Client add Successfully, Do you want to add again (Y/N) ?";
        cin >> answer;
    }





    return newClient;


}
void addClients() {

    system("cls");
    cout << "adding new client : \n";
    sClient newClient = readClient();
}
void printthefront() {
    cout << "\n==================================================\n";
    cout << "               Main Menu screeen                 \n";
    cout << "==================================================\n";
    cout << "       [1] Show Client List. \n";
    cout << "       [2] Add New Client.  \n";
    cout << "       [3] Delete Client. \n";
    cout << "       [4] Update Client Info. \n";
    cout << "       [5] Find Client.\n";
    cout << "       [6] Transaction. \n";
    cout << "       [7] Exit.        \n";
    cout << "==================================================\n";
}
short readtheOption() {
    short op;
    cout << "choose what want to do ? [1 to 6]?";
    cin >> ws >> op;
    return op;
}
void deleteClient() {
    string accountNumber;
    cout << "inter account number to delete ? ";
    cin >> accountNumber;
    deleteClientFromFile(fileName, accountNumber);

}
void printTransactionMenu() {
    cout << "============================================= = \n";
    cout << "                Transaction Menu                \n";
    cout << "================================================\n";
    cout << "    [1] Deposit. \n";
    cout << "    [2] Withdraw.\n";
    cout << "    [3] Total Balance. \n";
    cout << "    [4] Main Menu \n";
    cout << "================================================\n";
    cout << "Choose What do you want to do [1 to 4] ? ";
}
void Deposite() {
    system("cls");
    cout << "-----------------------------\n";
    cout << "        Deposit Screen       \n";
    cout << "-----------------------------\n\n";

    vector<sClient> vClient = loadClientsFromFile(fileName);
    vector<sClient>::iterator iter;
    double deposit;
    bool clientFound = false;


    while (!clientFound) {
        cout << "Please enter Account Number: ";
        string AccountNumber;
        cin >> AccountNumber;


        for (iter = vClient.begin(); iter != vClient.end(); ++iter) {
            if (iter->AccountNumber == AccountNumber) {
                clinetInformation(*iter);

                cout << "\nPlease enter Deposit amount: ";
                cin >> deposit;


                iter->AccountBalance += deposit;


                ofstream file(fileName);
                if (file.is_open()) {
                    for (const sClient& client : vClient) {
                        file << convertRecordtoLine(client) << endl;
                    }
                    file.close();
                }

                cout << "Deposit successful! New Balance: " << iter->AccountBalance << endl;

                clientFound = true;
                break;
            }
        }

        if (!clientFound) {
            cout << "Client not found. Please enter a valid Account Number.\n";
        }
    }
}
void Withdraw() {
    system("cls");
    cout << "-----------------------------\n";
    cout << "        Withdraw Screen       \n";
    cout << "-----------------------------\n\n";
    vector<sClient> vClient = loadClientsFromFile(fileName);
    vector<sClient>::iterator iter;
    double Withdraw;
    bool clientFound = false;
    while (!clientFound) {
        cout << "Please enter Account Number: ";
        string AccountNumber;
        cin >> AccountNumber;


        for (iter = vClient.begin(); iter != vClient.end(); ++iter) {
            if (iter->AccountNumber == AccountNumber) {
                clinetInformation(*iter);

                cout << "\nPlease enter Withdraw amount: ";
                cin >> Withdraw;


                iter->AccountBalance -= Withdraw;


                ofstream file(fileName);
                if (file.is_open()) {
                    for (const sClient& client : vClient) {
                        file << convertRecordtoLine(client) << endl;
                    }
                    file.close();
                }

                cout << "Withdraw successful! New Balance: " << iter->AccountBalance << endl;

                clientFound = true;
                break;
            }
        }

        if (!clientFound) {
            cout << "Client not found. Please enter a valid Account Number.\n";
        }
    }

}
void transactionMenu();
void TotalBalance() {
    system("cls");
    cout << "-----------------------------\n";
    cout << "        Total Balance        \n";
    cout << "-----------------------------\n\n";
    vector<sClient> vClient = loadClientsFromFile(fileName);
    vector<sClient>::iterator iter;
    double totalbalance = 0;
    for (iter = vClient.begin(); iter != vClient.end(); iter++) {
        totalbalance += iter->AccountBalance;
    }
    cout << "the Total Balance is: " << totalbalance << endl;
    cout << "\n\nPress any key to go back to Transaction Menue...";
    system("pause>0");
    system("cls");
    transactionMenu();

}
void playtheApp();
void transactionMenu() {
    printTransactionMenu();
    short choose;
    cin >> choose;
    switch (choose)
    {
    case 1:
        Deposite();
        GoBackToMainMenue();
        break;
    case 2:
        Withdraw();
        GoBackToMainMenue();
        break;
    case 3:
        TotalBalance();
    case 4:
        system("cls");
        playtheApp();
        break;
    default:
        break;
    }

}
void playtheApp() {
    vector<sClient> CLientsOfTheFile = loadClientsFromFile(fileName);
    printthefront();
    short option = readtheOption();

    if (option == 1) {
        system("cls");
        ShowClients(CLientsOfTheFile);
        GoBackToMainMenue();

    }
    else if (option == 2) {
        system("cls");
        addClients();
        GoBackToMainMenue();
    }
    else if (option == 3) {
        system("cls");
        deleteClient();
        GoBackToMainMenue();
    }
    else if (option == 4) {
        system("cls");
        string accountNumber;
        cout << "inter account number to delete ? ";
        cin >> accountNumber;
        updateclientinfile(fileName, accountNumber);
        GoBackToMainMenue();
    }
    else if (option == 5) {
        system("cls");
        string accountNumber;
        cout << "inter account number to find ? ";
        cin >> accountNumber;
        findClient(accountNumber, fileName);
        GoBackToMainMenue();
    }
    else if (option == 6) {
        system("cls");
        transactionMenu();
    }
    else if (option == 7) {
        system("cls");
        cout << "--------------------------------------\n";
        cout << "            System Ened :)            \n";
        cout << "--------------------------------------\n";
    }

}
void GoBackToMainMenue() {

    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    system("cls");
    playtheApp();
}


int main()
{
    playtheApp();

    return 0;
}

