#include "dbconn.hpp"
#include"googletest/googletest/include/gtest/gtest.h"
#include"googletest/googlemock/include/gmock/gmock.h"

#include <iostream>


class MockDBConnect : public IDBConnection
{
    public:
        MOCK_METHOD(bool, open, (std::string hostname), (override));
        MOCK_METHOD(bool, close_c, (), (override));
        MOCK_METHOD(bool, execQuery, (std::string query), (override));

};

TEST(ConnecterTest, test1)
{
    MockDBConnect mconn;

    EXPECT_CALL(mconn, open).Times(::testing::AtLeast(1));
    EXPECT_CALL(mconn, execQuery).Times(::testing::AtLeast(1));
    EXPECT_CALL(mconn, close_c).Times(::testing::AtLeast(1));

    ClassThatUsesDB caller;
    caller.openConnection(mconn);
    caller.useConnection(mconn,"");
    caller.closeConnection(mconn);
}
TEST(connectDB, test2)
{
    //check close first
    DBConnection dbconnect;
    EXPECT_TRUE(dbconnect.close_c()); // should fail test, cannot close before open
    ASSERT_TRUE(dbconnect.open("localhost"));
    ASSERT_TRUE(dbconnect.close_c());
}
TEST(useDB, test3)
{
    DBConnection dbconnect;
    ClassThatUsesDB caller;

    ASSERT_TRUE(caller.openConnection(dbconnect));
    EXPECT_EQ(caller.useConnection(dbconnect, ""), false);
    EXPECT_EQ(caller.useConnection(dbconnect, "someCommand"), true);
    EXPECT_EQ(caller.closeConnection(dbconnect), true);

}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}