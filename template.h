template <class T>
class Array
{
public:

 Array(){
   size = 1;
   data = new T*[size];
 }

 void addAccount(T* d){
  
   T **temp;  
   temp = new T*[size];
   for (int i=0;i<size;i++){
   temp[i] = data[i];
   }
   delete[] data;
   data = new T*[size];
   for (int i=0;i<size;i++){
   data[i] = temp[i];
   }
   delete[] temp;
   data[size-1]=d;
   size++;
   
 }
 
 int getSize(){
   return size;
 }  

 T* getAccount(int n){
   return data[n];
 }

private:
 T **data;
 int size;
};
