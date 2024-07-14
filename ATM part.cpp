//****************************************************************************
//                           HEADER FILE USED IN PROJECT  
//****************************************************************************

#include<iostream>   
#include<fstream>
#include<cctype>
#include<iomanip> 
#include<ctime>
#include<conio.h>
using namespace std;

//****************************************************************************
//                           CLASS USED IN PROJECT                               
//****************************************************************************												

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
 public:
	void create_account(); // function to get data from user
	void show_account() const;  //function to show data on screen
	void modify();  // function to add new data													
	void dep(int); // function to accept amount and add to balance amount
	void draw(int); // function to accept amount and subtract from the balance amount
	void report()const; // function to show data in tabular form
	int retacno()const; // function to account number
	int retdeposit()const; //function to return balance amount
	char rettype()const; // function to return type of account
	void developers();
};            //  CLASS ENDS HERE

void account::create_account()
{
	cout<<"\n Enter the Account Number. : ";
	cin>>acno;
	cout<<"\n Enter the name of Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout<<"\n Enter type of account(c/s) : ";
	cin>>type;
	type = toupper(type);
	cout<<"\n Enter the initial amount(>=500 for saving and >=1000 for current) : ";
	cin>>deposit;
	cout<<"\n Accpount created ...";										
}

void account::show_account()const
{
	cout<<"\n Account Number. : "<<acno;
	cout<<"\n Account Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\n Balance Amount : "<<deposit;
}


void account::modify()
{
	cout<<"\n Account No. : " <<acno;
	cout<<"\n Modify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout<<"\n Modify Type of Account : ";
	cin>>type;
	type  = toupper(type);														
	cout<<"\nModify Balance Amount : ";
	cin>>deposit;
}

//**************************************************************************************
//					BASIC FUNCTIONALITIES
//**************************************************************************************
void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report()const
{
	cout<<acno<<setw(10)<<"	"<<name<<"		 "<<type<<"		"<<deposit<<endl;	
}																			

int account::retacno()const
{
	return acno;
}

int account::retdeposit()const
{
	return deposit;
}

char account::rettype()const
{
	return type;
}
void account::developers()
{
}

//****************************************************************************
// 							 function declaration
//****************************************************************************

	void write_account();			//function to write record in binary file								
	void display_sp(int);			//function to display account detailsgiven by user
	void modify_account(int);		//function to modify record of file
	void delete_account(int);		//function to delete record of file
	void display_all();				//funtion to display all account details
	void deposit_withdraw(int,int); //function to deposit/withdraw amount for the given account
	void intro();  					//Introductory screen function
	void developers();

//*****************************************************************************
//             		  THE MAIN FUNCTION OF THE PROGRAM   
//*****************************************************************************

int main()
{
	char ch;
	int num;
	time_t now = time(0);
    char* dt = ctime(&now);
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\t\t\tWELCOME TO BURAAQ BANKING SYSTEM\n\n";
		cout<<"\t\t\t"<<dt;
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";										
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. DELETE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. LOGOUT";
		cout<<"\n\n\t09. SOFTWARE CREATERS";
		cout<<"\n\n\t0...SELECT YOUR OPTION (1-8)";
		ch=getch();
		system("cls");
		switch(ch)
		{
			case '1':
				write_account();
				break;
			case '2':
				cout<<"\n Enter the Account NO. : ";cin>>num;
				deposit_withdraw(num,1);
				break;															
			case '3':
				cout<<"\n\n\t Enter the Account No. : ";cin>>num;
				deposit_withdraw(num,2);
				break;
			case '4':
				cout<<"\n\n\t Enter the Account No. : ";cin>>num;
				display_sp(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout<<"\n\n\t Enter the Account NO. : ";cin>>num;
				delete_account(num);
				break;
			case '7':
				cout<<"\n\n\t Enter the Account No. : ";cin>>num;
				modify_account(num);
				break;
			case '8':
				cout<<"\n\n\t THANKS FOR USING BANK MANAGMENT SYSTEM";
				break;
			case '9':
				developers();
				break;																		
			default:cout<<"\a";	
		}
		cin.ignore();
		cin.get();	
	}while (ch != '8');
	return 0;
}


