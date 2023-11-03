/************************************************************************************************************************
Name:  Sharon Nir        Z#: Z23492542
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date:  04/13/2022           Due Time: 11:59 PM
Total Points: 20.00
Assignment #: order_class.h

Description:
The point of this program file is to declare the classes that the program is going to use and implement it in another cpp
file.
*************************************************************************************************************************/

#pragma once
#include <iostream>
#include<string>
#include <fstream>
#include <iomanip>

using namespace std;

class order_record
{
public:
	string cell_number;
	string item_number;
	double quantity;
	double price;
	int processing_plant;
	double tax_rate;
	double order_tax;
	double net_cost;
	double total_cost;
};

class order_class
{
public:
	order_class();
	~order_class(); //de-allocates all memory allocate to INV by operator new.
	bool is_Empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item is in INV; otherwise return -1
	void add(); //adds a order record to INV
	order_class& operator-(const string key); //removes all items in INV with a cell number that matches key.
	void double_size();
	void process();
	friend ostream& operator<<(ostream& out, order_class& Org); //prints all the elements in INV to the screen
private:
	int count;
	int size;
	int loc;
	order_record* INV;
};