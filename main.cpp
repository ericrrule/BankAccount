#include <iostream>
using namespace std;
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "template.h"
#include "bankAccount.h"
#include "savingsAccount.h"
#include "checkingAccount.h"

void startup(Array<bankAccount> &);
int getInt(const int defaultValue);
int findAccount(Array<bankAccount> &);
int giveNumber(Array<bankAccount> &);
void createNewAccount(Array<bankAccount> &);
void readAccounts(Array<bankAccount> &);
void writeAccounts(Array<bankAccount> &);
void displayInfo(Array<bankAccount> &);
void preWithdrawl(Array<bankAccount> &);
void preDeposit(Array<bankAccount> &);
void preCheck(Array<bankAccount> &);

int main(){
 
Array<bankAccount> a;

readAccounts(a);

startup(a);

writeAccounts(a);
 
return 0;   

}

// Function startup runs at beginning of program execution for user input

void startup(Array<bankAccount> &a){

int answer;

cout << "\nWelcome to the Rule Banking Institution.\n\n";
cout << "Below are a list of possible actions to take.\n\n";
cout << "1 - Create a new bank account.\n";
cout << "2 - Display account information.\n";
cout << "3 - Make a deposit.\n";
cout << "4 - Make a withdrawl.\n";
cout << "5 - Write a check (if account type is checking).\n\n";

cout << "Please enter the number of the option you wish to select: \n";

answer = getInt(-1);

switch(answer){

   case(1):  
      cout << "You have chosen to create a new bank account.\n";
      createNewAccount(a);
      break;
   case(2):  
      cout << "You have chosen to display your account information.\n";
      displayInfo(a);
      break;
   case(3):  
      cout << "You have chosen to make a deposit.\n";
      preDeposit(a);
      break;
   case(4):  
      cout << "You have chosen to make a withdrawl.\n";
      preWithdrawl(a);
      break;
   case(5):  
      cout << "You have chosen to write a check.\n";
      preCheck(a);
      break;
   default:
      cout << "Invalid input. Please input one of the numbers listed above.\n";
      startup(a);
      break;
   }
}

//getInt simply allows the program to stop the loop in startup()

int getInt(const int defaultValue = -1){
  
  string input;
  cin >> input;
  stringstream stream(input);
  int result = defaultValue;
  if(stream >> result) return result;
  else return defaultValue;

}


// createNewAccount walks the user through which type of account he or she wants to 
// open and creates a new account of that type.

void createNewAccount(Array<bankAccount> &a){
  string ans, ans2;
  cout << "Please specify which type of account you wish to open by typing either 'Savings' or 'Checking': \n";
  cin >> ans;
  
  // Open a new savings account
  
  if(ans == "Savings" || ans == "savings"){
   cout << "You have chosen to create a new savings account.  Is this correct? (yes/no)\n";
   cin >> ans2;
      if(ans2 == "yes" || ans2 == "Yes" || ans2 == "y" || ans2 == "YES"){
         string name;
         double balance;
         int number, start;
         cout << "Thank you for choosing to create a new savings account.  What is your name?\n";
         cin >> name;
         number = giveNumber(a);
         cout << "Your account number is: " << number << endl;
         cout << "The interest rate for this account is 1.2%, compounded annually.\n";
         cout << "The minimum required balance for this account is $1000.\nIf the balance falls below this threshold, there will be a $5 monthly charge.\n";
         cout << "Please enter the amount of cash you would like to initially deposit: ";
         cin >> balance;
         start = time(0);
         savingsAccount* s = new savingsAccount(number, name, balance, 's', start);
         a.addAccount(s);
      }
      else if(ans2 == "no" || ans2 == "No" || ans2 == "n" || ans2 == "NO"){
      createNewAccount(a);
      }
      else{
      cout << "Invalid response.\n";
      createNewAccount(a);
      }
  }
  // Open a new checking account
  
  else if (ans == "Checking" || ans == "checking"){
   cout << "You have chosen to create a new checking account.  Is this correct? (yes/no)\n";
   cin >> ans2;
      if(ans2 == "yes" || ans2 == "Yes" || ans2 == "y" || ans2 == "YES"){
         string name;
         double balance;
         int number, start;
         cout << "Thank you for choosing to create a new checking account.  What is your name?\n";
         cin >> name;
         number = giveNumber(a);
         cout << "Your account number is: " << number << endl;
         cout << "The minimum required balance for this account is $1000.\nIf the balance falls below this threshold, there will be a $5 monthly charge.\n";
         cout << "Please enter the amount of cash you would like to initially deposit: ";
         cin >> balance;
         start = time(0);
         checkingAccount* c = new checkingAccount(number, name, balance, 'c', start);
         a.addAccount(c);
         
      }     
      else if(ans2 == "no" || ans2 == "No" || ans2 == "n" || ans2 == "NO"){
      createNewAccount(a);
      }
      else{
      cout << "Invalid response.\n";
      createNewAccount(a);
      }
  }
  else{
  cout << "Invalid response.\n";
      createNewAccount(a);
  
  }
}

