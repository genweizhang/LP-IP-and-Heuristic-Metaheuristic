#include <iostream>
using namespace std;

int factorial (int n)
         {
	  int f;
	  if (n<1) return 1;
	  f=factorial(n-1);
	  return n*f;
       	 }

int main()
	{
	 cout<<"Please enter the integer you want to calculate its factorial:"<<endl;
	 int x;
	 cin>>x;
	 cout<<x<<"!="<<factorial(x)<<endl;
	 return 0;
	}

