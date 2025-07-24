#include "../Task4/AVLTree.h"
#include "../googletest/googletest/include/gtest/gtest.h"

TEST(AVLTreeTests, Test1)
{
    AVLTree<int> tree;
    ASSERT_TRUE(tree.Empty());
    tree.Insert(2);
    tree.Insert(1);
    auto pkl = tree.RoundRrootL();
    int expect[] = {2, 1};
    for (int i = 0; i < 2; i++)
    {
        ASSERT_EQ(expect[i], pkl[i]);
    }  
}

TEST(AVLTreeTests, Test2)
{
    int values[] = {2, 1, 3};
    AVLTree<int> tree(values, 3);
    auto pkl = tree.RoundRrootL();
    int expect[] = {3, 2, 1};
    for (int i = 0; i < 3; i++)
    {
        ASSERT_EQ(expect[i], pkl[i]);
    }  
    tree.Remove(2);
    auto pkl2 = tree.RoundRrootL();
    int expect2[] = {3, 1};
    for (int i = 0; i < 2; i++)
    {
        ASSERT_EQ(expect2[i], pkl2[i]);
    }  
}

TEST(AVLTreeTests, Test3)
{
    int values[] = {2, 1, 3};
    AVLTree<int> tree(values, 3);
    AVLTree<int> newTree(tree);
    auto pkl = tree.RoundRrootL();
    int expect[] = {3, 2, 1};
    for (int i = 0; i < 3; i++)
    {
        ASSERT_EQ(expect[i], pkl[i]);
    }  
}

TEST(AVLTreeTests, Test4)
{
    int values[] = {10, 5, 15};
    AVLTree<int> tree(values, 3);
    tree.Insert(42);
    ASSERT_TRUE(tree.Contains(42));
    ASSERT_FALSE(tree.Contains(4));
    auto pkl = tree.RoundRrootL();
    int expect[] = {42, 15, 10};
    for (int i = 0; i < 3; i++)
    {
        ASSERT_EQ(expect[i], pkl[i]);
    }  
}