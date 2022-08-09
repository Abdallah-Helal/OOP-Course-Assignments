#include <iostream>
using namespace std;

/*************************************class item********************************************/
class Item
{
	int ID;
	string name;
	int quantity;
	float price;
public:
	static int id;  //static counter to make the id of the items
	static void correctID()
	{
		id--;
	}
	Item(); //default constructor
	Item(string name, int quan, int price);     //parametrized constructor
	Item(const Item& item);  //copy constructor
	//setter and getter to items
	void setName(string name);
	void setQuantity(int quantity);
	void setPrice(int price);
	string getName();
	int getQuantity();
	int getPrice();
	int getID();
	//operator overloading for the >> to take the item information
	friend istream& operator>>(istream& is, Item& item);
	//operator overloading for the << to output the item information
	friend ostream& operator<<(ostream& os, const Item& item);
	bool operator==(const Item& item);  //operator overloading for the ==
	Item operator+=(int quantity);  //operator overloading for the +=
	Item operator-=(int quantity);  //operator overloading for the -=

};
/**************************************************************************************/
int Item::id = 0;
Item::Item() :name(""), quantity(0), price(0)
{
}

Item::Item(string name, int quan, int price)
{
	id++;
	ID = id;
	this->name = name;
	quantity = quan;
	this->price = price;
}

Item::Item(const Item& item)
{
	id++;
	ID = id;
	name = item.name;
	quantity = item.quantity;
	price = item.price;
}

void Item::setName(string name)
{
	this->name = name;
	id++;
	ID = id;
}

void Item::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Item::setPrice(int price)
{
	this->price = price;
}

string Item::getName()
{
	return name;
}

int Item::getQuantity()
{
	return quantity;
}

int Item::getPrice()
{
	return price;
}
int Item::getID()
{
	return ID;
}
istream& operator>>(istream& is, Item& item)
{
	is >> item.name >> item.quantity >> item.price;
	return is;

}

ostream& operator<<(ostream& os, const Item& item)
{
	os << endl << "ID: " << item.ID << ", Quantity= " << item.quantity
		<< ", Price= " << item.price << ", name= " << item.name << endl;
	return os;

}

bool Item::operator==(const Item& item)
{
	return name == item.name;
}

Item Item::operator+=(int quantity)
{
	this->quantity = (this->quantity + quantity);
	return *this;
}

Item Item::operator-=(int quantity)
{
	this->quantity = (this->quantity - quantity);
	return *this;
}

/*********************************class seller*********************************************/
class Seller
{
	string name;    //the name and email of the seller
	string email;
	Item* items;    //a dynamic array of items
	int maxItems;   //the max items could be in the seller store
	int counter = 0;
public:

	Seller(string name, string email, int maxitems);    //parametrized constructor
	friend ostream& operator<<(ostream& os, const Seller& it);  //operator overloading for << to print the seller information
	bool addItems(Item& item); //function to add items in the store
	bool sellItems(string name, int quantity); //function that sell the items
	void print(); //function print the information of the items in the store
	Item& findItem(int ID); //function take the ID of an item and return the information of the item if exist
	~Seller(); // destructor to delete the array
};
/***************************** declaration ***********************************/
Seller::Seller(string name, string email, int maxitems)
{
	this->name = name;
	this->email = email;
	maxItems = maxitems;
	items = new Item[maxItems];
}

ostream& operator<<(ostream& os, const Seller& seller)
{
	os << "Name: " << seller.name << " ,email: " << seller.email << endl;
	return os;
}

bool Seller::addItems(Item& item)
{
	bool status = false;

	for (int i = 0; i < counter; i++)
	{
		if (item == items[i])
		{
			items[i] += item.getQuantity();
			status = true;
			item.correctID();
			item.correctID();
			break;
		}
	}
	if (!status && counter < maxItems)
	{
		items[counter] = item;
		counter++;
		status = true;
	}
	return status;
}

bool Seller::sellItems(string  name, int quantity)
{
	bool status = false;

	for (int i = 0; i < counter; i++)
	{
		if (items[i].getName() == name)
		{
			if (quantity <= items[i].getQuantity())
			{
				items[i] -= quantity;
				status = true;
			}
			else
				cout << "There is only {" << items[i].getQuantity() << "} left for this item" << endl;
			break;
		}
	}return status;
}

void Seller::print()
{
	cout << "NAME: " << name << endl
		<< "Email: " << email << endl
		<< "MaxItems: " << maxItems
		<< endl;
	for (int i = 0; i < counter; i++)
		cout << items[i] << endl;
}

Item& Seller::findItem(int ID)
{
	for (int i = 0; i < counter; i++)
	{
		if (items[i].getID() == ID)
		{
			return items[i];
		}
	}
	cout << "there is not any item with this ID" << endl;
}

Seller::~Seller()
{
	delete[] items;
}

/****************************************************************************/
int main()
{
	string name, email;
	int maxNum;
	cout << "Please, Enter your name and your email" << endl;
	cin >> name >> email;
	cout << "Please, Enter the max number of items: ";
	cin >> maxNum;
	Seller sel1(name, email, maxNum);
	while (true)
	{
		int option;
		cout << "Please, choose any number from the following list" << endl
			<< "1. Print My Info" << endl
			<< "2. Add An Item" << endl
			<< "3. Sell An Item" << endl
			<< "4. Print Items" << endl
			<< "5. Find an Item by ID" << endl
			<< "6. Exit" << endl;
		cin >> option;
		// switch to do what user choose
		switch (option) {
		case 1:
			cout << sel1 << endl;
			break;
		case 2:
		{string Name;
		int quantity, price;
		cout << "Enter the name , quantity and price" << endl;
		cin >> Name >> quantity >> price;
		Item item(Name, quantity, price);
		if (!sel1.addItems(item))cout << "there is not enough item" << endl;
		break; }
		case 3:
		{string Name;
		int quantity;
		cout << "Enter the name and quantity " << endl;
		cin >> Name >> quantity;
		sel1.sellItems(Name, quantity);
		break; }
		case 4:
			sel1.print();
			break;
		case 5:
		{int id;
		cout << "Enter the ID" << endl;;
		cin >> id;
		cout << sel1.findItem(id);
		break; }
		default:
			return 0;
		}
	}
	return 0;
}
