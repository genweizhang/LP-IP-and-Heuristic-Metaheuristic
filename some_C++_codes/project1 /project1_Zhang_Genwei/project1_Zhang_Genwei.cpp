#include <iostream>
using namespace std;

class Item														// create Item class.
{
private:
																// protected field.
public:
	Item();														// default and empty constructor.
	Item(char [8],int, int, int, int, double, 
		 double, double,double, double, int, bool,int);			// non-default constructor, initializing.
	void display();												// display the data informaton.
	virtual ~Item();											// destructor.
	
	int Code, Color, Brand, Type, Attr11;						// define common identifiers.
	double H, L, W, Wt, Price;
	bool Attr10;
};

Item::Item(){}

Item::Item(char command[8], int quantity,int code, int color, int brand, double h, double l, double w, double wt,
	double price, int type, bool attr10, int attr11)
{							
	Code = code;
	Color = color;
	Brand = brand;
	H = h;
	L = l;
	W = w;
	Wt = wt;
	Price = price;
	Type = type;
	Attr10 = attr10;
	Attr11 = attr11;					// Class Item: transfering all the local vrialbles to common variables.
}

void Item::display()
{										// Display method prints out each line stored in the Bag array.
	cout<< "The item attribute (including code) stored in the Bag array is:" << " "<<Code << " " <<Color << " " <<Brand << " " << H<< " "
		<< L<< " " << W << " " << Wt << " " << Price << " " << Type << " " << Attr10 << " " << Attr11 << " " << endl;
}

Item::~Item()
{
	cout << "Item object was destroyed!!!" << endl;
}

class Pens : public Item				// Define class Pens, which inherit Item class.
{
private:
	int packetsize;

public:
	Pens(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
		double price, int type, bool attr10, int attr11);								 // non-default constructor, initializing.
	virtual ~Pens();																	 // default destructor.
};
Pens::Pens(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
	double price, int type, bool attr10, int attr11)
{
	Code = code;
	Color = color;
	Brand = brand;
	H = h;
	L = l;
	W = w;
	Wt = wt;
	Price = price;
	Type = type;
	Attr10 = attr10;
	Attr11 = attr11;					// Transfering all the local vrialbles to common variables.
}
Pens::~Pens()
{
	cout << "The pen object was destroyed!" << endl;
}
class Printer : public Item				// Define class Printer, which inherit Item class.
{
private:
	int traycapacity;

public:
	Printer(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
			double price, int type, bool attr10, int attr11);                    // Non-default printer constructor.
	virtual ~Printer();															 // Default printer destructor.

};
Printer::Printer(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
	double price, int type, bool attr10, int attr11)
{
	Code = code;
	Color = color;
	Brand = brand;
	H = h;
	L = l;
	W = w;
	Wt = wt;
	Price = price;
	Type = type;
	Attr10 = attr10;
	Attr11 = attr11;					// Transfering all the local vrialbles to common variables.
}
Printer::~Printer()
{
	cout << "The printer object was destroyed!" << endl;
}

class SafeBox : public Item				// Define class SafeBox, which inherit Item class.
{
private:
	bool electroniclock;

public:
	SafeBox(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
		double price, int type, bool attr10, int attr11);						// Non-default safebox constructor.
	virtual ~SafeBox();														    // Default safebox destructor.
};
SafeBox::SafeBox(char command[8], int quantity, int code, int color, int brand, double h, double l, double w, double wt,
	double price, int type, bool attr10, int attr11)
{
	Code = code;
	Color = color;
	Brand = brand;
	H = h;
	L = l;
	W = w;
	Wt = wt;
	Price = price;
	Type = type;
	Attr10 = attr10;
	Attr11 = attr11;					// Transfering all the local vrialbles to common variables.
}
SafeBox::~SafeBox()
{
	cout << "Then safebox object was destroyed!" << endl;
}


int main()
{
	Item* Bag[250];						// Create an Item class Bag array, which can hold up to 250 pointers.
	Pens* onePen;
	Printer* onePrinter;
	SafeBox* oneSafebox;
										// Define local variables.
	char command[8];
	int quantity, code, color, brand, type, attr11;
	double h, l, w, wt, price;
	bool attr10;
	
	int index = 0;						// Initialize line number index.
	
	while (!cin.eof())					//while end of line is not reached.
	{	
		// Redirected input to read input file using standard cin. 
		std::cin >> command >> quantity >> code >> color >> brand >> h >> l >> w >> wt >>price >> type >>attr10 >> attr11;
		
		// Print out each line after read in from input file.
		cout << "The current line read from file is:" <<" "<< command << " " << quantity << " " << code << " " << color << " " << brand << " " 
			 <<h << " " <<l << " " << w<< " " << wt<<" " << price <<" "<<type << " " << attr10 << " " << attr11 << " " << endl;
		
		// Switch code and store each item into Bag array based on quantity numbers.
		for (int i = 0; i < quantity; i++)
		{
			switch (code)
			{
				case 1: { //Pen
						Bag[index++] = new Pens(command, quantity, code, color, brand, h, l, w,
											wt, price, type, attr10,attr11);
						break;
				}
				case 2: { // Printer
						Bag[index++] = new Printer(command, quantity,code, color, brand, h, l, w, 
													wt, price, type, attr10, attr11);
						break;
				}
				case 3: { // Safebox
						Bag[index++] = new SafeBox(command, quantity,code, color, brand, h, l, w, 
													wt, price, type, attr10, attr11);
						break;
				}
				default: {
						cout << "I do not recognize this item based on its code!" << endl;
						break;
				}
			}
		}
	
	}

		cout << "Total number of lines stored in the bag is: "<<index-1 << endl;	// Since "while (!cin.eof()){}" by default read the last line twice, 
																					// so we need to subtract 1 from returned index.
		
		int numberpen = 0;							// Define local variables for printing out the summary info. of the items from Bag array.
		int numberprinter = 0;
		int numbersafebox = 0;
		double pentotalprice=0;
		double printertotalprice = 0;
		double safeboxtotalprice = 0;
		double allitemtotalprice = 0;
	
	for (int i = 0; i < index-1; i++)	
	{
		switch ((*Bag[i]).Code) {
		
			case 1: {   //Pens
					(static_cast<Pens*>(Bag[i]))->display();
					pentotalprice = pentotalprice + (*Bag[i]).Price;
					numberpen++;
					break;
					}
			case 2: {  //Printers
					(static_cast<Printer*>(Bag[i]))->display();
					printertotalprice = printertotalprice + (*Bag[i]).Price;
					numberprinter++;
					break;
					}
			case 3: {  //Safe Box
					(static_cast<SafeBox*>(Bag[i]))->display();
					safeboxtotalprice = safeboxtotalprice + (*Bag[i]).Price;
					numbersafebox++;
					break;
					}
			default: cout << "I do not recognize this Item in the Bag" << endl;
		}
	}
		allitemtotalprice = pentotalprice+ printertotalprice +safeboxtotalprice;
		cout << "The number of pen items is: " << numberpen << endl;
		cout << "The number of printer items is: " << numberprinter << endl;
		cout << "The number of safe box items is: " << numbersafebox << endl;
		cout << "The total price of pen items is: " << pentotalprice << endl;
		cout << "The total price of pinter items is: " << printertotalprice << endl;
		cout << "The total price of safebox items is: " << safeboxtotalprice << endl;
		cout << "The total price of all items is: " << allitemtotalprice << endl;
	
	return 0;
}

