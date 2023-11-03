/************************************************************************************************************************
Name:  Sharon Nir        Z#: Z23492542
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date:  04/13/2022           Due Time: 11:59 PM
Total Points: 20.00
Assignment #: order_class.cpp

Description:
The point of this program file is to implement the class functions that the actual program will use to test.
*************************************************************************************************************************/

#include "order_class.h"

/************************************************************************************************************************************/
//Name: default constructor
//Precondition: 
//Postcondition: 
//Decription: Reads the data file of purchase order information (cell number, item, quantity, price, and processing plant) into the dynamic array of order records, 
//INV. If the count become equal to the size the function double_size is called and the memory allocated to INV is doubled.
/************************************************************************************************************************************/
order_class::order_class()
{
	count = 0;
	size = 1;

	INV = new order_record[size];

	ifstream in;
	in.open("purchase_data_Assignment11.txt");

	if (in.fail())
	{
		cout << "Could not access file.";
	}

	while (!in.eof())
	{
		if (is_full())
		{
			double_size();
		}

		in >> INV[count].cell_number
			>> INV[count].item_number
			>> INV[count].quantity
			>> INV[count].price
			>> INV[count].processing_plant;

		count++;
	}

	--count;
	in.close();

	cout << "The default constructor has been called\n";
}

/***********************************************************************************************************************************/
//Name: is_Empty
//Precondition: 
//Postcondition: 
//Decription: returns true if INV is empty
/**********************************************************************************************************************************/
bool order_class::is_Empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: 
//Postcondition: 
//Decription: returns true if INV is full
/*********************************************************************************************************************************/
bool order_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: 
//Postcondition: 
//Decription: locates key in INV if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int order_class::search(const string key)
{
	loc = -1;

	for (int i = 0; i <= count; i++)
	{
		if (INV[i].cell_number == key)
		{
			loc = i;

			return loc;

			break;
		}
	}

	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: 
//Postcondition: 
//Decription: adds a call_record to INV; if INV is full, double_size is called to increase the size of INV. The user 
//            is prompted to enter the cell number, item, quantity, price, and processing plant.
/********************************************************************************************************************************/
void order_class::add()
{
	count += 1;

	if (is_full())
	{
		double_size();
	}

	cout << "Enter a cell number: ";
	cin >> INV[count].cell_number;

	cout << "Enter a item number: ";
	cin >> INV[count].item_number;

	cout << "Enter the quantity: ";
	cin >> INV[count].quantity;

	cout << "Enter the price: ";
	cin >> INV[count].price;

	cout << "Enter a processing plant: ";
	cin >> INV[count].processing_plant;

	process();
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: 
//Postcondition: 
//Decription: doubles the size (capacity) of INV
/******************************************************************************************************************************/
void order_class::double_size()
{
	size *= 2;
	order_record* temp = new order_record[size];

	for (int i = 0; i < count; i++)
	{
		temp[i] = INV[i];
	}

	delete[] INV;
	INV = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: 
//Postcondition: 
//Decription: calculate the tax rate, order tax, net cost, total order cost for every call record in INV.
/*****************************************************************************************************************************/
void order_class::process()
{
	for (int i = 0; i <= count; i++)
	{
		if (INV[i].processing_plant >= 0 && INV[i].processing_plant <= 50)
		{
			INV[i].tax_rate = 6;
		}
		else if (INV[i].processing_plant >= 51 && INV[i].processing_plant <= 110)
		{
			INV[i].tax_rate = 7;
		}
		else if (INV[i].processing_plant >= 111 && INV[i].processing_plant <= 200)
		{
			INV[i].tax_rate = 8;
		}
		else if (INV[i].processing_plant >= 201 && INV[i].processing_plant <= 500)
		{
			INV[i].tax_rate = 9;
		}
		else if (INV[i].processing_plant > 500)
		{
			INV[i].tax_rate = 11;
		}

		INV[i].order_tax = (INV[i].quantity * INV[i].price) * (INV[i].tax_rate / 100);

		INV[i].net_cost = INV[i].quantity * INV[i].price;

		INV[i].total_cost = INV[i].net_cost + INV[i].order_tax;
	}
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: 
//Postcondition: 
//Decription: de-allocates all memory allocated to INV.  This will be the last function to be called (automatically by the compiler)
//before the program is exited.
/***************************************************************************************************************************/
order_class::~order_class()
{
	delete[] INV;
	cout << "The destructor has been called\n";
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: 
//Postcondition: 
//Decription: removes all order records in INV with a cell number field that matches key, if it is there. Chain was
//            implemented.
/*******************************************************************************************************************************/
order_class& order_class::operator-(const string key) //removes an item from the list
{
	loc = -1;

	loc = search(key);

	while (loc != -1)
	{
		for (int i = loc; i <= count; i++)
		{
			INV[i] = INV[i + 1];
		}

		count--;

		loc = search(key);
	}

	return *this;
}

/****************************************************************************************************************************/
//Name: operator<<
//Precondition: 
//Postcondition: 
//Decription: prints every field of every call_record in INV formatted to the screen.
/***************************************************************************************************************************/
ostream& operator<<(ostream& out, order_class& Org) //prints all the elements in INV to the screen
{
	ofstream fileOut;
	fileOut.open("purchase11_results.txt");

	for (int i = 0; i <= Org.count; i++)
	{
		fileOut << setprecision(2) << fixed << right
			<< setw(10) << Org.INV[i].cell_number
			<< setw(10) << Org.INV[i].item_number
			<< setw(10) << Org.INV[i].quantity
			<< setw(10) << Org.INV[i].price
			<< setw(10) << Org.INV[i].processing_plant
			<< setw(10) << Org.INV[i].tax_rate
			<< setw(10) << Org.INV[i].order_tax
			<< setw(10) << Org.INV[i].net_cost
			<< setw(10) << Org.INV[i].total_cost << endl;

		out << setprecision(2) << fixed << right
			<< setw(10) << Org.INV[i].cell_number
			<< setw(10) << Org.INV[i].item_number
			<< setw(10) << Org.INV[i].quantity
			<< setw(10) << Org.INV[i].price
			<< setw(10) << Org.INV[i].processing_plant
			<< setw(10) << Org.INV[i].tax_rate
			<< setw(10) << Org.INV[i].order_tax
			<< setw(10) << Org.INV[i].net_cost
			<< setw(10) << Org.INV[i].total_cost << endl;
	}

	fileOut.close();

	return out;
}