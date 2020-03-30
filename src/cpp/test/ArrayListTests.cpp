//
// Created by Kalelzar on 25/03/2020.
//

#include "../src/collection/ArrayList.hpp"
#include "../src/Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(ArrayList, DefaultConstructor_Room) {
    ArrayList<Room> rl;
    EXPECT_EQ(rl.capacity(), ArrayList<Room>::getDefaultReservedSpace());
    EXPECT_EQ(rl.length(), 0);
}

TEST(ArrayList, Clear) {
    ArrayList<int> rl;
    for (int i = 0; i < 10; i++) {
        rl.append(i);
    }
    EXPECT_EQ(rl.length(), 10);
    rl.clear();
    EXPECT_EQ(rl.length(), 0);
    EXPECT_THROW(rl[0]->get(), NoValueException);
}

TEST(ArrayList, Subscript) {
    ArrayList<int> rl;
    EXPECT_THROW(rl[0]->get(), NoValueException);
    rl.append(1);
    rl.append(2);
    rl.append(3);
    EXPECT_EQ(rl[0]->get(), 1);
    EXPECT_EQ(rl[1]->get(), 2);
    EXPECT_EQ(rl[2]->get(), 3);
    EXPECT_THROW(rl[3]->get(), NoValueException);
}

TEST(ArrayList, Constructor_Room) {
    int capacity = 4;
    ArrayList<Room> rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    EXPECT_EQ(rl.length(), 0);
}

TEST(ArrayList, AppendGet_Room) {
    ArrayList<Room> rl;
    Room r(0, 1);
    Room r2(1, 1);
    EXPECT_EQ(rl.length(), 0);
    rl.append(r);
    EXPECT_EQ(rl.length(), 1);
    EXPECT_TRUE(rl.get(0) == r);
    rl.append(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(1) == r2);
}

TEST(ArrayList, PrependGet_Room) {
    ArrayList<Room> rl;
    Room r(0, 1);
    Room r2(1, 1);
    EXPECT_EQ(rl.length(), 0);

    rl.prepend(r);
    EXPECT_EQ(rl.length(), 1);
    EXPECT_TRUE(rl.get(0) == r);

    rl.prepend(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r2);
    EXPECT_TRUE(rl.get(1) == r);
}


TEST(ArrayList, Insert_Room) {
    ArrayList<Room> rl;
    Room r1(0, 1);
    Room r2(1, 1);
    Room r3(2, 1);
    rl.append(r1);
    rl.append(r2);
    EXPECT_TRUE(r1 == rl.get(0));
    EXPECT_TRUE(r2 == rl.get(1));
    rl.insert(r3, 1);
    EXPECT_TRUE(r1 == rl.get(0));
    EXPECT_TRUE(r3 == rl.get(1));
    EXPECT_TRUE(r2 == rl.get(2));
}

TEST(ArrayList, AppendAll_Room) {
    ArrayList<Room> rl;
    Room r(0, 1);
    Room r2(1, 1);
    rl.append(r);
    rl.append(r2);
    ArrayList<Room> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.appendAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_TRUE(newList.get(0) == rl.get(0));
    EXPECT_TRUE(newList.get(1) == rl.get(1));
}

TEST(ArrayList, PrependAll_Room) {
    ArrayList<Room> rl;
    Room r(0, 1);
    Room r2(1, 1);
    rl.append(r);
    rl.append(r2);
    ArrayList<Room> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.prependAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_TRUE(newList.get(0) == rl.get(1));
    EXPECT_TRUE(newList.get(1) == rl.get(0));
}

TEST(ArrayList, Expand_Room) {
    int capacity = 1;
    ArrayList<Room> rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    for (int i = 0; i < capacity * 4; i++) {
        rl.append(Room());
    }
    EXPECT_EQ(rl.capacity(), capacity * 4);
}

TEST(ArrayList, Remove_Room) {
    ArrayList<Room> rl;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.remove(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r1);
    EXPECT_TRUE(rl.get(1) == r3);
}

