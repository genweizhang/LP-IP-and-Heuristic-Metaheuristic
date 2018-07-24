#ifndef HASHTABLE_H
#define HASHTABLE_H

# include<iostream>
# include <vector>
# include <string>
# include <list>
# include <algorithm>
using namespace std;


class HashingTable
{
private:
	vector<list<string>> thelists;
	int tablesize=0;
	int hash(const string& key);
public:
	HashingTable();
	HashingTable(int size);
	virtual ~HashingTable();
	void insert(string name);
	bool find(string name);
	void remove(string name);
	void split(int i, int p);
	friend ostream &operator << (ostream &output, HashingTable &ml);
	
};
#endif

ostream &operator << (ostream &output, HashingTable &mh)
{
		for (int j = 0; j < mh.thelists.size(); j++)
		{
			if (!mh.thelists[j].empty())
			{
				for (list<string>::const_iterator it = mh.thelists[j].begin(); it != mh.thelists[j].end(); it++)
				{
					output << *it << "    ";
				}
				output << endl;
			}
		}
		return output;
}
HashingTable::HashingTable()
{

}
HashingTable::HashingTable(int size)
{
		thelists.resize(size);
		int tablesize = thelists.size();
}

HashingTable::~HashingTable()
{
}

int HashingTable::hash(const string& key)
{
		int val = 0;
		val = key[0] - 'A';
		return val;
}

void HashingTable::insert(string name)
{
		int index = hash(name);
		list<string>& linkedlist = thelists[index];
		linkedlist.push_back(name);
}

bool HashingTable::find(string name)
{
		int id = hash(name);
		std::list<string>& whichlist = thelists[id];
		std::list<string>::iterator iter;
		iter = std::find(whichlist.begin(), whichlist.end(), name);
		if (iter != whichlist.end())	return 1;
		else 
			for (int id; id < thelists.size()-1; id++)
			{
				std::list<string>& whichlist = thelists[id+1];
				std::list<string>::iterator iter;
				iter = std::find(whichlist.begin(), whichlist.end(), name);
				if (iter != whichlist.end()) 
				{ 
					return 1; 
					break; 
				}
				
			}
		if (id == thelists.size()-1) return 0;
}

void HashingTable::remove(string name)
{
		int id = hash(name);
		std::list<string>& whichlist = thelists[id];
		whichlist.remove(name);
		thelists[id] = whichlist;
}

void HashingTable::split(int i, int p)
{
		if (i == thelists.size() - 1)
		{
			thelists.resize(i+3);
			if (thelists[i].size() > p)
			{
				int j = thelists[i].size() - p;
				list<string>::reverse_iterator revit;
				for (revit = thelists[i].rbegin(); j > 0;)
				{
					thelists[i + 1].push_front(*revit);
					thelists[i].remove(*revit);
					j--;
				}
				if (thelists[i + 1].size() > p)
				{
					int j = thelists[i + 1].size() - p;
					list<string>::reverse_iterator revit;
					for (revit = thelists[i + 1].rbegin(); j > 0;)
					{
						thelists[i + 2].push_front(*revit);
						thelists[i + 1].remove(*revit);
						j--;
					}
				}
			}
		}

			if (!thelists[i].empty())
			{
				if (thelists[i].size() > p)
				{
					int j = thelists[i].size() - p;
					list<string>::reverse_iterator revit;
					for (revit = thelists[i].rbegin(); j > 0;)
					{
						thelists[i + 1].push_front(*revit);
						thelists[i].remove(*revit);
						j--;

					}
				}
			}

	
}



int main()
{
		char* Names[] = { "Andy B", "Amy Dean", "Antonio G", "Andy Roberts",
							"Brian W","Bob Macy", "Brent James", "Buck Muck",
							"Cannon James", "Cart Wright", "Catherine Zeta", "Carl Lewis",
							"David Johnson", "Dowd Peter", "Daniel Fauchier", "Dawn Smith",
							"Yarda Varda", "Yami Jacob", "Yester Louis", "Yukon Oklahoma",
							"Zandi Rich", "Zea John", "Zelby Leon", "Ziert Paul", "Zanola Helen" };
		HashingTable* myHashTable;
		int i;
		myHashTable = new HashingTable(26);
		for (i = 0; i < 25; i++)
			(*myHashTable).insert(Names[i]);
		cout << "Printing the hash table after inserting...." << endl;
	
		cout << *myHashTable << endl;
	
		if ((*myHashTable).find("Zandi Rich"))
		cout << "Zandi Rich is in the list" << endl;
		else
		cout << "Zandi Rich is not in the list" << endl;
	
		(*myHashTable).remove("Zea John");
		if ((*myHashTable).find("Zea John"))
		cout << "Zea John is in the list" << endl;
		else
		cout << "Zea John is not in the list" << endl;

		cout << "Table after remove 'Zea John' is:"<<endl;
		cout << *myHashTable << endl;
		
		for (i = 0; i < 26; i++)
		{
			(*myHashTable).split(i, 2);
		}
		cout << "Printing the hash table after splitting...." << endl;
		cout << *myHashTable << endl;

		if ((*myHashTable).find("Ziert Paul"))
		cout << "'Ziert Paul' is in the list" << endl;
		else
		cout << "'Ziert Paul' is not in the list" << endl;
		(*myHashTable).insert("Zea John");
		if ((*myHashTable).find("Zea John"))
		cout << "Zea John is in the list" << endl;
		else
		cout << "Zea John is not in the list" << endl;
		delete myHashTable;

		return 0;
}