#include<iostream>
#include <string>
#include <fstream>
using namespace std;

const int SIZE = 10;
struct Shareholder
{
	int accountID, availableBalance, numberofShares, amountInvested;
	string customerName, investmentCompany;
};
struct Shares
{
	double pricePerShare;
	string companyName;
};
void loadStockInfo(Shares info[]);
Shareholder getShareholderData();
void displayShares(const Shares info[]);
void stockPurchase(Shareholder& purchase, const Shares info[]);
void displayaccountinfo(const Shareholder purchase);
int main()
{
	Shares shares[SIZE];
	loadStockInfo(shares);
	Shareholder holderInfo = getShareholderData();
	displayShares(shares);
	stockPurchase(holderInfo, shares);
	displayaccountinfo(holderInfo);
	system("Pause");
	return 0;
}
void loadStockInfo(Shares info[])
{
	ifstream inFile;
	inFile.open("stockDataCPSC121.txt");
	for (int i = 0; i < SIZE; i++)
	{
		getline(inFile, info[i].companyName, ',');
		inFile.ignore(1, ',');
		inFile >> info[i].pricePerShare;
		inFile.ignore();
	}
}
Shareholder getShareholderData()
{
	Shareholder holderInfo;
	cout << "What is the available balance? " << endl;
	cin >> holderInfo.availableBalance;
	cin.ignore();
	cout << "What is your name? " << endl;
	getline(cin, holderInfo.customerName);
	cout << "What is your account ID? " << endl;
	cin >> holderInfo.accountID;
	cout << endl;
	return holderInfo;
}
void displayShares(const Shares info[])
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << info[i].companyName << "\'s Price Per Share: $" << info[i].pricePerShare << endl;
	}
}
void stockPurchase(Shareholder& purchase, const Shares info[])
{
	char choice;
	cout << "Would you like to invest into a stock purchase(y/n)? " << endl;
	cin >> choice;
	cin.ignore();
	while (((choice != 'n') && (choice != 'N')) && ((choice != 'y') && (choice != 'Y'))) {
		cout << "Incorrect input!! Would you like to try again? " << endl;
		cin >> choice;
		cin.ignore();
	}
	if ((choice == 'y') || (choice == 'Y'))
	{
		cout << "What company would you like to invest in? " << endl;
		getline(cin, purchase.investmentCompany);
		for (int i = 0; i < SIZE; i++)
		{
				if (purchase.investmentCompany == info[i].companyName)
				{
					cout << "How many shares would you like to purchase? " << endl;
					cin >> purchase.numberofShares;
					purchase.amountInvested = purchase.numberofShares*info[i].pricePerShare;
					while (purchase.amountInvested >= purchase.availableBalance)
					{
						cout << "Your purchase is greater than your available balance!!" << endl;
						cout << "Please input how many shares you would like to buy: " << endl;
						cin >> purchase.numberofShares;
						purchase.amountInvested = purchase.numberofShares*info[i].pricePerShare;
					}
					purchase.availableBalance -= purchase.amountInvested;
					cout << "Purchase Complete!" << endl;
					break;
				}
				else if(purchase.investmentCompany != info[i].companyName)
				{
					cout << "Incorrect Company!" << endl;
					cout << "Would you still like to invest in a company(y/n)? " << endl;
					cin >> choice;
					cin.ignore();
					break;
				}
		}
	}
	if ((choice == 'n') || (choice == 'N')) {
		cout << "You are not exiting your purchase" << endl;
	}
}
void displayaccountinfo(const Shareholder purchase)
{
	char choice;
	cout << "Would you like to see your account informaiton? " << endl;
	cin >> choice;
	cin.ignore();
	if ((choice == 'y') || (choice == 'Y'))
	{
		cout << "Name: " <<purchase.customerName << "            Account ID: " << purchase.accountID << endl << endl;;
		cout << "You have invested $" << purchase.amountInvested << ". Your remaining balance is $" << purchase.availableBalance << "." << endl;
		cout << "You have invested in "<<purchase.investmentCompany << "\'s stocks with " << purchase.numberofShares<< " shares." << endl;
	}
	else {
		cout << "Thank you for your purchases!" << endl;
	}
}
