#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Interface
{
public:
    virtual ~Interface() = default;

    int fuu(int i, float f)
    {
        return boo(f) + foo(i) * 2;
    }

private:
    virtual int boo(float) const = 0;
    virtual int foo(int) = 0;
};

class InterfaceMock : public Interface
{
public:
    MOCK_METHOD(int, foo, (int));
    MOCK_METHOD(int, boo, (float), (const));
};

TEST(Test1, should_fail)
{
    EXPECT_TRUE(false);
}

using ::testing::Return;
using ::testing::_;

TEST(Test2, fuu_should_pass)
{
    InterfaceMock mock;

    EXPECT_CALL(mock, boo(5.0)).WillOnce(Return(10));
    EXPECT_CALL(mock, foo(_)).WillOnce(Return(2));

    EXPECT_EQ(mock.fuu(1, 5.0), 14);
}
