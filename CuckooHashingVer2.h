#pragma once
#include <utility>
#include <functional>
#include <iostream>


//Cuckoo Hash Requiem

template <typename TKey, typename TValue>
class CuckooVer2
{
private:
	//structs
	struct HashTableRec
	{
		TKey Key{};
		TValue Value{};
		int State = 0;
		//0 - empty
		//1 - occypied
		//-152 -special code, we need insert after rehash
	};
	//structs

	//variables
	HashTableRec* the_table;
	int iters_count = 0;
	int the_size = 0;
	int the_insert_index_total = 0;
	//variables

	//hash functions
	size_t h1index(TKey key) //get_index
	{
		return std::hash<TKey>{}(key) % the_size;
	}
	size_t h2index(TKey key) //get_index
	{
		//return (std::hash<TKey>{}(key) * 1000003 + 3) % the_size;
		//return (key * 0x9e3779b9) % the_size; //только для INT
		return (std::hash<TKey>{}(key) * 0x9e3779b9) % the_size;
	}
	//hash functions

	//private functions
	HashTableRec Insert(TKey key, TValue value, int last_hash_used, HashTableRec* where, bool helpy)
	{
		HashTableRec ret;
		the_insert_index_total++;
		if ((iters_count >= the_size - 1) && helpy)// than we got цикл
		{
			ReHash();
			ret.Key = key;
			ret.Value = value;
			ret.State = -152;
			return ret;
		}
		if ((iters_count >= the_size - 1) && !helpy)// than we got цикл
		{
			std::cout << "REHASH DIDNT HELP!!!\n";
			ret.Key = key;
			ret.Value = value;
			ret.State = -154;
			return ret;
		}
		size_t index1 = h1index(key);
		size_t index2 = h2index(key);
		if ((where[index1].State == 0 && last_hash_used != 0) || (where[index1].Key == key && last_hash_used != 0))
		{
			where[index1].Key = key;
			where[index1].Value = value;
			where[index1].State = 1;
			return ret;
		}
		else if ((where[index2].State == 0 && last_hash_used != 1) || (where[index2].Key == key && last_hash_used != 1))
		{
			where[index2].Key = key;
			where[index2].Value = value;
			where[index2].State = 1;
			return ret;
		}
		else
		{
			int indexes[2];
			indexes[0] = index1;
			indexes[1] = index2;
			last_hash_used = the_insert_index_total % 2;
			int index_get_out = indexes[last_hash_used];
			iters_count++;
			HashTableRec get_out = where[index_get_out];
			where[index_get_out].Key = key;
			where[index_get_out].Value = value;
			ret = Insert(get_out.Key, get_out.Value, last_hash_used, where, helpy);
			return ret;
		}
	}
	void ReHash()
	{
		HashTableRec ret;
		ret.State = -154;
		int old_size = the_size;
		while (ret.State == -154)
		{
			std::cout << "REHASH \n";
			//changing parametrs
			the_size *= 2; //the_size * 2
			//changing parametrs
			//local
			HashTableRec* the_table2 = new HashTableRec[the_size];
			//local
			for (int i = 0; i < old_size; ++i)
			{
				if (the_table[i].State == 1)
				{
					iters_count = 0;
					ret = Insert(the_table[i].Key, the_table[i].Value, -1, the_table2, false);
					if (ret.State == -154) continue;
				}
			}
			delete[] the_table;
			the_table = the_table2;
		}
	}
	//private functions
public:
	//constructors
	CuckooVer2(int the_size1)
	{
		the_size = the_size1;
		the_table = new HashTableRec[the_size1];
	}
	~CuckooVer2()
	{
		delete[] the_table;
	}
	//constructors
	//public functions
	void UserInsert(TKey key, TValue value)
	{
		iters_count = 0;
		HashTableRec ret = Insert(key, value, -1, the_table, true);
		while (ret.State == -152)
		{
			iters_count = 0;
			ret = Insert(ret.Key, ret.Value, -1, the_table, true);
		}
	}
	//public functions
	void Print()
	{
		for (int i = 0; i < the_size; ++i)
		{
			std::cout << "\n" << the_table[i].Key << " " << the_table[i].Value << " " << the_table[i].State << " " << "\n";
		}
	}
	int GetSize()
	{
		return the_size;
	}
	std::pair<TValue, bool> Find(TKey key)
	{
		std::pair<TValue, bool> result;
		size_t index1 = h1index(key);
		size_t index2 = h2index(key);
		if (the_table[index1].State == 1 && the_table[index1].Key == key)
		{
			result.first = the_table[index1].Value;
			result.second = true;
		}
		else if (the_table[index2].State == 1 && the_table[index2].Key == key)
		{
			result.first = the_table[index2].Value;
			result.second = true;
		}
		else
		{
			result.first = TValue{};
			result.second = false;
		}
		return result;
	}
	void Delete(TKey key)
	{
		size_t index1 = h1index(key);
		size_t index2 = h2index(key);
		if (the_table[index1].State == 1 && the_table[index1].Key == key)
		{
			the_table[index1].Key = TKey{};
			the_table[index1].Value = TValue{};
			the_table[index1].State = 0;
			return;
		}
		else if (the_table[index2].State == 1 && the_table[index2].Key == key)
		{
			the_table[index2].Key = TKey{};
			the_table[index2].Value = TValue{};
			the_table[index2].State = 0;
			return;
		}
		return;
	}
};

