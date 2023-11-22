#include<iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <bitset>
using namespace std;

struct stClientData
{
	string Name;
	string Phone;
	string AccountNumber;
	string PinCode;
	double AccountBalance = 0;
};
const string ClientsFileName = "ClientsData.txt";
const string UsersFileName = "Users.txt";
const string Separator = "#//#";
string CurrentUserName;
void MainScreen();
void LoginScreen();
void UsersScreen();
int ReadNumberInRange(string Message, int From, int To)
{
	int Number = 0;
	do
	{
		cout << Message << endl;
		cin >> Number;
	} while (Number < From || Number > To);
	return Number;
}
void ClearScreen()
{
	system("CLS");
}
// START Add CLIENTS
string CreateClientDataInLine(stClientData ClientData, string Separator = "#//#")
{
	string ClientRecord = "";
	ClientRecord = ClientData.AccountNumber + Separator +
		ClientData.PinCode + Separator +
		ClientData.Name + Separator +
		ClientData.Phone + Separator +
		to_string(ClientData.AccountBalance);
	return ClientRecord;
}
void SaveClientDataInFile(string ClientData, string FileName)
{
	fstream myfile;
	myfile.open(FileName, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << ClientData << endl;
		myfile.close();
	}
}
vector <string> SplitString(string S1, string delim)
{
	vector <string> vTokens;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vTokens.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		vTokens.push_back(S1);
	}
	return vTokens;
}
bool CheckClientIfFound(string& AcountNumber)
{
	vector <string> vClientsDataInLine;
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	if (myfile.is_open())
	{
		string Line;
		while (getline(myfile, Line))
		{
			vClientsDataInLine.push_back(Line);
		}
		myfile.close();
	}
	for (string& L : vClientsDataInLine)
	{
		vector <string> vClientDataInLine = SplitString(L, Separator);
		if (vClientDataInLine[0] == AcountNumber)
		{
			return true;
		}
	}
	return false;
}
void AddNewClient()
{
	stClientData ClientData;
	cout << "\n Enter account number ? ";
	getline(cin >> ws, ClientData.AccountNumber);

	while (CheckClientIfFound(ClientData.AccountNumber))
	{
		cout << "Client with [" << ClientData.AccountNumber << "] Already exists, Enter anthor Acoount Number ? ";
		getline(cin >> ws, ClientData.AccountNumber);
	}
	cout << "\n Enter pin code ? ";
	getline(cin, ClientData.PinCode);
	cout << "\n Enter  name? ";
	getline(cin, ClientData.Name);
	cout << "\n Enter phone ? ";
	getline(cin, ClientData.Phone);
	cout << "\n Enter account balance ? ";
	cin >> ClientData.AccountBalance;

	// Save new client data to file
	SaveClientDataInFile(CreateClientDataInLine(ClientData), ClientsFileName);
}
void AddClients()
{
	char NewClient = 'Y';
	do
	{
		system("cls");
		cout << "-----------------------------------------\n";
		cout << setw(30) << "Add new clients Screen:\n";
		cout << "-----------------------------------------\n";
		cout << "\nAdding new client:\n";
		AddNewClient();
		cout << "\nClient Added Successfully, Do you want to add new client? Enter Y/N ==> ";
		cin >> NewClient;
	} while (toupper(NewClient) == 'Y');
}
// START SHOW CLIENTS
short HowManyClientsAdded()
{
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	short CountClients = 0;
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			if (OneLine != "")
			{
				CountClients++;
			}
		}
		myfile.close();
	}
	return CountClients;
}
void PrintClientsHeader()
{
	cout << "\n" << setw(50) << "Client List (" << HowManyClientsAdded() << ") Clients(s)" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(20) << "Account Number"
		<< "| " << left << setw(10) << "Pin Code"
		<< "| " << left << setw(30) << "Client Name"
		<< "| " << left << setw(15) << "Phone"
		<< "| " << left << setw(15) << "Balance" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
}
void PrintClientInfo(vector <string>& ClientData)
{
	cout << "| " << left << setw(20) << ClientData[0]
		<< "| " << left << setw(10) << ClientData[1]
		<< "| " << left << setw(30) << ClientData[2]
		<< "| " << left << setw(15) << ClientData[3]
		<< "| " << left << setw(15) << ClientData[4] << endl;
}
void PrintClientsInfo()
{
	PrintClientsHeader();
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			if (OneLine != "")
			{
				vector <string> ClearSeparatorInClientData = SplitString(OneLine, "#//#");
				PrintClientInfo(ClearSeparatorInClientData);
			}
			cout << "\n";
		}
		cout << "\n______________________________________________________________________________________________________________\n";
		cout << "\n\n";
		myfile.close();
	}
}
// START DELETE CLIENTS 
void PrintClientInfoInUserScreen(vector <string>& ClientData)
{
	cout << "\nThe Following are the client details:\n";
	cout << "------------------------------------------\n";
	cout << "Account Number  : " << ClientData[0] << endl;
	cout << "Pin code        : " << ClientData[1] << endl;
	cout << "Name            : " << ClientData[2] << endl;
	cout << "Phone           : " << ClientData[3] << endl;
	cout << "Account Balance : " << ClientData[4] << endl;
	cout << "------------------------------------------\n";
}
void SaveNewDataAfterDeleteToFile(vector <string>& vClientsData)
{
	fstream myfile;
	myfile.open(ClientsFileName, ios::out);
	if (myfile.is_open())
	{
		for (string& Line : vClientsData)
		{
			if (Line != "")
			{
				myfile << Line << endl;
			}
		}
	}
	myfile.close();
}
void DeleteClient(vector <string>& vClientsData, string AccountNumber)
{
	char DeleteClient = 'y';
	cout << "Do you want to delete this client ? ";
	cin >> DeleteClient;
	if ('Y' == toupper(DeleteClient))
	{
		for (string& OneLine : vClientsData)
		{
			vector <string> vClientDataLine = SplitString(OneLine, "#//#");
			if (vClientDataLine[0] == AccountNumber)
			{
				OneLine = "";
				cout << "\nClient Deleted successfully.\n\n";
				SaveNewDataAfterDeleteToFile(vClientsData);
				break;
			}
		}
	}
}
void ShowClientInfoInClientScreen(vector <string>& vClientData, string& AccountNumber)
{
	for (string& Line : vClientData)
	{
		vector <string> vClientDataLine = SplitString(Line, Separator);
		if (vClientDataLine[0] == AccountNumber)
		{
			PrintClientInfoInUserScreen(vClientDataLine);
			break;
		}
	}
}
void DeleteClients(vector <string>& vClientData)
{
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Delete client Screen:\n";
	cout << "-----------------------------------------\n";
	string AccountNumber = "";
	cout << "\nPlease enter Account Number ? ";
	cin >> AccountNumber;
	while (!CheckClientIfFound(AccountNumber))
	{
		cout << "Client with Account Number [" << AccountNumber << "] is not found, Enter anthor Acoount Number ? ";
		getline(cin >> ws, AccountNumber);
	}
	ShowClientInfoInClientScreen(vClientData, AccountNumber);
	DeleteClient(vClientData, AccountNumber);
}
// START UPDATE CLIENT'S INFO
void UpdateClient(vector <string>& vClientDataLine)
{
	cout << "Enter Pin ? ";
	getline(cin >> ws, vClientDataLine[1]);
	cout << "Enter Name ? ";
	getline(cin, vClientDataLine[2]);
	cout << "Enter Phone ? ";
	getline(cin, vClientDataLine[3]);
	cout << "Enter Account Balance ? ";
	cin >> vClientDataLine[4];
}
string JoinString(vector <string>& vClientDataLine, string Delim)
{
	string FullName = "";
	for (string& Line : vClientDataLine)
	{
		if (Line != "")
		{
			FullName = FullName + Line + Delim;
		}
	}
	return FullName.substr(0, FullName.length() - Delim.length());
}
void UpdateClient(vector <string>& vClientsData, string AccountNumber)
{
	char DeleteClient = 'y';
	cout << "Do you want to update this client ? ";
	cin >> DeleteClient;
	if ('Y' == toupper(DeleteClient))
	{
		for (string& OneLine : vClientsData)
		{
			vector <string> vClientDataLine = SplitString(OneLine, "#//#");
			if (vClientDataLine[0] == AccountNumber)
			{
				UpdateClient(vClientDataLine);
				OneLine = JoinString(vClientDataLine, "#//#");
				cout << "\nClient Updated successfully.\n\n";
				SaveNewDataAfterDeleteToFile(vClientsData);
				break;
			}
		}
	}
}
void UpdateClients(vector <string>& vClientData)
{
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Update client Info Screen:\n";
	cout << "-----------------------------------------\n";
	string AccountNumber = "";
	cout << "\nPlease enter Account Number ? ";
	cin >> AccountNumber;
	while (!CheckClientIfFound(AccountNumber))
	{
		cout << "Client with Account Number [" << AccountNumber << "] is not found, Enter anthor Acoount Number ? ";
		getline(cin >> ws, AccountNumber);
	}
	ShowClientInfoInClientScreen(vClientData, AccountNumber);
	UpdateClient(vClientData, AccountNumber);
}
// START FIND CLIENTS
void FindClients(vector <string>& vClientData)
{
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Find Client Info Screen:\n";
	cout << "-----------------------------------------\n";
	string AccountNumber = "";
	cout << "\nPlease enter Account Number ? ";
	cin >> AccountNumber;
	while (!CheckClientIfFound(AccountNumber))
	{
		cout << "Client with Account Number [" << AccountNumber << "] is not found, Enter anthor Acoount Number ? ";
		getline(cin >> ws, AccountNumber);
	}
	ShowClientInfoInClientScreen(vClientData, AccountNumber);
}
// strat Transactions Screen 
// start Deposit 
void TransactionsScreen(vector <string>&);
enum enTransactionsChooses
{
	Deposit = 1,
	Withdraw = 2,
	TotalBalance = 3,
	MainMenue = 4,
};
void AddDepositAmount(vector <string>& vClientData, string AccountNumber, double DepositAmount)
{
	for (string& OneLine : vClientData)
	{
		vector <string> vClientDataLine = SplitString(OneLine, "#//#");
		if (vClientDataLine[0] == AccountNumber)
		{
			vClientDataLine[4] = to_string((stod(vClientDataLine[4]) + DepositAmount));
			OneLine = JoinString(vClientDataLine, "#//#");
			cout << "\n\nSuccessfully Operation\n\n";
			SaveNewDataAfterDeleteToFile(vClientData);
			system("pause");
			break;
		}
	}
}
void DepositScreen(vector <string>& vClientData)
{
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Deposit Screen:\n";
	cout << "-----------------------------------------\n";
	string AccountNumber = "";
	cout << "\nPlease enter Account Number ? ";
	cin >> AccountNumber;
	while (!CheckClientIfFound(AccountNumber))
	{
		cout << "Client with Account Number [" << AccountNumber << "] is not found, Enter anthor Acoount Number ? ";
		getline(cin >> ws, AccountNumber);
	}
	ShowClientInfoInClientScreen(vClientData, AccountNumber);

	double DepositAmount = 0;
	cout << "\n Please enter Deposit Amount ? ";
	cin >> DepositAmount;

	char Accept = 'Y';
	cout << "\n\nAre you sure you want perform this transaction ? y/n ? ";
	cin >> Accept;

	if (toupper(Accept) == 'Y')
	{
		AddDepositAmount(vClientData, AccountNumber, DepositAmount);
	}
}
// start total balances
void PrintClientsHeaderOfTotalBalancesScreen()
{
	cout << "\n" << setw(50) << "Client List (" << HowManyClientsAdded() << ") Clients(s)" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(20) << "Account Number"
		<< "| " << left << setw(30) << "Client Name"
		<< "| " << left << setw(15) << "Balances" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
}
void PrintClientInfoInTotalBlancesScreen(vector <string>& ClientData)
{
	cout << "| " << left << setw(20) << ClientData[0]
		<< "| " << left << setw(30) << ClientData[2]
		<< "| " << left << setw(15) << ClientData[4] << endl;
}
double CalculateTotalBalances(vector <string>& ClientData)
{
	double TotalBalances = 0;
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	if (myfile.is_open())
	{
		for (string& OneLine : ClientData)
		{
			vector <string> vClientDataLine = SplitString(OneLine, "#//#");
			TotalBalances += stod(vClientDataLine[4]);
		}
		myfile.close();
	}
	return TotalBalances;
}
void PrintClientsInfoInTotalBalancesScreen(vector <string>& vClientData)
{
	PrintClientsHeaderOfTotalBalancesScreen();
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			if (OneLine != "")
			{
				vector <string> ClearSeparatorInClientData = SplitString(OneLine, "#//#");
				PrintClientInfoInTotalBlancesScreen(ClearSeparatorInClientData);
			}
			cout << "\n";
		}
		cout << "\n______________________________________________________________________________________________________________\n";
		cout << "\n\n";
		myfile.close();
	}
	cout << right << setw(60) << "Total Balances = " << CalculateTotalBalances(vClientData);
	cout << "\n\n";
	system("pause");
	ClearScreen();
}
// start Withdraw
void AddWithDrawAmount(vector <string>& vClientData, string AccountNumber)
{
	double WithDrawAmount = 0;
	cout << "\n Please enter Withdraw Amount ? ";
	cin >> WithDrawAmount;

	for (string& OneLine : vClientData)
	{
		vector <string> vClientDataLine = SplitString(OneLine, "#//#");

		if (vClientDataLine[0] == AccountNumber)
		{
			while (WithDrawAmount > stod(vClientDataLine[4]))
			{
				cout << "\nAmount Exceeds the balance, You can withdraw up : " << stod(vClientDataLine[4]) << endl;
				cout << "Please enter another amount ? ";
				cin >> WithDrawAmount;
			}
			char Accept = 'Y';
			cout << "\n\nAre you sure you want perform this transaction ? y/n ? ";
			cin >> Accept;
			if (toupper(Accept) == 'Y')
			{
				vClientDataLine[4] = to_string(stod(vClientDataLine[4]) - WithDrawAmount);
				OneLine = JoinString(vClientDataLine, "#//#");
				cout << "\n\nSuccessfully Operation\n\n";
				SaveNewDataAfterDeleteToFile(vClientData);
			}
			system("pause");
			ClearScreen();
			break;
		}
	}
}
void WithScreen(vector <string>& vClientData)
{
	cout << "-----------------------------------------\n";
	cout << setw(35) << "Withdraw Screen:\n";
	cout << "-----------------------------------------\n";
	string AccountNumber = "";
	cout << "\nPlease enter Account Number ? ";
	cin >> AccountNumber;
	while (!CheckClientIfFound(AccountNumber))
	{
		cout << "Client with Account Number [" << AccountNumber << "] is not found, Enter anthor Acoount Number ? ";
		getline(cin >> ws, AccountNumber);
	}
	ShowClientInfoInClientScreen(vClientData, AccountNumber);
	AddWithDrawAmount(vClientData, AccountNumber);
}
void TransactionsMenue(enTransactionsChooses Choice, vector <string>& vClientData)
{
	switch (Choice)
	{
	case enTransactionsChooses::Deposit:
		ClearScreen();
		DepositScreen(vClientData);
		TransactionsScreen(vClientData);
		break;
	case enTransactionsChooses::Withdraw:
		ClearScreen();
		WithScreen(vClientData);
		TransactionsScreen(vClientData);
		break;
	case enTransactionsChooses::TotalBalance:
		ClearScreen();
		PrintClientsInfoInTotalBalancesScreen(vClientData);
		TransactionsScreen(vClientData);
		break;
	case enTransactionsChooses::MainMenue:
		ClearScreen();
		MainScreen();
		break;
	}
}
void TransactionsChooses(vector <string>& vClientData)
{
	int UserChoice = 0;
	UserChoice = ReadNumberInRange("Choose what do you want to do [ 1 to 4 ] ? ", 1, 4);
	enTransactionsChooses Choice;
	Choice = (enTransactionsChooses)UserChoice;
	TransactionsMenue(Choice, vClientData);
}
void TransactionsScreen(vector <string>& vClientData)
{
	ClearScreen();
	cout << "\n=================================================================\n";
	cout << right << setw(45) << "-( Transactions Menue Screen )-" << endl;
	cout << "=================================================================\n";
	cout << setw(20) << right << "[1]" << " Deposit." << endl;
	cout << setw(20) << "[2]" << " Withdraw." << endl;
	cout << setw(20) << "[3]" << " Total Balance." << endl;
	cout << setw(20) << "[4]" << " Main Menue." << endl;
	cout << "=================================================================\n";
	TransactionsChooses(vClientData);
}
// USER SCREEN SECTION =====================================================================
enum enUserChooses
{
	ListUser = 1, AddUser = 2, Deleteuser = 3, UpdateUser = 4, FindUser = 5, MainMenueScreen = 6
};
vector <string> SaveUsersDateInVector();
// List user screen
short HowManyUsersAdded()
{
	fstream myfile;
	myfile.open(UsersFileName, ios::in);
	short CountUsers = 0;
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			if (OneLine != "")
			{
				CountUsers++;
			}
		}
		myfile.close();
	}
	return CountUsers;
}
void PrintUsersHeader()
{
	cout << "\n" << setw(50) << "Users List (" << HowManyUsersAdded() << ") User(s)" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(30) << "User Name"
		<< "| " << left << setw(20) << "Password"
		<< "| " << left << setw(35) << "Permissions" << endl;
	cout << "\n______________________________________________________________________________________________________________\n\n";
}
void PrintUserInfo(vector <string>& UsersDate)
{
	cout << "| " << left << setw(30) << UsersDate[0]
		<< "| " << left << setw(20) << UsersDate[1]
		<< "| " << left << setw(35) << UsersDate[2] << endl;
}
void PrintUsersInfo()
{
	PrintUsersHeader();
	fstream myfile;
	myfile.open(UsersFileName, ios::in);
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			if (OneLine != "")
			{
				vector <string> ClearSeparatorInUserData = SplitString(OneLine, "#//#");
				PrintUserInfo(ClearSeparatorInUserData);
			}
			cout << "\n";
		}
		cout << "\n______________________________________________________________________________________________________________\n";
		cout << "\n\n";
		myfile.close();
	}
	system("pause");
	ClearScreen();
}
// Add user screen
struct stUserInfo
{
	string UserName, Password;
	int Permissions;
};
string CreateUserDataInLine(stUserInfo UserData, string Separator = "#//#")
{
	string UserRecord = "";
	UserRecord = UserData.UserName + Separator +
		UserData.Password + Separator + to_string(UserData.Permissions);
	return UserRecord;
}
void SaveUserDataInFile(string UserData, string FileName)
{
	fstream myfile;
	myfile.open(FileName, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << UserData << endl;
		myfile.close();
	}
}
bool CheckUserIfFound(string& UserName)
{
	vector <string> vUsersDateInLine;
	fstream myfile;
	myfile.open(UsersFileName, ios::in);
	if (myfile.is_open())
	{
		string Line;
		while (getline(myfile, Line))
		{
			vUsersDateInLine.push_back(Line);
		}
		myfile.close();
	}
	for (string& L : vUsersDateInLine)
	{
		vector <string> vUsersDateInLine = SplitString(L, Separator);
		if (vUsersDateInLine[0] == UserName)
		{
			return true;
			break;
		}
	}
	return false;
}
int GetPermissions()
{
	char Access = 'Y';
	cout << "\nDo you want to give full access ? [y/n] ";
	cin >> Access;
	int TotalAccess = 0;
	if (toupper(Access) != 'Y')
	{
		cout << "\nDo you want to give access to : \n";
		cout << "\nShow client list ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 1;
		cout << "\nAdd new client ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 2;
		cout << "\nDelete client ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 4;
		cout << "\nUpdate clients ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 8;
		cout << "\nFind clients ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 16;
		cout << "\nTransactions ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 32;
		cout << "\nManage Users ? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			TotalAccess += 64;
		return TotalAccess;
	}
	else
		return -1;
}
void AddNewUser()
{
	stUserInfo UserData;
	cout << "\n Enter UserName ? ";
	getline(cin >> ws, UserData.UserName);
	while (CheckUserIfFound(UserData.UserName))
	{
		cout << "User with [" << UserData.UserName << "] Already exists, Enter anthor Username ? ";
		getline(cin >> ws, UserData.UserName);
	}
	cout << "\n Enter password ? ";
	getline(cin, UserData.Password);
	UserData.Permissions = GetPermissions();
	// Save new user data to file
	SaveUserDataInFile(CreateUserDataInLine(UserData), UsersFileName);
}
void AddUsers()
{
	char NewUser = 'Y';
	do
	{
		system("cls");
		cout << "-----------------------------------------\n";
		cout << setw(30) << "Add new users Screen:\n";
		cout << "-----------------------------------------\n";
		cout << "\nAdding new user:\n";
		AddNewUser();
		cout << "\nUser Added Successfully, Do you want to add new user? Enter Y/N ==> ";
		cin >> NewUser;
	} while (toupper(NewUser) == 'Y');
	system("pause");
	ClearScreen();
}
//Delete users
void PrintUserInfoInUserScreen(vector <string>& UserDate)
{
	cout << "\nThe Following are the user details:\n";
	cout << "------------------------------------------\n";
	cout << "User Name              : " << UserDate[0] << endl;
	cout << "Password               : " << UserDate[1] << endl;
	cout << "Permissions            : " << UserDate[2] << endl;
	cout << "------------------------------------------\n";
}
void SaveNewUserAfterDeleteToFile(vector <string>& vUsersData)
{
	fstream myfile;
	myfile.open(UsersFileName, ios::out);
	if (myfile.is_open())
	{
		for (string& Line : vUsersData)
		{
			if (Line != "")
			{
				myfile << Line << endl;
			}
		}
	}
	myfile.close();
}
void DeleteUser(vector <string>& vUsersData, string UserName)
{
	char DeleteUser = 'y';
	cout << "Do you want to delete this client ? ";
	cin >> DeleteUser;
	if ('Y' == toupper(DeleteUser))
	{
		for (string& OneLine : vUsersData)
		{
			vector <string> vUserDataLine = SplitString(OneLine, "#//#");
			if (vUserDataLine[0] == UserName)
			{
				OneLine = "";
				cout << "\nUser Deleted successfully.\n\n";
				SaveNewUserAfterDeleteToFile(vUsersData);
				break;
			}
		}
	}
}
void ShowUserInfoInUserScreen(vector <string>& vUsersData, string& UserName)
{
	for (string& Line : vUsersData)
	{
		vector <string> vUserDataLine = SplitString(Line, Separator);
		if (vUserDataLine[0] == UserName)
		{
			PrintUserInfoInUserScreen(vUserDataLine);
			break;
		}
	}
}
void DeleteUsers()
{
	vector <string> vUsersData = SaveUsersDateInVector();
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Delete Users Screen:\n";
	cout << "-----------------------------------------\n";
	string UserName = "";
	cout << "\nPlease enter username ? ";
	cin >> UserName;
	// not able to delete the admin from the system
	if (UserName == "admin")
	{
		cout << "\nYou cannot delete this user\n\n";
		system("Pause");
		UsersScreen();
	}
	while (!CheckUserIfFound(UserName))
	{
		cout << "User with username [" << UserName << "] is not found, Enter anthorusername ? ";
		getline(cin >> ws, UserName);
	}
	ShowUserInfoInUserScreen(vUsersData, UserName);
	DeleteUser(vUsersData, UserName);
	system("pause");
}
//Update users
void UpdateTheUser(vector <string>& vUsersDataLine)
{
	cout << "Password ? ";
	getline(cin >> ws, vUsersDataLine[1]);
	vUsersDataLine[2] = to_string(GetPermissions());
}
void UpdateOneUser(vector <string>& vUsersData, string UserName)
{
	char UpdateUser = 'y';
	cout << "Do you want to update this user ? ";
	cin >> UpdateUser;
	if ('Y' == toupper(UpdateUser))
	{
		for (string& OneLine : vUsersData)
		{
			vector <string> vUsersDataLine = SplitString(OneLine, Separator);
			if (vUsersDataLine[0] == UserName)
			{
				UpdateTheUser(vUsersDataLine);
				OneLine = JoinString(vUsersDataLine, "#//#");
				cout << "\nUser Updated successfully.\n\n";
				SaveNewUserAfterDeleteToFile(vUsersData);
				break;
			}
		}
	}
}
void UpdateUsers()
{
	vector <string> vUsersData = SaveUsersDateInVector();
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Update Users Screen:\n";
	cout << "-----------------------------------------\n";
	string UserName = "";
	cout << "\nPlease enter username ? ";
	cin >> UserName;
	while (!CheckUserIfFound(UserName))
	{
		cout << "User with username [" << UserName << "] is not found, Enter anthorusername ? ";
		getline(cin >> ws, UserName);
	}
	ShowUserInfoInUserScreen(vUsersData, UserName);
	UpdateOneUser(vUsersData, UserName);
	system("pause");
}
// Find Users
void FindUsers()
{
	vector <string> vUsersData = SaveUsersDateInVector();
	cout << "-----------------------------------------\n";
	cout << setw(30) << "Find Users Screen:\n";
	cout << "-----------------------------------------\n";
	string UserName = "";
	cout << "\nPlease enter username ? ";
	cin >> UserName;
	while (!CheckUserIfFound(UserName))
	{
		cout << "User with username [" << UserName << "] is not found, Enter anthorusername ? ";
		getline(cin >> ws, UserName);
	}
	ShowUserInfoInUserScreen(vUsersData, UserName);
	system("pause");
}
void ManageUserScreen(enUserChooses UserChoice)
{
	switch (UserChoice)
	{
	case ListUser:
		ClearScreen();
		PrintUsersInfo();
		UsersScreen();
		break;
	case AddUser:
		ClearScreen();
		AddUsers();
		UsersScreen();
		break;
	case Deleteuser:
		ClearScreen();
		DeleteUsers();
		UsersScreen();
		break;
	case UpdateUser:
		ClearScreen();
		UpdateUsers();
		UsersScreen();
		break;
	case FindUser:
		ClearScreen();
		FindUsers();
		UsersScreen();
		break;
	case MainMenueScreen:
		ClearScreen();
		MainScreen();
		break;
	}
}
void UserChooses()
{
	int UserChoice = 0;
	UserChoice = ReadNumberInRange("Choose what do you want to do [ 1 to 6 ] ? ", 1, 6);
	enUserChooses Choice;
	Choice = (enUserChooses)UserChoice;
	ManageUserScreen(Choice);
}
void UsersScreen()
{
	ClearScreen();
	cout << "\n=================================================================\n";
	cout << right << setw(45) << "-( Manage Users Menue Screen )-" << endl;
	cout << "=================================================================\n";
	cout << setw(20) << right << "[1]" << " List Users." << endl;
	cout << setw(20) << "[2]" << " Add New User." << endl;
	cout << setw(20) << "[3]" << " Delete User." << endl;
	cout << setw(20) << "[4]" << " Update User." << endl;
	cout << setw(20) << "[5]" << " Find User." << endl;
	cout << setw(20) << "[6]" << " Main Menue." << endl;
	cout << "=================================================================\n";
	UserChooses();
}
// START MAIN SCREEN
void BackToMainScreen()
{
	system("pause");
	ClearScreen();
	MainScreen();
}
enum enUserChoice
{
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Transactions = 6,
	ManageUsers = 7,
	Logout = 8,
};
void ResultOfUserChoice(enUserChoice& Choice, vector <string>& vClientData)
{
	switch (Choice)
	{
	case enUserChoice::Show:
		ClearScreen();
		PrintClientsInfo();
		BackToMainScreen();
		break;
	case enUserChoice::Add:
		ClearScreen();
		AddClients();
		BackToMainScreen();
		break;
	case enUserChoice::Delete:
		ClearScreen();
		DeleteClients(vClientData);
		BackToMainScreen();
		break;
	case enUserChoice::Update:
		ClearScreen();
		UpdateClients(vClientData);
		BackToMainScreen();
		break;
	case enUserChoice::Find:
		ClearScreen();
		FindClients(vClientData);
		BackToMainScreen();
		break;
	case enUserChoice::Transactions:
		ClearScreen();
		TransactionsScreen(vClientData);
		break;
	case enUserChoice::ManageUsers:
		ClearScreen();
		UsersScreen();
		break;
	case enUserChoice::Logout:
		ClearScreen();
		LoginScreen();
		break;
	}
}
vector <string> SaveClientsDataInVector(vector <string>& vClientData)
{
	fstream myfile;
	myfile.open(ClientsFileName, ios::in);
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			vClientData.push_back(OneLine);
		}
		myfile.close();
	}
	return vClientData;
}
bool PermissionsResult(int UserChoose, int UserPermissions)
{
	string UserPermissionsString = "";
	// convert user permission number to binary number
	std::bitset<8> binaryNumber(UserPermissions);
	// convert binary number to string to check the permission
	UserPermissionsString = binaryNumber.to_string();
	for (int i = UserPermissionsString.length() - 1; i >= 0; i--)
	{
		if (UserPermissionsString.length() - i == UserChoose )
		{
			if (UserPermissionsString[i] == '1')
				return true;
			else
				return false;
		}
	}
}
bool CheckPermissions(int UserChoose)
{
	string UserName = CurrentUserName;
	vector <string> vUsersDate = SaveUsersDateInVector();
	int UserPermission = 0;
	for (string& Line : vUsersDate)
	{
		vector <string> DateForOneUser = SplitString(Line, Separator);
		if (UserName == DateForOneUser[0])
		{
			UserPermission = stoi(DateForOneUser[2]);
			break;
		}
	}
	if ( UserPermission == -1 || UserChoose == 8)
		return true;
	if (PermissionsResult(UserChoose, UserPermission))
		return true;
	else
	{
		ClearScreen();
		cout << "\n-----------------------------------------------------------------\n";
		cout << "Access Denied !!\n";
		cout << "you don't have permission to do this ,\n";
		cout << "Please contact your admin.\n";
		cout << "\n-----------------------------------------------------------------\n";
	}
	system("pause");
	ClearScreen();
	MainScreen();
}
void UserChoice()
{
	vector <string> vClientData;
	vClientData = SaveClientsDataInVector(vClientData);
	int UserChoice = 0;
	UserChoice = ReadNumberInRange("Choose what do you want to do [ 1 to 8 ] ? ", 1, 8);
	CheckPermissions(UserChoice);
	enUserChoice Choice;
	Choice = (enUserChoice)UserChoice;
	ResultOfUserChoice(Choice, vClientData);
}
void MainScreen()
{
	cout << "\n=================================================================\n";
	cout << right << setw(35) << "-( Main Screen )-" << endl;
	cout << "=================================================================\n";
	cout << setw(20) << right << "[1]" << " Show Client List." << endl;
	cout << setw(20) << "[2]" << " Add New Client." << endl;
	cout << setw(20) << "[3]" << " Delete Client." << endl;
	cout << setw(20) << "[4]" << " Update Client Info." << endl;
	cout << setw(20) << "[5]" << " Find Client." << endl;
	cout << setw(20) << "[6]" << " Transactions." << endl;
	cout << setw(20) << "[7]" << " Manage Users." << endl;
	cout << setw(20) << "[8]" << " Logout." << endl;
	cout << "=================================================================\n";
	UserChoice();
}
//LOGIN SCREEN SECTION 
struct stSignIn
{
	string UserName, Password;
};
bool CheckUserIfFound(string& UserName, string& Password)
{
	vector <string> vUsersDateInLine;
	fstream myfile;
	myfile.open(UsersFileName, ios::in);
	if (myfile.is_open())
	{
		string Line;
		while (getline(myfile, Line))
		{
			vUsersDateInLine.push_back(Line);
		}
		myfile.close();
	}
	for (string& L : vUsersDateInLine)
	{
		vector <string> vUsersDateInLine = SplitString(L, Separator);
		if (vUsersDateInLine[0] == UserName)
		{
			if (vUsersDateInLine[1] == Password)
				return true;
			else
				return false;
		}
	}
	return false;
}
stSignIn LoginScreenSignIn()
{
	stSignIn SignIn;
	cout << "Enter user name ? ";
	cin >> SignIn.UserName;
	cout << "Enter Password ? ";
	cin >> SignIn.Password;
	return SignIn;
}
vector <string> SaveUsersDateInVector()
{
	vector <string> vUsersDate;
	fstream myfile;
	myfile.open(UsersFileName, ios::in);
	if (myfile.is_open())
	{
		string OneLine;
		while (getline(myfile, OneLine))
		{
			vUsersDate.push_back(OneLine);
		}
		myfile.close();
	}
	return vUsersDate;
}
void LoginScreen()
{
	cout << "\n=================================================================\n";
	cout << right << setw(35) << "-( Login Screen )-" << endl;
	cout << "=================================================================\n";
	vector <string> vUsersDate = SaveUsersDateInVector();
	stSignIn SignIn = LoginScreenSignIn();
	while (!CheckUserIfFound(SignIn.UserName, SignIn.Password))
	{
		ClearScreen();
		cout << "\n=================================================================\n";
		cout << right << setw(35) << "-( Login Screen )-" << endl;
		cout << "=================================================================\n";
		cout << "Invalid username/password!\n";
		SignIn = LoginScreenSignIn();
	}
	CurrentUserName = SignIn.UserName;
	ClearScreen();
	MainScreen();
}
int main()
{
	LoginScreen();
}