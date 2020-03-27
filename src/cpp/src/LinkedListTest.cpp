//
// Created by Kalelzar on 26/03/2020.
//

#include "LinkedList.hpp"
#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(LinkedList, Constructor_Int){
    LinkedList<int> ll;
    EXPECT_THROW(ll.head()->get(), NoValueException);
    EXPECT_THROW(ll.last()->get(), NoValueException);
}

TEST(LinkedList, Append_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 1);
    EXPECT_EQ(ll.last()->get(), 2);
}

TEST(LinkedList, Clear){
    LinkedList<int> rl;
    for(int i = 0; i < 10; i++){
        rl.append(i);
    }
    EXPECT_EQ(rl.length(), 10);
    rl.clear();
    EXPECT_EQ(rl.length(), 0);
    EXPECT_THROW(rl[0]->get(), NoValueException);
}

TEST(LinkedList, Subscript){
    LinkedList<int> rl;
    EXPECT_THROW(rl[0]->get(), NoValueException);
    rl.append(1);
    rl.append(2);
    rl.append(3);
    EXPECT_EQ(rl[0]->get(), 1);
    EXPECT_EQ(rl[1]->get(), 2);
    EXPECT_EQ(rl[2]->get(), 3);
    EXPECT_THROW(rl[3]->get(), NoValueException);
}

TEST(LinkedList, Prepend_Int){
    LinkedList<int> ll;
    ll.prepend(1);
    ll.prepend(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 2);
    EXPECT_EQ(ll.last()->get(), 1);
}

TEST(LinkedList, Insert_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.insert(3, 1);
    EXPECT_EQ(ll.length(), 3);
    EXPECT_EQ(ll.head()->get(), 1);
    EXPECT_EQ(ll.get(1), 3);
    EXPECT_EQ(ll.last()->get(), 2);
}

TEST(LinkedList, Remove_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.remove(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 1);
    EXPECT_EQ(ll.last()->get(), 3);
}

TEST(LinkedList, RemoveAt_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.removeAt(1);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 1);
    EXPECT_EQ(ll.last()->get(), 3);
}

TEST(LinkedList, Pop_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.pop();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 1);
    EXPECT_EQ(ll.last()->get(), 2);
}

TEST(LinkedList, Shift_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.shift();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head()->get(), 2);
    EXPECT_EQ(ll.last()->get(), 3);
}

TEST(LinkedList, Constructor_Room){
    LinkedList<Room> ll;
    EXPECT_THROW(ll.head()->get(), NoValueException);
    EXPECT_THROW(ll.last()->get(), NoValueException);
}

TEST(LinkedList, Append_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    ll.append(r1);
    ll.append(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r1);
    EXPECT_TRUE(ll.last()->get() == r2);
}

TEST(LinkedList, Prepend_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    ll.prepend(r1);
    ll.prepend(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r2);
    EXPECT_TRUE(ll.last()->get() == r1);
}

TEST(LinkedList, Insert_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.insert(r3, 1);
    EXPECT_EQ(ll.length(), 3);
    EXPECT_TRUE(ll.head()->get() ==r1);
    EXPECT_TRUE(ll.get(1) ==r3);
    EXPECT_TRUE(ll.last()->get() ==r2);
}

TEST(LinkedList, Remove_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.remove(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r1);
    EXPECT_TRUE(ll.last()->get() == r3);
}

TEST(LinkedList, RemoveAt_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.removeAt(1);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r1);
    EXPECT_TRUE(ll.last()->get() == r3);
}

TEST(LinkedList, Pop_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.pop();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r1);
    EXPECT_TRUE(ll.last()->get() == r2);
}

TEST(LinkedList, Shift_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.shift();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head()->get() == r2);
    EXPECT_TRUE(ll.last()->get() == r3);
}
