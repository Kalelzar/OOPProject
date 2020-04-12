//
// Created by Kalelzar on 24/03/2020.
//
#include "../src/Date.hpp"
#include "gtest/gtest.h"


TEST(Date, Equal) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 1);
    Hotel::Date d3(2020, 1, 2);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(Date, NotEqual) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 1);
    Hotel::Date d3(2020, 1, 2);
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 != d3);
}

TEST(Date, Greater) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 2);
    Hotel::Date d3(2020, 1, 3);
    EXPECT_TRUE(d2 > d1);
    EXPECT_FALSE(d2 > d3);
}

TEST(Date, Less) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 2);
    Hotel::Date d3(2020, 1, 3);
    EXPECT_TRUE(d2 < d3);
    EXPECT_FALSE(d2 < d1);
}

TEST(Date, GreaterEq) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 2);
    Hotel::Date d3(2020, 1, 3);
    EXPECT_TRUE(d2 >= d1);
    EXPECT_TRUE(d2 >= d2);
    EXPECT_FALSE(d2 >= d3);
}

TEST(Date, LessEq) {
    Hotel::Date d1(2020, 1, 1);
    Hotel::Date d2(2020, 1, 2);
    Hotel::Date d3(2020, 1, 3);
    EXPECT_FALSE(d2 <= d1);
    EXPECT_TRUE(d2 <= d2);
    EXPECT_TRUE(d2 <= d3);
}

TEST(Date, JanuaryHas31Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(1, 0), 31)
                                << "January doesn't have 31 days apparently.";
}

TEST(Date, AprilHas30Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(4, 0), 30)
                                << "April doesn't have 30 days apparently.";
}

TEST(Date, FebruaryHas28or29Days) {
    ASSERT_EQ(Hotel::Date::daysOfMonth(2, 2013), 28)
                                << "February doesn't have 28 days during non-leap year.";
    ASSERT_EQ(Hotel::Date::daysOfMonth(2, 2012), 29)
                                << "February doesn't have 29 days during leap year.";
}

TEST(Date, Constructor) {
    Hotel::Date date(2020, 3, 24);
    EXPECT_EQ(date.getYear(), 2020) << "Year not set properly.";
    EXPECT_EQ(date.getMonth(), 3) << "Month not set properly.";
    EXPECT_EQ(date.getDay(), 24) << "Day not set properly.";
}

TEST(Date, LeapYear) {
    EXPECT_TRUE(Hotel::Date::isLeapYear(1600));
    EXPECT_FALSE(Hotel::Date::isLeapYear(1500));
}

TEST(Date, Today) {
    Hotel::Date today = Hotel::Date::today();
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    EXPECT_EQ(1900 + ltm->tm_year, today.getYear());
    EXPECT_EQ(ltm->tm_mon + 1, today.getMonth());
    EXPECT_EQ(ltm->tm_mday, today.getDay());
}

TEST(Date, DefaultConstructor) {
    Hotel::Date today;
    Hotel::Date tday = Hotel::Date::today();
    ASSERT_EQ(today.getDay(), tday.getDay());
    ASSERT_EQ(today.getMonth(), tday.getMonth());
    ASSERT_EQ(today.getYear(), tday.getYear());
}

TEST(Date, CurrentYear) {
    int year = Hotel::Date::currentYear();
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    EXPECT_EQ(1900 + ltm->tm_year, year);
}

TEST(Date, CurrentMonth) {
    int month = Hotel::Date::currentMonth();
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    EXPECT_EQ(ltm->tm_mon + 1, month);
}

TEST(Date, CurrentDay) {
    int day = Hotel::Date::currentDay();
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    EXPECT_EQ(ltm->tm_mday, day);
}

TEST(Date, GetString) {
    // 2020-01-01 - 10 char
    char str[11];
    Hotel::Date date(2020, 1, 1);
    date.getString(str);
    ASSERT_STREQ(str, "2020-01-01");
}

TEST(Date, FromString) {
    char str[11] = "2020-01-01";
    Hotel::Date date = Hotel::Date::fromString(str);
    char rstr[11];
    date.getString(rstr);
    ASSERT_STREQ(rstr, str);
}

TEST(Date, FromStringConstructor) {
    char str[11] = "2020-01-01";
    Hotel::Date date(str);
    char rstr[11];
    date.getString(rstr);
    ASSERT_STREQ(rstr, str);
}

TEST(Date, DaysBetweenStatic) {
    Hotel::Date start1(2011, 1, 1);
    Hotel::Date end1(2011, 12, 31);
    EXPECT_EQ(Hotel::Date::daysBetween(start1, end1), 365);
    EXPECT_EQ(Hotel::Date::daysBetween(end1, start1), 365);

    Hotel::Date start2(2012, 1, 1);
    Hotel::Date end2(2012, 12, 31);
    EXPECT_EQ(Hotel::Date::daysBetween(start2, end2), 366);
    EXPECT_EQ(Hotel::Date::daysBetween(end2, start2), 366);
    EXPECT_EQ(Hotel::Date::daysBetween(start2, start2), 1);

    Hotel::Date start3(2000, 1, 1);
    Hotel::Date end3(2002, 4, 12);
    EXPECT_EQ(Hotel::Date::daysBetween(start3, end3), 833);
    EXPECT_EQ(Hotel::Date::daysBetween(end3, start3), 833);
}

TEST(Date, DaysSince1900) {
    Hotel::Date d1(2000, 1, 1);
    EXPECT_EQ(Hotel::Date::daysSince1900(d1), 36525);
    Hotel::Date d2(2020, 3, 18);
    EXPECT_EQ(Hotel::Date::daysSince1900(d2), 43907);
}
