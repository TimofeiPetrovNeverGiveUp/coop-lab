#pragma once
#include <vector>
#include <functional>
#include <utility>
#include <iostream>
//index = hash % the_size

template <typename TKey, typename TValue>
class HashTableOpen 
{
private:
	int the_p; //for PROBIROVANIE
	double the_stop; //parametr
	struct HashTableRec
	{
		TKey Key{};
		TValue Value{};
		int state = 0;
		//0 - empty
		//1 - occypied
		//-1 - deleted
	};
	int the_size = 0;
	int the_count = 0; //count of elements we have
	HashTableRec* the_table;
	void ReHash()
	{
		int old_size = the_size;
		the_size *= 2; //the_size * 2
		HashTableRec* the_table2 = new HashTableRec[the_size];
		the_count = 0;
		for (int i = 0; i < old_size; ++i)
		{
			if (the_table[i].state == 1)
			{
				TheInsert(the_table[i].Key, the_table[i].Value, the_table2, false);
			}
		}
		delete[] the_table;
		the_table = the_table2;
	}
	void TheInsert(TKey key, TValue value, HashTableRec* where, bool helpy)
	{
		int index = 0;
		//uses linear PROBIROVANIE
		for (int i = 0; i < the_size; ++i)
		{
			index = (std::hash<TKey>{}(key)+i * the_p) % the_size;
			if (where[index].state <= 0)
			{
				where[index].Value = value;
				where[index].Key = key;
				where[index].state = 1;
				the_count++;
				return;
			}
			else if (where[index].state == 1 && key == where[index].Key)
			{
				where[index].Value = value;
				return;
			}
		}
		if ((the_count / (the_size * 1.0)) > the_stop && helpy)
		{
			ReHash();
		}
	}
public:
	HashTableOpen(int the_size1, int the_p1=1, double the_stop1=0.7)
	{
		the_stop = the_stop1;
		the_p = the_p1;
		the_size = the_size1;
		the_table = new HashTableRec[the_size1];
	}
	~HashTableOpen()
	{
		delete[] the_table;
	}
	std::pair<TValue,bool> Find(TKey key)
	{
		int index = 0;
		std::pair<TValue, bool> result;
		//uses linear PROBIROVANIE
		for (int i = 0; i < the_size; ++i)
		{
			index = (std::hash<TKey>{}(key)+i*the_p) % the_size;
			if (the_table[index].state == 0)
			{
				result.first = TValue{};
				result.second = false;
				return result;
				//there is no such key in table it would be default
			}
			else if (the_table[index].state == 1 && the_table[index].Key == key)
			{
				result.first = the_table[index].Value;
				result.second = true;
				return result;
			}
		}
		result.first = TValue{};
		result.second = false;
		return result;
		//there is no such key in table it would be default
	}
	void Insert(TKey key, TValue value)
	{
		TheInsert(key, value, the_table, true);
	}
	void Delete(TKey key)
	{
		int index = 0;
		//uses linear PROBIROVANIE
		for (int i = 0; i < the_size; ++i)
		{
			index = (std::hash<TKey>{}(key) + i * the_p) % the_size;
			if (the_table[index].state == 1 && the_table[index].Key == key)
			{
				the_table[index].state = -1;
				the_table[index].Key = TKey{};
				the_table[index].Value = TValue{};
				the_count--;
				return;
			}
		}
	}
	int GetSize() 
	{
		return the_size;
	}
	void Print()
	{
		for(int i = 0; i < the_size; ++i)
		{
			std::cout << "\n" <<the_table[i].Key << " " << the_table[i].Value << "\n";
		}
	}
};
