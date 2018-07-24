#include <iostream>
using namespace std;

int i;
void multiply (int& a){
		    a=i*2; 
	            }
int main(){
	   for (i=1; i<15;i++){
				 cout<<i<<endl;
				 multiply(i);
 				 cout<<i<<endl;
 				while (i>13 && i<28){
					     i=i/2;	
					    }	
			      }			
	   return 0;
	  }
