//
// Created by Kalelzar on 25/03/2020.
//

#include "ArraySet.hpp"
#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(ArraySet, DefaultConstructor_Room) {
    ArraySet<Room> rs;
    EXPECT_EQ(rs.capacity(), ArraySet<Room>::getDefaultReservedSpace());
    EXPECT_EQ(rs.length(), 0);
}

TEST(ArraySet, Constructor_Room) {
    int capacity = 4;
    ArraySet<Room> rs(capacity);
    EXPECT_EQ(rs.capacity(), capacity);
    EXPECT_EQ(rs.length(), 0);
}

TEST(ArraySet, AppendGet_Room) {
    ArraySet<Room> rs;
    Room r(0, 1);
    Room r2(1, 1);
    EXPECT_EQ(rs.length(), 0);
    rs.append(r);
    EXPECT_EQ(rs.length(), 1);
    EXPECT_TRUE(rs.get(0) == r);
    rs.append(r2);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_TRUE(rs.get(1) == r2);
}

TEST(ArraySet, PrependGet_Room) {
    ArraySet<Room> rl;
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

TEST(ArraySet, AppendAll_Room) {
    ArraySet<Room> rs;
    Room r(0, 1);
    Room r2(1, 1);
    rs.append(r);
    rs.append(r2);
    ArraySet<Room> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.appendAll(rs);
    EXPECT_EQ(newList.length(), rs.length());
    EXPECT_EQ(newList.capacity(), rs.capacity());
    EXPECT_TRUE(newList.get(0) == rs.get(0));
    EXPECT_TRUE(newList.get(1) == rs.get(1));
}

TEST(ArraySet, PrependAll_Room) {
    ArraySet<Room> rl;
    Room r(0, 1);
    Room r2(1, 1);
    rl.append(r);
    rl.append(r2);
    ArraySet<Room> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.prependAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_TRUE(newList.get(0) == rl.get(1));
    EXPECT_TRUE(newList.get(1) == rl.get(0));
}

TEST(ArraySet, Insert_Room){
    ArraySet<Room> rl;
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

TEST(ArraySet, Expand_Room) {
    int capacity = 1;
    ArraySet<Room> rs(capacity);
    EXPECT_EQ(rs.capacity(), capacity);
    for (int i = 0; i < capacity*4; i++) {
        rs.append(Room(i, 0));
    }
    EXPECT_EQ(rs.capacity(), capacity * 4);
}

TEST(ArraySet, Unique_Room){
    ArraySet<Room> rs;
    EXPECT_EQ(rs.length(), 0);
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(1, 3);
    Room r4(2, 3);
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.prepend(r3);
    rs.insert(r4, 1);
    EXPECT_EQ(rs.length(), 2);
}

TEST(ArraySet, Remove_Room){
    ArraySet<Room> rs;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.remove(r2);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_TRUE(rs.get(0) == r1);
    EXPECT_TRUE(rs.get(1) == r3);
}

TEST(ArraySet, RemoveAt_Room){
    ArraySet<Room> rs;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.removeAt(1);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_TRUE(rs.get(0) == r1);
    EXPECT_TRUE(rs.get(1) == r3);
}

TEST(ArraySet, Pop_Room){
    ArraySet<Room> rs;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.pop();
    EXPECT_EQ(rs.length(), 2);
    EXPECT_TRUE(rs.get(0) == r1);
    EXPECT_TRUE(rs.get(1) == r2);
}

TEST(ArraySet, Shift_Room){
    ArraySet<Room> rs;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.shift();
    EXPECT_EQ(rs.length(), 2);
    EXPECT_TRUE(rs.get(0) == r2);
    EXPECT_TRUE(rs.get(1) == r3);
}

TEST(ArraySet, DefaultConstructor_Int) {
    ArraySet<int> rs;
    EXPECT_EQ(rs.capacity(), ArraySet<Room>::getDefaultReservedSpace());
    EXPECT_EQ(rs.length(), 0);
}

TEST(ArraySet, Constructor_Int) {
    int capacity = 4;
    ArraySet<int> rs(capacity);
    EXPECT_EQ(rs.capacity(), capacity);
    EXPECT_EQ(rs.length(), 0);
}

TEST(ArraySet, AppendGet_Int) {
    ArraySet<int> rs;
    int r = 0;
    int r2 = 1;
    EXPECT_EQ(rs.length(), 0);
    rs.append(r);
    EXPECT_EQ(rs.length(), 1);
    EXPECT_EQ(rs.get(0), r);
    rs.append(r2);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_EQ(rs.get(1), r2);
}

TEST(ArraySet, PrependGet_Int) {
    ArraySet<int> rl;
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

TEST(ArraySet, Insert_Int){
    ArraySet<int> rl;
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

TEST(ArraySet, AppendAll_Int) {
    ArraySet<int> rs;
    int r = 0;
    int r2 = 1;
    rs.append(r);
    rs.append(r2);
    ArraySet<int> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.appendAll(rs);
    EXPECT_EQ(newList.length(), rs.length());
    EXPECT_EQ(newList.capacity(), rs.capacity());
    EXPECT_EQ(newList.get(0), rs.get(0));
    EXPECT_EQ(newList.get(1), rs.get(1));
}

TEST(ArraySet, PrependAll_Int) {
    ArraySet<int> rl;
    int r = 0;
    int r2 = 1;
    rl.append(r);
    rl.append(r2);
    ArraySet<int> newList;
    EXPECT_EQ(newList.length(), 0);
    newList.prependAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_EQ(newList.get(0), rl.get(1));
    EXPECT_EQ(newList.get(1), rl.get(0));
}

TEST(ArraySet, Expand_Int) {
    int capacity = 1;
    ArraySet<int> rs(capacity);
    EXPECT_EQ(rs.capacity(), capacity);
    for (int i = 0; i < capacity*4; i++) {
        rs.append(i);
    }
    EXPECT_EQ(rs.capacity(), capacity * 4);
}

TEST(ArraySet, Unique_Int){
    ArraySet<int> rs;
    EXPECT_EQ(rs.length(), 0);
    rs.append(1);
    rs.append(2);
    rs.append(1);
    rs.prepend(1);
    rs.insert(2, 1);
    EXPECT_EQ(rs.length(), 2);
}

TEST(ArraySet, Remove_Int){
    ArraySet<int> rs;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.remove(r2);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_EQ(rs.get(0), r1);
    EXPECT_EQ(rs.get(1), r3);
}

TEST(ArraySet, RemoveAt_Int){
    ArraySet<int> rs;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.removeAt(1);
    EXPECT_EQ(rs.length(), 2);
    EXPECT_EQ(rs.get(0), r1);
    EXPECT_EQ(rs.get(1), r3);
}

TEST(ArraySet, Pop_Int){
    ArraySet<int> rs;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.pop();
    EXPECT_EQ(rs.length(), 2);
    EXPECT_EQ(rs.get(0), r1);
    EXPECT_EQ(rs.get(1), r2);
}

TEST(ArraySet, Shift_Int){
    ArraySet<int> rs;
    int r1 = 1;
    int r2 = 2;
    int r3 = 3;
    rs.append(r1);
    rs.append(r2);
    rs.append(r3);
    rs.shift();
    EXPECT_EQ(rs.length(), 2);
    EXPECT_EQ(rs.get(0), r2);
    EXPECT_EQ(rs.get(1), r3);
}