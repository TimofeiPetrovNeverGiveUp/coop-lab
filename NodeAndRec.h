#pragma once
template <typename TKey=double, typename TValue=double>
struct TableRec
{
	TKey key;
	TValue value;
};
template <typename TKey, typename TValue>
struct Node
{
	TableRec<TKey, TValue> data;
	Node* left;
	Node* right;
	Node* parent;
	char color; //R B
	Node() : data{ TKey(), TValue() }, left(nullptr), right(nullptr), parent(nullptr), color('B') {}
};