#pragma once

#include <iostream>
using std::cout;

template <typename TKey, typename TValue>
class TP_BST
{
	struct TableRec
	{
		TKey key;
		TValue value;
	};
	struct TP_Node
	{
		TableRec data;
		TP_Node* left;
		TP_Node* right;
		TP_Node* parent;
	};
	TP_Node* pRoot; //корень дерева
	void MainPrint(TP_Node* p)
	{
		if (p == nullptr) return;
		std::cout << p->data.key << " - " << p->data.value << " ";
		if (p->left)
		{
			std::cout << " left ";
			MainPrint(p->left);
		}
		if (p->right)
		{
			std::cout << p->data.key << "->right ";
			MainPrint(p->right);
		}
		cout << "\n";
	}
public:
	//Обход
	//Поиск элемента с заданным ключом
	//Добавление нового элемента
	//Удаление элемента	
	//Поиск элемента с минимальным или максимальным ключом
	//Поиск предыдущего или последующего элемент для заданного ключа
	void Print()
	{
		cout << "Table\n";
		MainPrint(pRoot);
	}
	TP_BST()
	{
		pRoot = nullptr;
	}
	TP_Node* Find(TKey key)
	{
		if (!pRoot) return nullptr;
		TP_Node* result = pRoot;
		while(result)
		{
			if (result->data.key > key)
			{
				result = result->left;
			}
			else if (result->data.key < key)
			{
				result = result->right;
			}
			else
			{
				return result;
			}
		}
		return result;
	}
	void Insert(TKey key, TValue value)
	{
		TP_Node* goal = new TP_Node{ key, value };
		TP_Node* result = pRoot;
		while (result)
		{
			if (result->data.key > key)
			{
				if (result->left == nullptr)
				{
					//там должен быть наш чувачок
					result->left = goal;
					goal->parent = result;
					return;
				}
				else result = result->left;
			}
			else if (result->data.key < key)
			{
				if (result->right == nullptr)
				{
					//там должен быть наш чувачок
					result->right = goal;
					goal->parent = result;
					return;
				}
				else result = result->right;
			}
			else
			{
				return;
			}	
		}
		pRoot = goal;
	}
	void Delete(TKey key)
	{
		TP_Node* node_to_delete = Find(key);
		if (!node_to_delete) return; //удаляем того чего нет, удаляем пустоту ура
		if (node_to_delete->left==nullptr&&node_to_delete->right==nullptr)
		{
			//ура у нас лист
			if (node_to_delete->parent->left==node_to_delete)
			{
				node_to_delete->parent->left = nullptr;
			}
			else if (node_to_delete->parent->right == node_to_delete)
			{
				node_to_delete->parent->right = nullptr;
			}
			delete node_to_delete;
		}
		else if (node_to_delete->left == nullptr && node_to_delete->right != nullptr)
		{
			//только правый потомок
			if (node_to_delete->parent->left == node_to_delete)
			{
				node_to_delete->parent->left = node_to_delete->right;
			}
			else if (node_to_delete->parent->right == node_to_delete)
			{
				node_to_delete->parent->right = node_to_delete->right;
			}
			delete node_to_delete;
		}
		else if (node_to_delete->left != nullptr && node_to_delete->right == nullptr)
		{
			//только левый потомок
			if (node_to_delete->parent->left == node_to_delete)
			{
				node_to_delete->parent->left = node_to_delete->left;
			}
			else if (node_to_delete->parent->right == node_to_delete)
			{
				node_to_delete->parent->right = node_to_delete->left;
			}
			delete node_to_delete;
		}
		else if (node_to_delete->left != nullptr && node_to_delete->right != nullptr)
		{
			TP_Node* result_to_swap;
			result_to_swap = node_to_delete->right;
			while(result_to_swap->left != nullptr)
			{
				result_to_swap = result_to_swap->left;
			}
			node_to_delete->data = result_to_swap->data;
			if (result_to_swap->parent->right == result_to_swap)
				result_to_swap->parent->right = nullptr;
			else if (result_to_swap->parent->left == result_to_swap)
				result_to_swap->parent->left = nullptr;
			delete result_to_swap;
		}

	}
};