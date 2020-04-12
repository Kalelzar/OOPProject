//
// Created by kalelzar on 4/10/20.
//

#include "../src/DateRange.hpp"
#include "gtest/gtest.h"

TEST(DateRange, Date_Equal) {
    Hotel::DateRange d1{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    EXPECT_TRUE(d1 == d2);
    EXPECT_TRUE(d1 == d3);
    EXPECT_FALSE(d1 == d4);
}

TEST(DateRange, Date_NotEqual) {
    Hotel::DateRange d1{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    EXPECT_FALSE(d1 != d2);
    EXPECT_FALSE(d1 != d3);
    EXPECT_TRUE(d1 != d4);
}

TEST(DateRange, Date_Less) {
    Hotel::DateRange d1{{2020, 1, 3}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    Hotel::Date d5 = {2020, 1, 11};
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(d1 < d3);
    EXPECT_FALSE(d1 < d4);
    EXPECT_TRUE(d1 < d5);
}

TEST(DateRange, Date_LessEq) {
    Hotel::DateRange d1{{2020, 1, 3}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    Hotel::Date d5 = {2020, 1, 11};
    EXPECT_TRUE(d1 <= d2);
    EXPECT_FALSE(d1 <= d3);
    EXPECT_TRUE(d1 <= d4);
    EXPECT_TRUE(d1 <= d5);
}

TEST(DateRange, Date_Greater) {
    Hotel::DateRange d1{{2020, 1, 3}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    Hotel::Date d5 = {2020, 1, 11};
    EXPECT_FALSE(d1 > d2);
    EXPECT_TRUE(d1 > d3);
    EXPECT_FALSE(d1 > d4);
    EXPECT_FALSE(d1 > d5);
    }

TEST(DateRange, Date_GreaterEq) {
    Hotel::DateRange d1{{2020, 1, 3}, {2020, 1, 7}};
    Hotel::Date d2 = {2020, 1, 7};
    Hotel::Date d3 = {2020, 1, 1};
    Hotel::Date d4 = {2020, 1, 3};
    Hotel::Date d5 = {2020, 1, 11};
    EXPECT_TRUE(d1 >= d2);
    EXPECT_TRUE(d1 >= d3);
    EXPECT_TRUE(d1 >= d4);
    EXPECT_FALSE(d1 >= d5);
}



TEST(DateRange, DateRange_Equal) {
    Hotel::DateRange d1{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 5}};
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(DateRange, DateRange_NotEqual) {
    Hotel::DateRange d1{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 1}, {2020, 1, 7}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 5}};
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 != d3);
}

TEST(DateRange, DateRange_Less) {
    Hotel::DateRange d1{{2020, 1, 5}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 8}, {2020, 1, 10}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 4}};
    Hotel::DateRange d4{{2020, 1, 5}, {2020, 1, 11}};
    Hotel::DateRange d5{{2020, 1, 1}, {2020, 1, 7}};
    EXPECT_TRUE(d1 < d2);
    EXPECT_FALSE(d1 < d3);
    EXPECT_FALSE(d1 < d4);
    EXPECT_FALSE(d1 < d5);
}

TEST(DateRange, DateRange_LessEq) {
    Hotel::DateRange d1{{2020, 1, 5}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 8}, {2020, 1, 10}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 4}};
    Hotel::DateRange d4{{2020, 1, 5}, {2020, 1, 11}};
    Hotel::DateRange d5{{2020, 1, 1}, {2020, 1, 7}};
    EXPECT_TRUE(d1 <= d2);
    EXPECT_FALSE(d1 <= d3);
    EXPECT_TRUE(d1 <= d4);
    EXPECT_TRUE(d1 <= d5);
}

TEST(DateRange, DateRange_Greater) {
    Hotel::DateRange d1{{2020, 1, 5}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 8}, {2020, 1, 10}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 4}};
    Hotel::DateRange d4{{2020, 1, 5}, {2020, 1, 11}};
    Hotel::DateRange d5{{2020, 1, 1}, {2020, 1, 7}};
    EXPECT_FALSE(d1 > d2);
    EXPECT_TRUE(d1 > d3);
    EXPECT_FALSE(d1 > d4);
    EXPECT_FALSE(d1 > d5);
}

TEST(DateRange, DateRange_GreaterEq) {
    Hotel::DateRange d1{{2020, 1, 5}, {2020, 1, 7}};
    Hotel::DateRange d2{{2020, 1, 8}, {2020, 1, 10}};
    Hotel::DateRange d3{{2020, 1, 1}, {2020, 1, 4}};
    Hotel::DateRange d4{{2020, 1, 5}, {2020, 1, 11}};
    Hotel::DateRange d5{{2020, 1, 1}, {2020, 1, 7}};
    EXPECT_FALSE(d1 >= d2);
    EXPECT_TRUE(d1 >= d3);
    EXPECT_TRUE(d1 >= d4);
    EXPECT_TRUE(d1 >= d5);
}