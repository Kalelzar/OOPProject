#include "gtest/gtest.h"
#include "../src/collection/RangeBinaryTree.hpp"
#include "../src/collection/BinaryNode.hpp"


TEST(RangeBinaryTree, Populate) {
    RangeBinaryTree<int, int> tree;
    tree.populate(0, 0);
    EXPECT_EQ(tree.viewHead()->value.get(0), 0);
    tree.populate(1, 1);
    EXPECT_EQ(tree.viewHead()->right->value.get(0), 1);
    tree.populate(-1, -1);
    EXPECT_EQ(tree.viewHead()->left->value.get(0), -1);
}

TEST(RangeBinaryTree, firstMatch) {
    RangeBinaryTree<int, int> tree;
    tree.populate(0, 0);
    tree.populate(1, 1);
    tree.populate(-1, -1);
    tree.populate(3, 3);
    tree.populate(2, 2);
    tree.populate(4, 4);
    const BinaryNode<int, int> *match1 = tree.findFirst([](int a) { return a == 0; });
    ASSERT_FALSE(match1 == nullptr);
    EXPECT_EQ(match1, tree.viewHead());
    const BinaryNode<int, int> *match2 = tree.findFirst([](int a) { return a > 1; });
    ASSERT_FALSE(match2 == nullptr);
    EXPECT_EQ(match2->tag, 3);
    const BinaryNode<int, int> *match3 = tree.findFirst([](int a) { return a < -1; });
    ASSERT_TRUE(match3 == nullptr);
    const BinaryNode<int, int> *match4 = tree.findFirst([](int a) { return a > 1 && a != 3; });
    ASSERT_FALSE(match4 == nullptr);
    EXPECT_EQ(match4->tag, 2);
}

TEST(RangeBinaryTree, inRange) {
    RangeBinaryTree<int, int> tree;
    tree.populate(0, 0);
    tree.populate(1, 1);
    tree.populate(-1, -1);
    tree.populate(3, 3);
    //tree.populate(2, 2);
    tree.populate(7, 7);

    ArrayList<int> a;
    a.append(0);
    a.append(1);
    a.append(3);

    unique_ptr<ArrayList<int>> res1 = tree.inRange(0, 3);
    ASSERT_EQ(a.length(), res1->length());
    for (unsigned i = 0; i < a.length(); i++) {
        EXPECT_EQ(a.get(i), res1->get(i));
    }

    tree.populate(5, 5);
    tree.populate(4, 4);

    a.append(5);
    a.append(4);

    unique_ptr<ArrayList<int>> res2 = tree.inRange(0, 6);
    ASSERT_EQ(a.length(), res2->length());
    for (unsigned i = 0; i < a.length(); i++) {
        EXPECT_EQ(a.get(i), res2->get(i));
    }
}