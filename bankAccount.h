class bankAccount{

   private:
                
   public:
   
   virtual void printInfo() = 0;
   virtual int getNum() = 0;
   virtual string getName() = 0;
   virtual double getBalance() = 0;
   virtual char getType() = 0;
   virtual int getStart() = 0;
   virtual int getCurrent() = 0;
   virtual void makeDeposit() = 0;
   virtual void makeWithdrawl() = 0;
   virtual void setBalance(double) = 0;
   virtual double calculateInterest() = 0;
   virtual void writeCheck() = 0;
   
   
};