//*****************************************************************************
//     					function to make record in file
//*****************************************************************************
void write_account()
{
	account ac;
	ofstream outFile;														
	outFile.open("account.dat",ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
	outFile.close();
}


//********************************************************************************
//    				function to read specific record from file
//********************************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key";						
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
	   cout << "\n\n Account number does not exist";	
}


//************************************************************************************
//       functions to modify record of file
//************************************************************************************										

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary | ios::in | ios::out );
	if (!File)
	{
		cout<<"file could not be open !! Press any key";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*>(&ac),sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout<<"\n\nEnter the new details of account"<<endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac),sizeof(account));
			cout<<"\n\nRecord Updated";							
			found = true;
		}
	}
	File.close();
	if(found==false)
	cout<<"\n\nRecord not found";
}
		
//****************************************************************************
//                           FUNCTION TO DELETE RECORD  
//****************************************************************************											


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!! Press any key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
	{
		if(ac.retacno()!= n)
		{
			outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");										
	cout<<"\n\n\tRecord Deleted...";											
}

//***************************************************************************
//					FUNCTION TO DISPLAY DEPOSIT LIST
//***************************************************************************

void display_all()
{
	account ac;
	time_t now = time(0);
    char* dt = ctime(&now);
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST";
	cout<<"\n\n\t\t\t"<<dt;
	
	cout<<"\n\n**********************************************************************\n";
	cout<<"A/C.		NAME		TYPE		BALANCE\n";
	cout<<"**********************************************************************\n";		
	while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))					
	{
		ac.report();
	}
	inFile.close();
}

//********************************************
//		FUNCTION DEPOSIT AND WITHDRAW AMOUNT
//*****************************************

void deposit_withdraw(int n,int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary | ios::in | ios::out);
	if(!File)
	{
		cout<<"File could not be open!! Press any key...";
		return;																		
	}
	while(!File.eof()&&found==false)
	{
		File.read(reinterpret_cast<char*>(&ac),sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\nTo Deposit Amount";
				cout<<"\n\nEnter the amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\nTo Withdraw Amount";
				cout<<"\n\nEnter the amount to be withdraw";								
				cin>>amt;																	
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient Balance";
				else
					ac.draw(amt);
		}
		int pos=(-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos, ios::cur);
		File.write(reinterpret_cast<char*>(&ac), sizeof(account));
		cout<<"\n\n\tRecord updated";
		found=true;
	}
}
File.close();
if(found==false)	
	cout<<"\n\nRecord not found";
}

//***************************************************************************
//						INTRODUCTION FUNCTION
//***************************************************************************				

void intro()													
{
	
	time_t now = time(0);
    char* dt = ctime(&now);
	cout<<"\n\n\t\t\tWELCOME TO BURAAQ BANKING SYSTEM\n\n";
	cout<<"\t\t\t"<<dt;
	cout<<"\n\n\nEnter any key to continue";
	cin.get();
}


//***************************************DEVELOPERS**********************
void developers()				//DEVELOPERS DETAIl
{
	char choose;
	cout<<"\n\n\t\tSoftware \t:\tBURAAQ ONLINE BANKING STSTEM"<<endl;
	cout<<"\t\tCompany  \t:\tPROJECT TEAM"<<endl;
	cout<<"\t\tTeam Head\t:\tMuzammil Ijaz Mughal\n"<<endl;
	cout<<"*************************************************************";
	cout<<"\n\nTeam Members with Registration Number:"<<endl;
	cout<<"\t\t1. Muzammil Ijaz \t:\tFA22-BSE-116"<<endl;
	cout<<"\t\t2. Muzamil Munir \t:\tFA22-BSE-111"<<endl;
	cout<<"\t\t3. Bilal Afzal	\t:\tFA22-BSE-107\n"<<endl;
	cout<<"*************************************************************";
	cout<<"\n\n\nEnter any key to continue";
	cin.get();
}
//**************************************************************************
//*************************************************************************
//*******************************		END		********************************
//*************************************************************************
//**************************************************************************
