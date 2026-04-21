#include "pch.h"
#include "../Tablica/RBT.h"
#include "../Tablica/NodeAndRec.h"
#include "../Tablica/BST.h"
#include "../Tablica/HashTableOpen.h"
#include "../Tablica/CuckooHashingVer2.h"
//RBT TESTS
//Base
TEST(RBT, CanCreate)
{
	RBT<int, int> tree;
	SUCCEED();  
}
TEST(RBT, CanInsert) 
{
	RBT<int, int> tree;
	EXPECT_NO_THROW(tree.Insert(1,1));
}
TEST(RBT, CanDelete)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Delete(1));
	EXPECT_EQ(tree.Find(1), nullptr);
}
TEST(RBT, CanFind)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	Node<int, int>* res = tree.Find(1);
	ASSERT_NE(res, nullptr);
	EXPECT_EQ(res->data.key, 1);
	EXPECT_EQ(res->data.value, 1);
}
TEST(RBT, CanPrint)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Print());
}
TEST(RBT, CorrectDeleteOfNotExist)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Delete(2));
}
//Special
TEST(RBT, CorrectAfterManyInserts)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	tree.Insert(17, 1);
	tree.Insert(12, 1);
	tree.Insert(19, 1);
	tree.Insert(11, 1);
	tree.Insert(114, 1);
	tree.Insert(121, 1);
	tree.Insert(1131, 1);
	tree.Insert(51, 1);
	tree.Insert(4341, 1);
	tree.Insert(1765, 1);
	tree.Insert(1234, 1);
	tree.Insert(167, 1);
	tree.Insert(1987, 1);
	tree.Insert(4561, 1);
	tree.Insert(25451, 1);
	tree.Insert(1111, 1);
	tree.Insert(32, 1);
	tree.Insert(191, 1);
	EXPECT_TRUE(tree.is_it_rbt());
}//
TEST(RBT, CorrectAfterManyDeletes)
{
	RBT<int, int> tree;
	tree.Insert(1, 1);
	tree.Insert(17, 1);
	tree.Insert(12, 1);
	tree.Insert(19, 1);
	tree.Insert(11, 1);
	tree.Insert(114, 1);
	tree.Insert(121, 1);
	tree.Insert(1131, 1);
	tree.Insert(51, 1);
	tree.Insert(4341, 1);
	tree.Insert(1765, 1);
	tree.Insert(1234, 1);
	tree.Insert(167, 1);
	tree.Insert(1987, 1);
	tree.Insert(4561, 1);
	tree.Insert(25451, 1);
	tree.Insert(1111, 1);
	tree.Insert(32, 1);
	tree.Insert(191, 1);

	tree.Delete(1);
	tree.Delete(17);
	tree.Delete(12);
	tree.Delete(19);
	tree.Delete(11);
	tree.Delete(114);
	tree.Delete(121);
	tree.Delete(1131);
	tree.Delete(1111);
	tree.Delete(32);
	EXPECT_TRUE(tree.is_it_rbt());
}//
//BST TESTS
//Base
TEST(BST, CanCreate)
{
	TP_BST<int, int> tree;
	SUCCEED();
}
TEST(BST, CanInsert)
{
	TP_BST<int, int> tree;
	EXPECT_NO_THROW(tree.Insert(1, 1));
}
TEST(BST, CanDelete)
{
	TP_BST<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Delete(1));
	EXPECT_EQ(tree.Find(1), nullptr);
}
TEST(BST, CanFind)
{
	TP_BST<int, int> tree;
	tree.Insert(1, 1);
	Node<int, int>* res = tree.Find(1);
	ASSERT_NE(res, nullptr);
	EXPECT_EQ(res->data.key, 1);
	EXPECT_EQ(res->data.value, 1);
}
TEST(BST, CanPrint)
{
	TP_BST<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Print());
}
TEST(BST, CorrectDeleteOfNotExist)
{
	TP_BST<int, int> tree;
	tree.Insert(1, 1);
	EXPECT_NO_THROW(tree.Delete(2));
}
//HashTableOpen TESTS
//Base
TEST(HashTableOpen, CanCreate)
{
	HashTableOpen<int, int> table(5,7,0.7);
	SUCCEED();
}
TEST(HashTableOpen, CanInsert)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	EXPECT_NO_THROW(table.Insert(1, 1));
}
TEST(HashTableOpen, CanDelete)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	table.Insert(1, 1);
	EXPECT_NO_THROW(table.Delete(1));
	std::pair<int, bool> test_r = { 0,0 };
	EXPECT_EQ(table.Find(1), test_r);
}
TEST(HashTableOpen, CanFind)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	table.Insert(1, 1);
	std::pair<int, bool> test_r = table.Find(1);
	std::pair<int, bool> test_rr = { 1,1 };
	ASSERT_EQ(test_r, test_rr);
}
TEST(HashTableOpen, CanPrint)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	table.Insert(1, 1);
	EXPECT_NO_THROW(table.Print());
}
TEST(HashTableOpen, CorrectDeleteOfNotExist)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	table.Insert(1, 1);
	EXPECT_NO_THROW(table.Delete(2));
}
//Special
TEST (HashTableOpen, CorrectReHash)
{
	HashTableOpen<int, int> table(5, 7, 0.7);
	table.Insert(10, 12);
	table.Insert(11, 12);
	table.Insert(12, 12);
	table.Insert(13, 12);
	table.Insert(14, 12);
	EXPECT_EQ(10, table.GetSize());
	table.Insert(10, 12);
	table.Insert(11, 12);
	table.Insert(12, 12);
	table.Insert(13, 12);
	table.Insert(14, 12);
	table.Insert(15, 12);
	table.Insert(16, 12);
	table.Insert(17, 12);
	EXPECT_EQ(20, table.GetSize());
}
//CuckooHashing TESTS
//Base
TEST(CuckooHashing, CanCreate)
{
	CuckooVer2<int, int> table(5);
	SUCCEED();
}
TEST(CuckooHashing, CanInsert)
{
	CuckooVer2<int, int> table(5);
	EXPECT_NO_THROW(table.UserInsert(1, 1));
}
TEST(CuckooHashing, CanDelete)
{
	CuckooVer2<int, int> table(5);
	table.UserInsert(1, 1);
	EXPECT_NO_THROW(table.Delete(1));
	std::pair<int, bool> test_r = { 0,0 };
	EXPECT_EQ(table.Find(1), test_r);
}
TEST(CuckooHashing, CanFind)
{
	CuckooVer2<int, int> table(5);
	table.UserInsert(1, 1);
	std::pair<int, bool> test_r = table.Find(1);
	std::pair<int, bool> test_rr = { 1,1 };
	ASSERT_EQ(test_r, test_rr);
}
TEST(CuckooHashing, CanPrint)
{
	CuckooVer2<int, int> table(5);
	table.UserInsert(1, 1);
	EXPECT_NO_THROW(table.Print());
}
TEST(CuckooHashing, CorrectDeleteOfNotExist)
{
	CuckooVer2<int, int> table(5);
	table.UserInsert(1, 1);
	EXPECT_NO_THROW(table.Delete(2));
}
//Special
TEST(CuckooHashing, CorrectReHash)
{
	CuckooVer2<int, int> table(5);
	table.UserInsert(10, 12);
	table.UserInsert(11, 12);
	table.UserInsert(12, 12);
	table.UserInsert(13, 12);
	table.UserInsert(14, 12);
	EXPECT_EQ(5, table.GetSize());
	table.UserInsert(10, 12);
	table.UserInsert(11, 12);
	table.UserInsert(12, 12);
	table.UserInsert(13, 12);
	table.UserInsert(14, 12);
	table.UserInsert(15, 12);
	table.UserInsert(16, 12);
	table.UserInsert(17, 12);
	EXPECT_EQ(10, table.GetSize());
}