TEST(ArrayList, RemoveAt_Room) {
    ArrayList<Room> rl;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.removeAt(1);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r1);
    EXPECT_TRUE(rl.get(1) == r3);
}

TEST(ArrayList, Pop_Room) {
    ArrayList<Room> rl;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.pop();
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r1);
    EXPECT_TRUE(rl.get(1) == r2);
}

TEST(ArrayList, Shift_Room) {
    ArrayList<Room> rl;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.shift();
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r2);
    EXPECT_TRUE(rl.get(1) == r3);
}

TEST(ArrayList, DefaultConstructor_Int) {
    ArrayList<int> rl;
    EXPECT_EQ(rl.capacity(), ArrayList<Room>::getDefaultReservedSpace());
    EXPECT_EQ(rl.length(), 0);
}

TEST(ArrayList, Constructor_Int) {
    int capacity = 4;
    ArrayList<int> rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    EXPECT_EQ(rl.length(), 0);
}

TEST(ArrayList, AppendGet_Int) {
    ArrayList<int> rl;
    int r = 0;
    int r2 = 1;
    EXPECT_EQ(rl.length(), 0);
    rl.append(r);
    EXPECT_EQ(rl.length(), 1);
    EXPECT_EQ(rl.get(0), r);
    rl.append(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(1), r2);
}

TEST(ArrayList, PrependGet_Int) {
    ArrayList<int> rl;
    int r = 0;
    int r2 = 1;
    EXPECT_EQ(rl.length(), 0);

    rl.prepend(r);
    EXPECT_EQ(rl.length(), 1);
    EXPECT_EQ(rl.get(0), r);

    rl.prepend(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(0), r2);
    EXPECT_EQ(rl.get(1), r);
}

TEST(ArrayList, Insert_Int) {
    ArrayList<int> rl;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rl.append(r1);
    rl.append(r2);
    EXPECT_EQ(r1, rl.get(0));
    EXPECT_EQ(r2, rl.get(1));
    rl.insert(r3, 1);
    EXPECT_EQ(r1, rl.get(0));
    EXPECT_EQ(r3, rl.get(1));
    EXPECT_EQ(r2, rl.get(2));
}

TEST(ArrayList, AppendAll_Int) {
    ArrayList<int> rl;
    int r = 0;
    int r2 = 1;
    rl.append(r);
    rl.append(r2);
    ArrayList<int> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.appendAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_EQ(newList.get(0), rl.get(0));
    EXPECT_EQ(newList.get(1), rl.get(1));
}

TEST(ArrayList, PrependAll_Int) {
    ArrayList<int> rl;
    int r = 0;
    int r2 = 1;
    rl.append(r);
    rl.append(r2);
    ArrayList<int> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.prependAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_EQ(newList.get(0), rl.get(1));
    EXPECT_EQ(newList.get(1), rl.get(0));
}

TEST(ArrayList, Expand_Int) {
    int capacity = 1;
    ArrayList<int> rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    for (int i = 0; i < capacity * 4; i++) {
        rl.append(i);
    }
    EXPECT_EQ(rl.capacity(), capacity * 4);
}

TEST(ArrayList, Remove_Int) {
    ArrayList<int> rl;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.remove(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(0), r1);
    EXPECT_EQ(rl.get(1), r3);
}

TEST(ArrayList, RemoveAt_Int) {
    ArrayList<int> rl;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.removeAt(1);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(0), r1);
    EXPECT_EQ(rl.get(1), r3);
}

TEST(ArrayList, Pop_Int) {
    ArrayList<int> rl;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.pop();
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(0), r1);
    EXPECT_EQ(rl.get(1), r2);
}

TEST(ArrayList, Shift_Int) {
    ArrayList<int> rl;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rl.append(r1);
    rl.append(r2);
    rl.append(r3);
    rl.shift();
    EXPECT_EQ(rl.length(), 2);
    EXPECT_EQ(rl.get(0), r2);
    EXPECT_EQ(rl.get(1), r3);
}