//displayInfo is called from startup() and finds the proper account with findAccount, then calls the proper printInfo

void displayInfo(Array<bankAccount> &a){
   
   int i = findAccount(a);
   a.getAccount(i)->printInfo();

}

//giveNumber returns a sequential integer to be used as a unique account number

int giveNumber(Array<bankAccount> &a){

   return a.getSize();
   
}

//preWithdrawl is called from startup() and finds the proper account with findAccount, then calls the proper makeWithdrawl

void preWithdrawl(Array<bankAccount> &a){

   int i = findAccount(a);
   a.getAccount(i)->makeWithdrawl();
   
}

//preDeposit is called from startup() and finds the proper account with findAccount, then calls the proper makeDeposit

void preDeposit(Array<bankAccount> &a){

   int i = findAccount(a);
   a.getAccount(i)->makeDeposit();
   
}

/*preCheck is called from startup() and finds the proper account with findAccount, then calls the proper writeCheck
 *NOTE: although I declared writeCheck as a pure virtual function in bankAccount, I do not allow the savingsAccount
 *implementation to be called by checking for the account type.
 */

void preCheck(Array<bankAccount> &a){

   int i = findAccount(a);
   if (a.getAccount(i)->getType() == 'c'){
   a.getAccount(i)->writeCheck();
   }
   else{
   cout << "\nError: account specified is a savings account.\n";
   preCheck(a);
   }
   
}


//printInfo uses std::cout to display all necessary information about an account to a customer

void checkingAccount::printInfo(){

   cout << "\nAccount statement for: " << accountName << "." << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Account type: Checking Account" << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Account number: " << accountNumber << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Balance: $" << fixed << setprecision(2) << accountBalance << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Time passed since account creation: " << currentTime - startTime << " seconds." << endl;
   cout << "---------------------------------------------------" << endl;
   
}

//printInfo uses std::cout to display all necessary information about an account to a customer

void savingsAccount::printInfo(){
   
   cout << "\nAccount statement for: " << accountName << "." << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Account type: Savings Account" << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Account number: " << accountNumber << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Balance: $" << fixed << setprecision(2) << accountBalance << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Interest rate: 1.2%" << endl;
   cout << "---------------------------------------------------" << endl;
   cout << "Time passed since account creation: " << currentTime - startTime << " seconds." << endl;
   cout << "---------------------------------------------------" << endl;   

}

//findAccount searches for an account by its unique account number

int findAccount(Array<bankAccount> &a){
int i,j,n;
cout << "Please enter your account number: ";
cin >> n;
if(n > 0){
   for(i=0;i<a.getSize()-1;i++){
      if(a.getAccount(i)->getNum() == n){
      j = i;
      cout << "Account found successfully." << endl;
      }
      else{
      }
   }
}
else{
   cout << "Invalid account number. Please enter a valid account number.\n";
   findAccount(a);
}
return j;
}

/* The following are implementations for all of the used functions that were declared pure virtual in the parent class
 * bankAccount. They are almost identical for savings and checking, as the only difference between the two is the addition
 * of an interest rate.
 */
 
//These are simple accessor and mutator functions 

int checkingAccount::getNum(){return accountNumber;}
string checkingAccount::getName(){return accountName;}
double checkingAccount::getBalance(){return accountBalance;}
char checkingAccount::getType(){return accountType;}
int checkingAccount::getStart(){return startTime;}
int checkingAccount::getCurrent(){return currentTime;}
void checkingAccount::setBalance(double d){accountBalance = d;}

//calculateInterst does nothing for a checking account as it is never actually used

double checkingAccount::calculateInterest(){return 0;}

//makeWithdrawl simply "removes" money from the balance and "gives" it to the user

void checkingAccount::makeWithdrawl(){

   double w;
   cout << "Enter the amount you wish to withdraw from your account, equal to or lesser than: $" << getBalance() << endl;
   cin >> w;
   if(w <= getBalance()){
   setBalance(getBalance() - w);
   cout << endl;
   cout << "Withdrawl successful. Your new balance is: " << fixed << setprecision(2) <<  getBalance() << endl;
   }
   else{
   cout << "You have attempted to withdraw more money than you currently have in your account.\nOperation aborted.";
   }

}

