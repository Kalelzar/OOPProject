//
// Created by Kalelzar on 24/03/2020.
//
#include "Date.hpp"
#include "gtest/gtest.h"

TEST(Date, JanuaryHas31Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(1,0), 31) << "January doesn't have 31 days apparently.";
}

TEST(Date, AprilHas30Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(4,0), 30) << "April doesn't have 30 days apparently.";
}

TEST(Date, FebruaryHas28or29Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(2, 2013), 28) << "February doesn't have 28 days during non-leap year.";
    ASSERT_EQ(Hotel::Date::daysOfMonth(2, 2012), 29) << "February doesn't have 29 days during leap year.";
}

TEST(Date, Constructor){
    Hotel::Date date(2020, 3, 24);
    EXPECT_EQ(date.getYear(), 2020) << "Year not set properly.";
    EXPECT_EQ(date.getMonth(), 3) << "Month not set properly.";
    EXPECT_EQ(date.getDay(), 24) << "Day not set properly.";
}

TEST(Date, ConstructorMonthOverflow){
    Hotel::Date monthOverflowPositive(2020, 13, 24);
    Hotel::Date monthOverflowPositive2(2020, 120, 24);
    Hotel::Date monthOverflowNegative(2020, -1, 24);
    Hotel::Date monthOverflowNegative2(2020, -36, 24);
    EXPECT_EQ(monthOverflowPositive.getMonth(), 1);
    EXPECT_EQ(monthOverflowPositive.getYear(), 2021);
    EXPECT_EQ(monthOverflowPositive2.getMonth(), 12);
    EXPECT_EQ(monthOverflowPositive2.getYear(), 2029);
    EXPECT_EQ(monthOverflowNegative.getMonth(), 11);
    EXPECT_EQ(monthOverflowNegative.getYear(), 2019);
    EXPECT_EQ(monthOverflowNegative2.getMonth(), 12);
    EXPECT_EQ(monthOverflowNegative2.getYear(), 2016);
}

TEST(Date, ConstructorDayOverflow){
    Hotel::Date dayOverflowPositive(2020, 4, 31);
    Hotel::Date dayOverflowPositive2(2020, 12, 70);
    Hotel::Date dayOverflowNegative(2020, 7, 0);
    Hotel::Date dayOverflowNegative2(2020, 1, -65);
    EXPECT_EQ(dayOverflowPositive.getDay(), 1);
    EXPECT_EQ(dayOverflowPositive.getMonth(), 5);
    EXPECT_EQ(dayOverflowPositive2.getDay(), 8);
    EXPECT_EQ(dayOverflowPositive2.getMonth(), 2);
    EXPECT_EQ(dayOverflowNegative.getDay(), 30);
    EXPECT_EQ(dayOverflowNegative.getMonth(), 6);
    EXPECT_EQ(dayOverflowNegative2.getDay(), 27);
    EXPECT_EQ(dayOverflowNegative2.getMonth(), 10);
}

TEST(Date, LeapYear){
    EXPECT_TRUE(Hotel::Date::isLeapYear(1600));
    EXPECT_FALSE(Hotel::Date::isLeapYear(1500));
}