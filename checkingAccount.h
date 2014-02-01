class checkingAccount : public bankAccount{
   
   private:
   int accountNumber;
   string accountName;
   double accountBalance;
   char accountType;
   int startTime;
   int currentTime;
   
   public:
   
   void printInfo();
   void makeDeposit();
   void makeWithdrawl();
   void writeCheck();
   int getNum();
   string getName();
   double getBalance();
   char getType();
   int getStart();
   int getCurrent();
   void setBalance(double);
   double calculateInterest();
   
   checkingAccount(int num, string name, double balance, char type, int start){
   
   accountNumber = num;
   accountName = name;
   accountBalance = balance;
   accountType = type;
   startTime = start;
   currentTime = time(0);
   
   }
   
};