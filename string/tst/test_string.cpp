#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "string.hpp"
#include "stubs/AllocStub.hpp"
#include <cstring>

namespace
{
constexpr const char* smallString = "123456789012345";
const size_t smallStringSize = strlen(smallString);

constexpr const char* string16 = "1234567890123456";
const size_t string16Size = strlen(string16);

constexpr const char* string25 = "1234567890123456789012345";
const size_t string25Size = strlen(string25);

constexpr const char* string31 = "1234567890123456789012345678901";
const size_t string31Size = strlen(string31);

constexpr const char* string32 = "12345678901234567890123456789012";
const size_t string32Size = strlen(string32);
} // anonymous namespace

struct TestDefaultConstructedString : public ::testing::Test
{
    void SetUp() override
    {
        resetAllocStats();
    }

    mystd::string<AllocStub<100>> str;
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

TEST_F(TestDefaultConstructedString, when_first_big_string_assigned__memory_should_be_allocated_with_size_fitted_to_new_string_size)
{
    const std::size_t expectedCapacityAfterFirstAssignment{string31Size};
    const std::size_t expectedCapacityAfterSecondAssignment{string31Size * 2};

    str = string31;
    EXPECT_EQ(str.size(), string31Size);
    EXPECT_EQ(str.capacity(), expectedCapacityAfterFirstAssignment);
    EXPECT_STREQ(str.c_str(), string31);

    std_str = string31;
    EXPECT_EQ(std_str.size(), string31Size);
    EXPECT_EQ(std_str.capacity(), expectedCapacityAfterFirstAssignment);
    EXPECT_STREQ(std_str.c_str(), string31);

    std_str = string32;
    EXPECT_EQ(std_str.size(), string32Size);
    EXPECT_EQ(std_str.capacity(), expectedCapacityAfterSecondAssignment);
    EXPECT_STREQ(std_str.c_str(), string32);
}

TEST_F(TestDefaultConstructedString, when_dynamic_allocation_done__memory_should_be_released_when_string_is_deleted)
{
    constexpr std::size_t expectedNumOfAllocDeallocCount{1};

    {
        mystd::string<AllocStub<100>> s;
        s = string16;
    }

    EXPECT_EQ(allocCount, deallocCount);
    EXPECT_EQ(allocCount, expectedNumOfAllocDeallocCount);
}

TEST_F(TestDefaultConstructedString, when_big_string_assigned_and_then_another_string_smaller_than_current_capacity_assigned__size_should_be_updated)
{
    const std::size_t expectedCapacity{string16Size};

    str = string16;
    str = smallString;

    EXPECT_EQ(str.size(), smallStringSize);
    EXPECT_EQ(str.capacity(), expectedCapacity);
    EXPECT_STREQ(str.c_str(), smallString);
}

TEST_F(TestDefaultConstructedString, when_big_string_assigned_and_then_bigger_string_assigned__capacity_should_be_doubled)
{
    const std::size_t expectedCapacityAfterFirstAssignment{string25Size};
    const std::size_t expectedCapacityAfterSecondAssignment{string25Size * 2};

    str = string25;
    EXPECT_EQ(str.size(), string25Size);
    EXPECT_EQ(str.capacity(), expectedCapacityAfterFirstAssignment);
    EXPECT_STREQ(str.c_str(), string25);
    EXPECT_EQ(allocBytes, expectedCapacityAfterFirstAssignment + 1);
    EXPECT_EQ(deallocBytes, expectedCapacityAfterFirstAssignment + 1);

    str = string31;
    EXPECT_EQ(str.size(), string31Size);
    EXPECT_EQ(str.capacity(), expectedCapacityAfterSecondAssignment);
    EXPECT_STREQ(str.c_str(), string31);
    EXPECT_EQ(allocBytes, expectedCapacityAfterSecondAssignment + 1);
    EXPECT_EQ(deallocBytes, expectedCapacityAfterSecondAssignment + 1);
}
