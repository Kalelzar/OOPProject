#include "Nullable.hpp"
#include "gtest/gtest.h"

TEST(Nullable, IsEmpty){
    NotNull<int> notNull(5);
    Null<int> null;
    EXPECT_FALSE(notNull.isEmpty());
    EXPECT_TRUE(null.isEmpty());
}

TEST(Nullable, IsDefined){
    NotNull<int> notNull(5);
    Null<int> null;
    EXPECT_TRUE(notNull.isDefined());
    EXPECT_FALSE(null.isDefined());
}

TEST(Nullable, Get){
    NotNull<int> notNull(5);
    Null<int> null;
    EXPECT_EQ(notNull.get(), 5);
    EXPECT_THROW(null.get(), NoValueException);
}

TEST(Nullable, GetOrElse){
    NotNull<int> notNull(5);
    Null<int> null;
    EXPECT_EQ(notNull.getOrElse(4), 5);
    EXPECT_EQ(null.getOrElse(4), 4);
}
