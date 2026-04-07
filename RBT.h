#pragma once

#include "BST.h"
#include <iostream>
#include "NodeAndRec.h"
#include <vector>

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
	using TP_BST<TKey, TValue>::pRoot;
	std::vector<Node<TKey, TValue>*> leafs;
	void find_leaf(Node<TKey, TValue>* node_to_find)
	{
		if (!node_to_find->left && !node_to_find->right)
		{
			leafs.push_back(node_to_find);
			return;
		}
		if (node_to_find->left)
			find_leaf(node_to_find->left);
		if (node_to_find->right)
			find_leaf(node_to_find->right);
	}
	int height_count(Node<TKey, TValue>* node_to_count)
	{
		int result = 0;
		while (node_to_count)
		{
			if (node_to_count->color == 'B') result++;
			node_to_count = node_to_count->parent;
		}
		return result;
	}
	bool color_check(Node<TKey, TValue>* node_to_check)
	{
		char previous_color = 'Z';
		while (node_to_check)
		{
			if (node_to_check->color == previous_color && previous_color == 'R')
			{
				return false;
			}
			previous_color = node_to_check->color;
			node_to_check = node_to_check->parent;
		}
		return true;
	}
	void re_balance(Node<TKey, TValue>* x, Node<TKey, TValue>* father)
	{
		//ЭТО КОРМЕН
		while (x != pRoot && (x == nullptr || x->color == 'B'))
		{
			if (x == father->left)
			{
				Node<TKey, TValue>* w = father->right;
				if (w && w->color == 'R') //1 кормен
				{
					w->color = 'B';
					father->color = 'R';
					//поворот левый
					if (father->right == w)
					{
						Node<TKey, TValue>* T1 = w->left;
						if (father->parent)
						{
							if (father->parent->left == father) father->parent->left = w;
							else father->parent->right = w;
						}
						else pRoot = w;
						w->parent = father->parent;
						father->parent = w;
						father->right = T1;
						if (T1) T1->parent = father;
						w->left = father;
					}
					else
					{
						Node<TKey, TValue>* T1 = w->right;
						if (father->parent)
						{
							if (father->parent->left == father) father->parent->left = w;
							else father->parent->right = w;
						}
						else pRoot = w;
						w->parent = father->parent;
						father->parent = w;
						father->left = T1;
						if (T1) T1->parent = father;
						w->right = father;
					}
					w = father->right;
				}
				if ((w == nullptr || w->left == nullptr || w->left->color == 'B') && (w == nullptr || w->right == nullptr || w->right->color == 'B'))
				//2 кормен
				{
					if (w) w->color = 'R';
					x = father;
					father = x->parent;
				}
				else
				{
					if (w && (w->right == nullptr || w->right->color == 'B')) //3 кормен
					{
						if (w->left) w->left->color = 'B';
						w->color = 'R';
						//поврот правый
						Node<TKey, TValue>* C = w->left;
						w->left = C->right;
						if (C->right) C->right->parent = w;
						C->right = w;
						w->parent = C;
						father->right = C;
						C->parent = father;
						w = C;
					}
					if (w) //4 кормен
					{
						w->color = father->color;
						father->color = 'B';
						if (w->right) w->right->color = 'B';
						//поворот левый
						Node<TKey, TValue>* Z = father->parent;
						if (Z)
						{
							if (Z->left == father) Z->left = w;
							else Z->right = w;
						}
						else pRoot = w;
						w->parent = Z;
						father->parent = w;
						father->right = w->left;
						if (w->left) w->left->parent = father;
						w->left = father;
					}
					x = pRoot;
					break;
				}
			}
			else //симметричный фрагмент с заменой left на right
			{
				Node<TKey, TValue>* w = father->left;
				if (w && w->color == 'R') //1 кормен
				{
					w->color = 'B';
					father->color = 'R';
					if (father->left == w)
					{
						Node<TKey, TValue>* T1 = w->right;
						if (father->parent)
						{
							if (father->parent->left == father) father->parent->left = w;
							else father->parent->right = w;
						}
						else pRoot = w;
						w->parent = father->parent;
						father->parent = w;
						father->left = T1;
						if (T1) T1->parent = father;
						w->right = father;
					}
					else
					{
						Node<TKey, TValue>* T1 = w->left;
						if (father->parent)
						{
							if (father->parent->left == father) father->parent->left = w;
							else father->parent->right = w;
						}
						else pRoot = w;
						w->parent = father->parent;
						father->parent = w;
						father->right = T1;
						if (T1) T1->parent = father;
						w->left = father;
					}
					w = father->left;
				}
				if ((w == nullptr || w->right == nullptr || w->right->color == 'B') && (w == nullptr || w->left == nullptr || w->left->color == 'B'))
				//2 кормен
				{
					if (w) w->color = 'R';
					x = father;
					father = x->parent;
				}
				else
				{
					if (w && (w->left == nullptr || w->left->color == 'B')) //3 кормен
					{
						if (w->right) w->right->color = 'B';
						w->color = 'R';
						Node<TKey, TValue>* C = w->right;
						w->right = C->left;
						if (C->left) C->left->parent = w;
						C->left = w;
						w->parent = C;
						father->left = C;
						C->parent = father;
						w = C;
					}
					if (w) //4 кормен
					{
						w->color = father->color;
						father->color = 'B';
						if (w->left) w->left->color = 'B';
						Node<TKey, TValue>* Z = father->parent;
						if (Z)
						{
							if (Z->left == father) Z->left = w;
							else Z->right = w;
						}
						else pRoot = w;
						w->parent = Z;
						father->parent = w;
						father->left = w->right;
						if (w->right) w->right->parent = father;
						w->right = father;
					}
					x = pRoot;
					break;
				}
			}
		}
		if (x) 
		{
			x->color = 'B';
		}
	}
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
		Node<TKey, TValue>* y = node_to_delete;
		Node<TKey, TValue>* x = nullptr;
		Node<TKey, TValue>* father = nullptr;
		char y_original_color = y->color;

		if (node_to_delete->left == nullptr)
		{
			x = node_to_delete->right;
			if (x)
				x->parent = node_to_delete->parent;//только правый потомок
			if (node_to_delete->parent == nullptr)
			{
				pRoot = x; //корень это вершина для удаления и если удаляем только его то он итак null
			}
			//подключили x
			else if (node_to_delete == node_to_delete->parent->left)
			{
				node_to_delete->parent->left = x;
			}
			else
			{
				node_to_delete->parent->right = x;
			}
			father = node_to_delete->parent;
			delete node_to_delete;
		}
		else if (node_to_delete->right == nullptr)
		{
			x = node_to_delete->left;
			if (x)
			{
				x->parent = node_to_delete->parent;	//только левый потомок
			}
			if (node_to_delete->parent == nullptr)
			{
				pRoot = x;//корень это вершина для удаления и если удаляем только его то он итак null
			}
			//подключили x
			else if (node_to_delete == node_to_delete->parent->left)
			{
				node_to_delete->parent->left = x;
			}
			else
			{
				node_to_delete->parent->right = x;
			}
			father = node_to_delete->parent;
			delete node_to_delete;
		}
		else
		{
			//узел
			y = node_to_delete->right;
			while (y->left != nullptr)
			{
				y = y->left;
			}
			//меняем данные
			y_original_color = y->color;
			x = y->right;
			//вдруг у у был ребенок
			if (x)
			{
				x->parent = y->parent;
			}
			if (y->parent == node_to_delete) //если y ребенок node_to_delete
			{
				father = y;
			}
			else // у не ребенок node_to_check
			{
				if (x)
				{
					x->parent = y->parent;
				}
				if (y->parent->left == y)
				{
					y->parent->left = x;
				}
				else
					y->parent->right = x;
				y->right = node_to_delete->right;
				node_to_delete->right->parent = y;
				father = y->parent;
			}
			if (node_to_delete->parent == nullptr)
			{
				pRoot = y;
			}
			else if (node_to_delete->parent->left == node_to_delete)
			{
				node_to_delete->parent->left = y;
			}
			else
			{
				node_to_delete->parent->right = y;
			}
			y->parent = node_to_delete->parent;
			y->left = node_to_delete->left;
			node_to_delete->left->parent = y;
			y->color = node_to_delete->color; //и меняем цвет
			delete node_to_delete;
		}
		//re balance если черный
		if (y_original_color == 'B')
		{
			re_balance(x, father);
		}
	}
	bool is_it_rbt()
	{
		if (!pRoot) return true;
		leafs.clear();
		find_leaf(pRoot);
		//height check
		int main_height = 0;
		for (int i = 0; i < leafs.size(); ++i)
		{
			if (main_height == 0)
			{
				main_height = height_count(leafs[i]);
			}
			if (height_count(leafs[i]) != main_height)
			{
				return false;
			}
		}
		//color check
		for (int i = 0; i < leafs.size(); ++i)
		{
			if (!color_check(leafs[i]))
			{
				return false;
			}
		}
		return true;
	}
};