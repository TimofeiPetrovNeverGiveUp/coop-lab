#pragma once

#include "BST.h"
#include <iostream>
#include "NodeAndRec.h"

using std::cout;

template <typename TKey, typename TValue>
class RBT : public TP_BST<TKey, TValue>
{
private:
	void simple_rotate_left(Node<TKey, TValue>* N, Node<TKey, TValue>* P, Node<TKey, TValue>* G, Node<TKey, TValue>* U)
	{
		P->color = 'B';
		G->color = 'R';
		Node<TKey, TValue>* T1 = P->right;
		if (G->parent) 
		{
			Node<TKey, TValue>* Z = G->parent;
			if (Z->left == G)
			{
				Z->left = P;
				P->parent = Z;
				G->parent = P;
				G->left = T1;
				P->right = G;
				if(T1)
					T1->parent = G;
			}
			else 
			{
				Z->right = P;
				P->parent = Z;
				G->parent = P;
				G->left = T1;
				P->right = G;
				if(T1)
				T1->parent = G;
			}
		}
		else 
		{
			G->parent = P;
			G->left = T1;
			P->right = G;
			if(T1)
			T1->parent = G;
			pRoot = P;
			P->parent = nullptr;
		}
	}
	void simple_rotate_right(Node<TKey, TValue>* N, Node<TKey, TValue>* P, Node<TKey, TValue>* G, Node<TKey, TValue>* U)
	{
		P->color = 'B';
		G->color = 'R';
		Node<TKey, TValue>* T1 = P->left;
		if (G->parent)
		{
			Node<TKey, TValue>* Z = G->parent;
			if (Z->left == G)
			{
				Z->left = P;
				P->parent = Z;
				G->parent = P;
				G->right = T1;
				P->left = G;
				if (T1)
					T1->parent = G;
			}
			else
			{
				Z->right = P;
				P->parent = Z;
				G->parent = P;
				G->right = T1;
				P->left = G;
				if (T1)
					T1->parent = G;
			}
		}
		else
		{
			G->parent = P;
			G->right = T1;
			P->left = G;
			if (T1)
				T1->parent = G;
			pRoot = P;
			P->parent = nullptr;
		}
	}
	void tree_check(Node<TKey, TValue>* node_to_check)
	{
		Node<TKey, TValue>* father = node_to_check->parent;
		Node<TKey, TValue>* uncle = nullptr;
		Node<TKey, TValue>* grandfather = nullptr;
		if (father)
		grandfather = father->parent;
		if (grandfather && grandfather->left == father)
		{
			uncle = grandfather->right;
		}
		else if (grandfather)
		{
			uncle = grandfather->left;
		}
		if (father && father->color == 'B')
		{
			return;
		}
		else
		{
			if (uncle && uncle->color == 'R')
			{
				father->color = 'B';
				uncle->color = 'B';
				grandfather->color = 'R';
				if (grandfather)
				tree_check(grandfather);
			}
			else
			{
				if (grandfather && grandfather->left == father && father->left == node_to_check)
				{
					//left left
					simple_rotate_left(node_to_check, father, grandfather, uncle);
				}
				else if (grandfather && grandfather->right == father && father->right == node_to_check)
				{
					//right right
					simple_rotate_right(node_to_check, father, grandfather, uncle);
				}
				else if (grandfather && grandfather->left == father && father->right == node_to_check)
				{
					grandfather->left = node_to_check;
					node_to_check->parent = grandfather;
					father->right = node_to_check->left;
					if (father->right) father->right->parent = father;
					father->parent = node_to_check;
					node_to_check->left = father;
					//мини поворот, свели задачу к предыдущей
					// left left
					simple_rotate_left(father, node_to_check, grandfather, uncle);

				}
				else if (grandfather && grandfather->right == father && father->left == node_to_check)
				{
					grandfather->right = node_to_check;
					node_to_check->parent = grandfather;
					father->left = node_to_check->right;
					if (father->left) father->left->parent = father;
					father->parent = node_to_check;
					node_to_check->right = father;
					//мини поворот, свели задачу к предыдущей
					//right right
					simple_rotate_right(father, node_to_check, grandfather, uncle);
				}
			}
		}
		pRoot->color = 'B';
	}
	void re_balance(Node<TKey, TValue>* P, Node<TKey, TValue>* B)
	{
		if (!B) //брата нет, проблема уходит вверх
		{
			if (P && P->parent)
			{
				Node<TKey, TValue>* new_P = P->parent;
				Node<TKey, TValue>* new_B;
				if (new_P->left == P) new_B = new_P->right;
				else new_B = new_P->left;
				re_balance(new_P, new_B);
			}
			return;
		}
		if (B)
		{
			if (P->color == 'R') 
			{
				if (B->color == 'B') 
				{
					if (B->left && B->left->color=='R') //6.1
					{
						Node<TKey, TValue>* C = B->left;
						Node<TKey, TValue>* Z = P->parent;
						if (Z)
						{
							C->parent = Z;
							if (Z->left == P)
							{
								Z->left = C;
							}
							else
							{
								Z->right = C;
							}
						}
						//родитель изменился но детей не бросили
						if (C->right)
						{
							B->left = C->right;
							C->right->parent = B;
						}
						if (C->left)
						{
							P->right = C->left;
							C->left->parent = P;
						}
						C->left = P;
						P->parent = C;
						C->right = B;
						B->parent = C;
					}
					else if (B->right && B->right->color=='R') //6.1
					{
						//с правый потомк B тяжело
						//ПРОВЕРИТЬ
						Node<TKey, TValue>* C = B->right;
						Node<TKey, TValue>* Z = P->parent;
						if (Z)
						{
							C->parent = Z;
							if (Z->left == P)
							{
								Z->left = C;
							}
							else
							{
								Z->right = C;
							}
						}
						else
						{
							pRoot = C;
							C->parent = nullptr;
						}
						if (C->left)
						{
							B->right = C->left;
							C->left->parent = B;
						}
						if (C->right)
						{
							P->left = C->right;
							C->right->parent = P;
						}
						C->right = P;
						P->parent = C;
						C->left = B;
						B->parent = C;
						C->color = 'B';
						P->color = 'R';
					}
					else if ((!B->right || B->right->color == 'B') && (!B->left || B->left->color == 'B')) //6.2
					{
						P->color = 'B';
						B->color = 'R';
					}
				}
			}
			else //P->color=='B', True
			{
				if (B->color == 'R')
				{
					if (B->left && B->left->color == 'B') 
					{
						if (B->left->left && B->left->left->color == 'R')//6.3(1)
						{
							//то же что и в 6.3(2), только поменяли местами P, D
							Node<TKey, TValue>* C = B->left;
							Node<TKey, TValue>* D = B->left->left;
							Node<TKey, TValue>* T1 = C->right;
							Node<TKey, TValue>* Z = P->parent;
							if (Z)
							{
								C->parent = Z;
								if (Z->left == P)
								{
									Z->left = C;
								}
								else
								{
									Z->right = C;
								}
							}
							//чертовщина
							C->left = D;
							D->parent = C;
							C->right = B;
							B->parent = C;
							B->left = P;
							P->parent = B;
							P->right = T1;
							T1->parent = P;
							//перекрашивать не надо вроде
						}
						else if (B->left->right && B->left->right->color == 'R')//6.3(2)
						{
							Node<TKey, TValue>* D = B->left->right;
							Node<TKey, TValue>* C = B->left;
							Node<TKey, TValue>* T1 = C->left;
							Node<TKey, TValue>* Z = P->parent;
							if (Z)
							{
								C->parent = Z;
								if (Z->left == P)
								{
									Z->left = C;
								}
								else
								{
									Z->right = C;
								}
							}
							//чертовщина
							C->left = P;
							P->parent = C;
							P->right = T1;
							T1->parent = P;
							C->right = B;
							B->parent = C;
							B->left = D;
							D->parent = B;
							D->color = 'B';
						}
						else if (B->left->left && B->left->right && B->left->left->color=='B' && B->left->right->color=='B')//6.4
						{
							Node<TKey, TValue>* C = B->left;
							Node<TKey, TValue>* D = C->right;
							Node<TKey, TValue>* C1L = C->left;
							Node<TKey, TValue>* D1L = D->left;
							Node<TKey, TValue>* D2R = D->right;
							C->color = 'R';
							B->color = 'R';
							P->color = 'B';

						}
					}
					else if (B->right && B->right->color == 'B')
					{
						if (B->right->left && B->right->left->color == 'R')//6.3(3)
						{
							//ПРОВЕРИТЬ
							Node<TKey, TValue>* C = B->right;
							Node<TKey, TValue>* D = C->left;
							Node<TKey, TValue>* Z = P->parent;
							if (Z)
							{
								D->parent = Z;
								if (Z->left == P) Z->left = D;
								else Z->right = D;
							}
							else
							{
								pRoot = D;
								D->parent = nullptr;
							}
							C->left = D->right;
							if (D->right) D->right->parent = C;
							B->right = D->left;
							if (D->left) D->left->parent = B;
							D->left = B;
							B->parent = D;
							D->right = C;
							C->parent = D;
							D->color = 'B';
						}
						if (B->right->right && B->right->right->color == 'R')//6.3(4)
						{
							//ПРОВЕРИТЬ
							Node<TKey, TValue>* C = B->right->right;
							Node<TKey, TValue>* Z = P->parent;
							if (Z)
							{
								C->parent = Z;
								if (Z->left == P) Z->left = C;
								else Z->right = C;
							}
							else
							{
								pRoot = C;
								C->parent = nullptr;
							}
							B->right = C->left;
							if (C->left) C->left->parent = B;
							C->left = B;
							B->parent = C;
							P->left = nullptr;
							P->parent = C;
							C->right = P;
							C->color = 'B';
						}
						else if (B->right->left && B->right->right && B->right->left->color == 'B' && B->right->right->color == 'B')//6.4
						{
							//ПРОВЕРИТЬ
							B->right->color = 'R';
							B->color = 'R';
							P->color = 'B';
						}
					}
				}
				else
				{
					if (B->left && B->left->color == 'R') //6.5
					{
						//ПРОВЕРИТЬ
						Node<TKey, TValue>* C = B->left;
						Node<TKey, TValue>* Z = P->parent;
						if (Z)
						{
							C->parent = Z;
							if (Z->left == P) Z->left = C;
							else Z->right = C;
						}
						else
						{
							pRoot = C;
							C->parent = nullptr;
						}
						B->left = C->right;
						if (C->right) C->right->parent = B;
						C->right = B;
						B->parent = C;
						C->color = 'B';
						B->color = 'R';
					}
					else if (B->right && B->right->color == 'R') //6.5
					{
						//ПРОВЕРИТЬ
						Node<TKey, TValue>* C = B->right;
						Node<TKey, TValue>* Z = P->parent;
						if (Z)
						{
							C->parent = Z;
							if (Z->left == P) Z->left = C;
							else Z->right = C;
						}
						else
						{
							pRoot = C;
							C->parent = nullptr;
						}
						B->right = C->left;
						if (C->left) C->left->parent = B;
						C->left = B;
						B->parent = C;
						C->color = 'B';
						B->color = 'R';
					}
					else if (B->left && B->right && B->left->color == 'B' && B->right->color == 'B') //6.6
					{
						//ПРОВЕРИТЬ
						B->color = 'R';
						if (P->parent)
						{
							Node<TKey, TValue>* new_P = P->parent;
							Node<TKey, TValue>* new_B;
							if (new_P->left == P)
							{
								new_B = new_P->right;
							}
							else
							{
								new_B = new_P->left;
							}
							re_balance(new_P, new_B);	
						}
					}
				}
			}
		}
	}
	using TP_BST<TKey, TValue>::pRoot;
public:
	void Insert(TKey key, TValue value) override
	{
		Node<TKey, TValue>* goal = new Node<TKey, TValue>;
		goal->data.key = key;
		goal->data.value = value;
		goal->color = 'R';
		if (!pRoot)
		{
			pRoot = goal;
			pRoot->color = 'B';
			return;
		}
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
					tree_check(goal);
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
					tree_check(goal);
					return;
				}
				else result = result->right;
			}
			else
			{
				return;
			}
		}
	}
	void Delete(TKey key) override
	{
		Node<TKey, TValue>* node_to_delete = TP_BST<TKey, TValue>::Find(key);
		if (!node_to_delete) return;
		if (node_to_delete->color == 'R') //red
		{
			if (node_to_delete->left == nullptr && node_to_delete->right == nullptr)
			{
				if (node_to_delete->parent->left == node_to_delete)
				{
					node_to_delete->parent->left = nullptr;
				}
				else if (node_to_delete->parent->right == node_to_delete)
				{
					node_to_delete->parent->right = nullptr;
				}
				delete node_to_delete;
			}
			else if (node_to_delete->left != nullptr && node_to_delete->right != nullptr)
			{
				Node<TKey, TValue>* result_to_swap;
				result_to_swap = node_to_delete->right;
				while (result_to_swap->left != nullptr)
				{
					result_to_swap = result_to_swap->left;
				}
				bool swapped_is_black = (result_to_swap->color == 'B');
				Node<TKey, TValue>* swapped_parent = result_to_swap->parent;
				Node<TKey, TValue>* swapped_child = result_to_swap->right;

				node_to_delete->data = result_to_swap->data;

				if (swapped_parent->left == result_to_swap)
					swapped_parent->left = swapped_child;
				else
					swapped_parent->right = swapped_child;
				if (swapped_child)
					swapped_child->parent = swapped_parent;

				delete result_to_swap;

				if (swapped_is_black)
				{
					re_balance(swapped_parent, swapped_child);
				}
			}
		}
		else //black
		{
			if (node_to_delete->left == nullptr && node_to_delete->right == nullptr)
			{
				Node<TKey, TValue>* B = nullptr;
				Node<TKey, TValue>* P = node_to_delete->parent; //hight changed
				if (node_to_delete->parent->left == node_to_delete)
				{
					node_to_delete->parent->left = nullptr;
					B = node_to_delete->parent->right;
				}
				else if (node_to_delete->parent->right == node_to_delete)
				{
					node_to_delete->parent->right = nullptr;
					B = node_to_delete->parent->left;
				}
				delete node_to_delete;
				re_balance(P, B); //balance
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
				while (result_to_swap->left != nullptr)
				{
					result_to_swap = result_to_swap->left;
				}
				bool swapped_is_black = (result_to_swap->color == 'B');
				Node<TKey, TValue>* swapped_parent = result_to_swap->parent;
				Node<TKey, TValue>* swapped_child = result_to_swap->right;
				node_to_delete->data = result_to_swap->data;
				if (swapped_parent->left == result_to_swap)
					swapped_parent->left = swapped_child;
				else
					swapped_parent->right = swapped_child;
				if (swapped_child)
					swapped_child->parent = swapped_parent;

				delete result_to_swap;
				if (swapped_is_black)
				{
					re_balance(swapped_parent, swapped_child);
				}
			}
		}
	}
};