//makeDeposit adds money to an account

void checkingAccount::makeDeposit(){
   
   double d;
   cout << "Please enter amount you wish to deposit.\n";
   cin >> d;
   if(d > 0){
   accountBalance += d;
   cout << "Deposit successful. Your new balance is: " << fixed << setprecision(2) << accountBalance << endl;
   }
   else{
   cout << "You have attempted to deposit an impossible amount. Please enter a valid amount to deposit.\n";
   makeDeposit();
   }
   
}

//writeCheck simply acts as a withdrawl

void checkingAccount::writeCheck(){

   cout << "Please enter the name of the person you wish to write the check to: ";
   string name;
   cin >> name;
   cout << "\nPlease enter the amount of cash to transfer: ";
   double d;
   cin >> d;
   setBalance(getBalance() - d);
   cout << "\nCheck successfully written to " << name << ". Your new balance is: $" << fixed << setprecision(2) <<  getBalance() << endl;

}
   
//Accessor and mutators for savingsAccount

int savingsAccount::getNum(){return accountNumber;}
string savingsAccount::getName(){return accountName;}
double savingsAccount::getBalance(){return accountBalance;}
char savingsAccount::getType(){return accountType;}
int savingsAccount::getStart(){return startTime;}
int savingsAccount::getCurrent(){return currentTime;}
void savingsAccount::setBalance(double d){accountBalance = d;}

//implementation of writeCheck that is never called

void savingsAccount::writeCheck(){}

//calculateInterest calculates the interest accrued since account creation time

double savingsAccount::calculateInterest(){
   int difference = currentTime - startTime;
   double t = (difference/31526000);
   double result = 0;
   result = (accountBalance * pow(1.012, t)) - accountBalance;
   return result;
}

//makeWithdrawl simply "removes" money from the balance and "gives" it to the user

void savingsAccount::makeWithdrawl(){
   
   double w;
   cout << "Enter the amount you wish to withdraw from your account, equal to or lesser than: $" << getBalance() << endl;
   cin >> w;
   if(w <= getBalance()){
   cout << "At the time of this withdrawl, your accrued interest is: $" << calculateInterest() << endl;
   setBalance((getBalance() - w) + calculateInterest());
   cout << endl;
   cout << "Withdrawl successful. Your new balance is: " << fixed << setprecision(2) << getBalance() << endl;
   }
   else{
   cout << "You have attempted to withdraw more money than you currently have in your account.\nOperation aborted.";
   }
   
}

//makeDeposit adds money to an account

void savingsAccount::makeDeposit(){
   
   double d;
   cout << "Please enter amount you wish to deposit.\n";
   cin >> d;
   if(d > 0){
   accountBalance += d;
   cout << "Deposit successful. Your new balance is: " << fixed << setprecision(2) << accountBalance << endl;
   }
   else{
   cout << "You have attempted to deposit an impossible amount. Please enter a valid amount to deposit.\n";
   makeDeposit();
   }
   
}

//readAccounts is called at the beginning of every program execution and reads previous data into the Array

void readAccounts(Array<bankAccount> &a){
   ifstream infile;
   string name;
   double balance;
   int num, start, current;
   char type;
   infile.open("accountdata.txt");
   if(infile.fail()){
      cout << "Cannot retrieve any accounts.\n\n";
      return;
   }
   else{
   while(infile >> num >> name >> balance >> type >> start >> current){
      if(type == 'c'){
            checkingAccount* c = new checkingAccount(num, name, balance, type, start);
            a.addAccount(c);
         }
      
      else if(type == 's'){
            savingsAccount* s = new savingsAccount(num, name, balance, type, start);
            a.addAccount(s);
         } 
      else{
      }
   }
   }
   infile.close();
   cout << "\nLoaded bank accounts." << endl;

}

//writeAccounts is called at the end of every program execution and writes all existing data to the text file

void writeAccounts(Array<bankAccount> &a){
   ofstream outfile;
   outfile.open("accountdata.txt");
   if(outfile.fail()){
      cout << "Cannot retrieve any accounts.\n\n";
      return;
   }
   else{
   for(int i=0; i < a.getSize()-1;i++){
   outfile << a.getAccount(i)->getNum() << " " << a.getAccount(i)->getName() << " " << a.getAccount(i)->getBalance()
    << " " << a.getAccount(i)->getType() << " " << a.getAccount(i)->getStart() << " " << a.getAccount(i)->getCurrent() << endl;
   }
   }
   outfile.close();
}
