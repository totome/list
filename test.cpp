#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "list.hpp"

namespace {

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FooTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

    list<int> mylist;
  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, WhenListIsEmptyThenSizeIsZeroAndIsEmptyISTrue)
{
    EXPECT_EQ(0, mylist.size());
    EXPECT_EQ(true, mylist.is_empty());
}

TEST_F(FooTest, WhenListIsNotEmptyThenSizeIsNotZeroAndIsEmptyIsFalse)
{
    mylist.push_front(111);
    EXPECT_NE(0, mylist.size());
    EXPECT_EQ(false, mylist.is_empty());
}

TEST_F(FooTest, SizeIsSameAsItShouldBeAfterPushFront)
{
    mylist.push_front(111);
    mylist.push_front(111);
    mylist.push_front(111);
    mylist.push_front(111);
    EXPECT_EQ(4, mylist.size());
}

TEST_F(FooTest, PopFrontAndPushFrontWorksProperly)
{
    int given=10;
    int received = -1;

    mylist.push_front(given);
    received = mylist.pop_front();

    EXPECT_EQ(given, received);

    given++;
    mylist.push_front(given);
    given++;
    mylist.push_front(given);
    given++;
    mylist.push_front(given);
    EXPECT_EQ(3, mylist.size());

    received = mylist.pop_front();
    EXPECT_EQ(given, received);
    EXPECT_EQ(2, mylist.size());

    received = mylist.pop_front();
    EXPECT_EQ(given, received);
    EXPECT_EQ(1, mylist.size());
}


TEST_F(FooTest, PopFrontAndPushFrontWorksProperly2)
{
    int given=10;
    int received = 11;

    mylist.push_front(given);
    received = mylist.pop_front();
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
