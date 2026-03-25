#pragma once
#include "NodeAndRec.h"
#include <iostream>
using std::cout;

template <typename TKey, typename TValue>
class TP_BST
{
protected:
	Node<TKey, TValue>* pRoot = nullptr; //корень дерева bst
	//вывод
	void MainPrint(Node<TKey, TValue>* p)
	{
		if (p == nullptr) return;
		//<< " - " << p->data.value
		std::cout << p->color << p->data.key << " ";
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
	void Print()
	{
		cout << "Table\n";
		MainPrint(pRoot);
	}
	TP_BST()
	{
		pRoot = nullptr;
	}
	~TP_BST()
	{
		pRoot = nullptr;
		delete pRoot;
	}
	Node<TKey, TValue>* Find(TKey key)
	{
		if (!pRoot) return nullptr;
		Node<TKey, TValue>* result = pRoot;
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
	virtual void Insert(TKey key, TValue value)
	{
		Node<TKey, TValue>* goal = new Node<TKey, TValue>;
		goal->data.key = key;
		goal->data.value = value;
		Node<TKey, TValue>* result = pRoot;
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
	virtual void Delete(TKey key)
	{
		Node<TKey, TValue>* node_to_delete = Find(key);
		if (!node_to_delete) return; //удаляем того чего нет, удаляем пустоту ура
		if (node_to_delete == pRoot)
		{
			pRoot = nullptr;
			return;
		}
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
				node_to_delete->right->parent = node_to_delete->parent;
			}
			else if (node_to_delete->parent->right == node_to_delete)
			{
				node_to_delete->parent->right = node_to_delete->right;
				node_to_delete->right->parent = node_to_delete->parent;
			}
			delete node_to_delete;
		}
		else if (node_to_delete->left != nullptr && node_to_delete->right == nullptr)
		{
			//только левый потомок
			if (node_to_delete->parent->left == node_to_delete)
			{
				node_to_delete->parent->left = node_to_delete->left;
				node_to_delete->left->parent = node_to_delete->parent;
			}
			else if (node_to_delete->parent->right == node_to_delete)
			{
				node_to_delete->parent->right = node_to_delete->left;
				node_to_delete->left->parent = node_to_delete->parent;
			}
			delete node_to_delete;
		}
		else if (node_to_delete->left != nullptr && node_to_delete->right != nullptr)
		{
			Node<TKey, TValue>* result_to_swap;
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