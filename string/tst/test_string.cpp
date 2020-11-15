#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.hpp>
#include <cstring>

namespace
{
constexpr const char* smallString = "123456789012345";
constexpr size_t smallStringSize = strlen(smallString);

constexpr const char* bigString = "1234567890123456";
constexpr size_t bigStringSize = strlen(bigString);
} // anonymous namespace

struct TestDefaultConstructedString : public ::testing::Test
{
    mystd::string str;
    std::string std_str;
};

TEST_F(TestDefaultConstructedString, when_created__should_create_empty_string_of_size_zero)
{
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), 15);
    EXPECT_STREQ(str.c_str(), "");

    EXPECT_EQ(std_str.size(), 0);
    EXPECT_EQ(std_str.capacity(), 15);
    EXPECT_STREQ(std_str.c_str(), "");
}

TEST_F(TestDefaultConstructedString, when_small_string_assigned__size_and_capa_should_be_updated)
{
    str = smallString;
    EXPECT_EQ(str.size(), smallStringSize);
    EXPECT_EQ(str.capacity(), smallStringSize);
    EXPECT_STREQ(str.c_str(), smallString);

    std_str = smallString;
    EXPECT_EQ(std_str.size(), smallStringSize);
    EXPECT_EQ(std_str.capacity(), smallStringSize);
    EXPECT_STREQ(std_str.c_str(), smallString);
}

TEST_F(TestDefaultConstructedString, when_nullptr_assigned__should_not_change_object)
{
    str = nullptr;
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), 15);
    EXPECT_STREQ(str.c_str(), "");

    // SegFault raised
//    std_str = nullptr;
//    EXPECT_EQ(std_str.size(), 0);
//    EXPECT_EQ(std_str.capacity(), 15);
//    EXPECT_STREQ(std_str.c_str(), "");
}

TEST_F(TestDefaultConstructedString, when_big_string_assigned__memory_should_be_allocated)
{
    str = bigString;
    EXPECT_EQ(str.size(), bigStringSize);
    EXPECT_EQ(str.capacity(), smallStringSize * 2);
    EXPECT_STREQ(str.c_str(), bigString);

    std_str = bigString;
    EXPECT_EQ(std_str.size(), bigStringSize);
    EXPECT_EQ(std_str.capacity(), smallStringSize * 2);
    EXPECT_STREQ(std_str.c_str(), bigString);
}

TEST_F(TestDefaultConstructedString, when_dynamic_allocation_done__memory_should_be_released_when_string_is_deleted)
{
}

TEST_F(TestDefaultConstructedString, when_big_string_assigned_and_then_small_string_assigned__size_and_capacity_should_be_updated)
{
}
