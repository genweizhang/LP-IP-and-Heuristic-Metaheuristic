#include <iostream>
using namespace std;


void exchangeval(int& x, int& y);
int i=0;
int main() {
            cout<< "Hello World!"<<endl;
            i++;
            cout<<i<<endl;
            int b=5;
            exchangeval(i,b);
            cout<<"my new i is:"<<i<<endl;
            return 0;
            
             }
                 
 void exchangeval(int& x, int& y) {
                                 int temp;
                                 temp=x;
                                 x=y;
                                 y=temp;
                                 return;
                                }



	
