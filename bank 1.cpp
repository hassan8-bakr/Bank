#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string filename = "the Clients.txt";
enum options { AddClients = 1,deleteClients = 2,UpdateClients = 3,FindClients = 4,ShowClients = 5, tranestion = 6,Exit = 7};
enum transation { eDeposit =1,eWithDraw =2,eTotalbalance =3,eBacktomainmenue = 4 };
void finalprogram();
void BackToMainList();
void Finaltransation();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkClient = false;
};
vector<string> split(string line,string delim ="//")
{
    vector<string> vstring;
    short pos;
    string sword;
    while ((pos = line.find(delim)) != std::string::npos)
    {
        sword = line.substr(0, pos);
        if (sword != "")
        {
            vstring.push_back(sword);
        }
        line.erase(0,pos + delim.length());
    }
    if(line != "")
    {
        vstring.push_back(line);
    }
    return vstring;
}


// (5)show Clients
void Show_5()
{
    cout << "____________________________________________________\n" << endl;
    cout << "\t\t Show Clients \t" << endl;
    cout << "____________________________________________________" << endl;
}
sClient ConvertLineToData(string Line)
{
    vector<string> vClients;
    sClient c1;
    vClients = split(Line);
    c1.AccountNumber = vClients[0];
    c1.PinCode = vClients[1];
    c1.Name = vClients[2];
    c1.Phone = vClients[3];
    c1.AccountBalance = stod(vClients[4]);
    return c1;

}
vector<sClient> LoadDataFiletovector(string filename)
{
    vector<sClient> vClients;
    fstream myfile;
    myfile.open(filename,ios::in);
    if (myfile.is_open())
    {
        string line;
        sClient c1;
        while (getline(myfile,line))
        {
            c1 = ConvertLineToData(line);
            vClients.push_back(c1);
        }
    }
    return vClients;
}
void PrintClientsDetails(sClient c1)
{
    cout << "| " << setw(15) << left << c1.AccountNumber;
    cout << "| " << setw(10) << left << c1.PinCode;
    cout << "| " << setw(40) << left << c1.Name;
    cout << "| " << setw(12) << left << c1.Phone;
    cout << "| " << setw(12) << left << c1.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")  Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientsDetails(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}


// (1)add clients
void Show_1()
{
    cout << "____________________________________________________" << endl;
    cout << "\t\t Add Client \t" << endl;
    cout << "____________________________________________________" << endl;
}
bool checkClient(string c1, string filename)
{
    vector <sClient> vClients;
    fstream myfile;
    myfile.open(filename,ios::in);
    if (myfile.is_open())
    {
        string line;
        sClient c2;
        while (getline(myfile,line))
        {
            c2 = ConvertLineToData(line);
            if (c2.AccountNumber == c1)
            {
                myfile.close();
                return true;
            }
            vClients.push_back(c2);
        }
        myfile.close();
    }
    return false;
}
sClient readclient()
{
    sClient customer1;
    vector <sClient> vClients = LoadDataFiletovector(filename);
    cout << "Enter Account : \n\n";
    cout << "enter your AccountNumber ?\n" << endl;
    getline(cin >> ws, customer1.AccountNumber);
    while (checkClient(customer1.AccountNumber,filename))
    {
        cout << " the account number " << customer1.AccountNumber << " is found please enter your account number again" << endl;
        getline(cin >> ws, customer1.AccountNumber);
    }
    cout << "enter your pincode ?\n" << endl;
    getline(cin, customer1.PinCode);
    cout << "enter your name ?\n" << endl;
    getline(cin, customer1.Name);
    cout << "enter your phone ?\n" << endl;
    getline(cin, customer1.Phone);
    cout << "enter your Accountbalance ?\n" << endl;
    cin >> customer1.AccountBalance;
    return customer1;
}
string ConvertClientToLine(sClient c1,string delim)
{
    string s1;
    s1 += c1.AccountNumber + delim;
    s1 += c1.PinCode + delim;
    s1 += c1.Name + delim;
    s1 += c1.Phone + delim;
    s1 += to_string(c1.AccountBalance);
    return s1;
}
void ConvertlineToFile(string filename,string line)
{
    fstream myfile;
    myfile.open(filename,ios::out | ios::app);
    if(myfile.is_open())
    {
        myfile << line << endl;
    }
    myfile.close();
}
void AddNewClients()
{
    sClient c1;
    char add = 'n';
    do
    {
        c1 = readclient();
        ConvertlineToFile(filename, ConvertClientToLine(c1, "//"));
        cout << "the client add sucsesfully , do you want add more clients ? (y/n)" << endl;
        cin >> add;
    } while (tolower(add) == 'y');
} 
//run this


// (4)find Clients
string ReadAccountNumber()
{
    string s1;
    cout << "enter account number ? " << endl;
    cin >> s1;
    cout << endl;
    return s1;
}
void Show_4()
{
    cout << "____________________________________________________" << endl;
    cout << "\t\t Find Clients \t" << endl;
    cout << "____________________________________________________" << endl;
}
bool SearchAccountNumber(string AccountNumber,sClient &search,vector <sClient> vClients)
{
    for (sClient c1 : vClients)
    {
        if (c1.AccountNumber == AccountNumber)
        {
            search = c1;
            return true;
        }
    }     
    return false;
}
void ShowClient(sClient search)
{
    cout << " The Account : " << endl;
    cout << "---------------------------------------------------\n";
    cout << "Account Number :" << search.AccountNumber << endl;
    cout << endl;
    cout << "Pin Code :" << search.PinCode << endl;
    cout << endl;
    cout << "Name :" << search.Name << endl;
    cout << endl;
    cout << "Phone :" << search.Phone << endl;
    cout << endl;
    cout << "Account Balance :" << search.AccountBalance << endl;
    cout << "---------------------------------------------------\n";

}


// (2) delete Clients
void Show_2()
{
    cout << "____________________________________________________" << endl;
    cout << "\t\t Delete Clients \t" << endl;
    cout << "____________________________________________________" << endl;
}
bool MarkClient(string AccountNumber,vector <sClient> &vClients)
{
    for (sClient &c1 : vClients)
    {
        if (c1.AccountNumber == AccountNumber)
        {
            c1.MarkClient = true;
            return true;
        }
    }
    return false;
}
vector<sClient> refreshfile(string FileName, vector <sClient> vClients)
{
    string s1;
    fstream myfile;
    myfile.open(FileName,ios::out);
    if (myfile.is_open())
    {
        for (sClient c1 : vClients)
        {
            if (c1.MarkClient == false)
            {
                s1 = ConvertClientToLine(c1,"//");
                myfile << s1 << endl;
            }
        }
    }
    myfile.close();
    return vClients;
}
bool deleteClientInFile(string AccountNumber, vector <sClient> vClients)
{
    sClient c1;
    char c = 'n';
    if (SearchAccountNumber(AccountNumber,c1, vClients))
    {
        ShowClient(c1);
        cout << "Do You Want Delete Your Client (y / n) ?" << endl;
        cin >> c;
        while (tolower(c) == 'y')
        {   
            MarkClient(AccountNumber, vClients);
            refreshfile(filename, vClients);
            vClients = LoadDataFiletovector(filename);
            cout << "The Client Was Deleted " << endl;
            cout << "Do You Want Delete Your Client (y / n) ?" << endl;
            cin >> c;
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}


//(3) Update Clients
void Show_3()
{
    cout << "____________________________________________________" << endl;
    cout << "\t\t Update Clients \t" << endl;
    cout << "____________________________________________________" << endl;
}
sClient UpdateClient(string accountnumber)
{
    sClient c1;
    c1.AccountNumber = accountnumber;
    cout << "enter your pincode ?" << endl;
    getline(cin >> ws, c1.PinCode);
    cout << "enter your name ?" << endl;
    getline(cin, c1.Name);
    cout << "enter your phone ?" << endl;
    getline(cin, c1.Phone);
    cout << "enter your Accountbalance ?" << endl;
    cin >> c1.AccountBalance;
    return c1;
}
bool updateclientinfile(string accountnumber, vector <sClient>& vClients)
{
    string s1;
    sClient c1;
    char c = 'n';
    if (SearchAccountNumber(accountnumber, c1, vClients))
    {
        ShowClient(c1);
        cout << "do you want update to client ?";
        cin >> c;
        if (tolower(c) == 'y')
        {
            for (sClient& c2 : vClients)
            {
                if (c2.AccountNumber == accountnumber)
                {
                    c2 = UpdateClient(accountnumber);
                    break;
                }
            }
            refreshfile(filename, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << accountnumber << ") is Not Found!";
        return false;
    }
}


//transetion
short choosenumberintransetion()
{
    short num = 0;
    cout << "Enter Your Number ?" << endl;
    cin >> num;
    return num;
}
bool DepositBalanceByAccountNumber(string accountnumber,double d1, vector <sClient>& vClient)
{     
    char ch1 = 'n';
    cout << "are you sure ? (y/n)" << endl;
    cin >> ch1;
    if (ch1 == 'y' || ch1 == 'Y')
    {
         for (sClient& c2 : vClient)
         {
             if (c2.AccountNumber == accountnumber)
             {
                c2.AccountBalance += d1;  
                refreshfile(filename, vClient);
                cout <<"\n\n Deposit Successfully."<< ", Account Balance : " << c2.AccountBalance << endl;   
                return true;
                break;
             }
         }
      return false;
    }
}
bool Deposit()
{
    vector <sClient> vClient = LoadDataFiletovector(filename);
    sClient c1;
    string accountnumber;
    cout << "Enter your account Number ?" << endl;
    cin >> accountnumber;
    if (SearchAccountNumber(accountnumber,c1,vClient))
    {
        ShowClient(c1);
        double d1 = 0;
        cout << "enter your deposit ?" << endl;
        cin >> d1;
        
        DepositBalanceByAccountNumber(accountnumber,d1,vClient);
    }
    else
    {
        cout << "Account Number not found \n";
        system("pause>0");
        finalprogram();
        return false;

    }
    
}
bool WithDraw()
{
    vector <sClient> vClient = LoadDataFiletovector(filename);
    sClient c1;
    string accountnumber;
    cout << "Enter your account Number ?" << endl;
    cin >> accountnumber;
    if (SearchAccountNumber(accountnumber, c1, vClient))
    {
        ShowClient(c1);
        double d1 = 0;
        cout << "enter your WithDraw ?" << endl;
        cin >> d1;
        while (d1 > c1.AccountBalance)
        {
            cout << "the balance " << d1 << " bigger than account balance please enter correct balance :\n";
            cin >> d1;
        }
        DepositBalanceByAccountNumber(accountnumber, d1 * -1, vClient);
    }
    else
    {
        cout << "Account Number not found \n";
        system("pause>0");
            finalprogram();
        return false;
    }
}
void Totalbalance()
{
    vector <sClient> vClient = LoadDataFiletovector(filename);
    double d1 = 0;
    for (sClient c1: vClient)
    {
       d1 += c1.AccountBalance;
    }
    PrintAllClientsData(vClient);
    cout << "total balance : " << d1 << endl;
}
void BackTotransetionList()
{
    cout << "press any key to back to main menue... " << endl;
    system("pause>0");
    Finaltransation();
}
void showtransationoption(transation option)
{
    system("cls");
    switch (option)
    {
    case transation::eDeposit:
        {
        system("cls");
          Deposit();
          BackTotransetionList();
          break;
        }
        case transation::eWithDraw:
            system("cls");
            WithDraw();
            BackTotransetionList();
            break;
        case transation::eTotalbalance:
            system("cls");
            Totalbalance();
            BackTotransetionList();
            break;
        case transation::eBacktomainmenue:
            system("cls");
            finalprogram();
            break;
    }
}
void Finaltransation()
{
    system("cls");
    cout << "================================\n";
    cout << "Transactions Menue Screen \n";
    cout << "==============================\n" << endl;
    cout << " [1] Deposit \n";
    cout << " [2] WithDraw \n";
    cout << " [3] Total Balances \n";
    cout << " [4] Main Menue\n";
    cout << "==============================\n" << endl;
    showtransationoption((transation)choosenumberintransetion());
}


void Options()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Add New Client.\n";
    cout << "\t[2] Delete Client.\n";
    cout << "\t[3] Update Client Info.\n";
    cout << "\t[4] Find Client.\n";
    cout << "\t[5] Show Client List.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
}
void BackToMainList()
{
    cout << "press any key to back to main menue... " << endl;
    system("pause>0");
    finalprogram();
}
void ProgramEnd()
{
    cout << "_____________________________________________" << endl;
    cout << "\t\t Program Ends \t" << endl;
    cout << "_____________________________________________" << endl;
}
short choosenumber()
{
    short num = 0;
    cout << "Enter Your Number ?" << endl;
    cin >> num;
    return num;
}
void showoption(options showoption)
{
    vector <sClient> vClients = LoadDataFiletovector(filename);
    sClient c1;
    switch (showoption)
    {
        case options::AddClients:
        {
            system("cls");
            Show_1();
            AddNewClients();
            BackToMainList();
            break;
        }
        case options::deleteClients:
            system("cls");
            Show_2();
            deleteClientInFile(ReadAccountNumber(), vClients);
            BackToMainList();
            break;
        
        case options::UpdateClients:
        
            system("cls");
            Show_3();
            updateclientinfile(ReadAccountNumber(), vClients);
            BackToMainList();
            break;
        
        case options::FindClients:
        
            system("cls");
            Show_4();
            SearchAccountNumber(ReadAccountNumber(), c1, vClients);
            ShowClient(c1);
            BackToMainList();
            break;
        
        case options::ShowClients:
        
            system("cls");
            Show_5();
            PrintAllClientsData(vClients);
            BackToMainList();
            break;

        case options::tranestion:
            system("cls");
            Finaltransation();
            break;
        case options::Exit:
        
            system("cls");
            ProgramEnd();
            break;
        
    }
       
    
}
void finalprogram()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Add New Client.\n";
    cout << "\t[2] Delete Client.\n";
    cout << "\t[3] Update Client Info.\n";
    cout << "\t[4] Find Client.\n";
    cout << "\t[5] Show Client List.\n";
    cout << "\t[6] Transetion.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    showoption((options)choosenumber());
}

int main()
{
   
    
    finalprogram();
}


