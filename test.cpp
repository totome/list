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

    list<double> mylist;
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

    given=11;
    mylist.push_front(given);
    given=12;
    mylist.push_front(given);
    given=13;
    mylist.push_front(given);

    EXPECT_EQ(3, mylist.size());

    received = mylist.pop_front();
    EXPECT_EQ(13, received);
    EXPECT_EQ(2, mylist.size());

    received = mylist.pop_front();
    EXPECT_EQ(12, received);
    EXPECT_EQ(1, mylist.size());
}


TEST_F(FooTest, PopBackAndPushBackWorksProperly)
{
    int received = -1;
    int given=10;

    mylist.push_back(given);
    received = mylist.pop_back();

    EXPECT_EQ(given, received);

    given=11;
    mylist.push_back(given);
    given=12;
    mylist.push_back(given);
    given=13;
    mylist.push_back(given);

    EXPECT_EQ(3, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(13, received);
    EXPECT_EQ(2, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(12, received);
    EXPECT_EQ(1, mylist.size());
}

TEST_F(FooTest, PopBackAndPushFrontkWorksProperly)
{
    int received = -1;

    int given=10;
    mylist.push_front(given);
    given=11;
    mylist.push_front(given);
    given=12;
    mylist.push_front(given);
    given=13;
    mylist.push_front(given);

    EXPECT_EQ(4, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(10, received);
    EXPECT_EQ(3, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(11, received);
    EXPECT_EQ(2, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(12, received);
    EXPECT_EQ(1, mylist.size());

    received = mylist.pop_back();
    EXPECT_EQ(13, received);
    EXPECT_EQ(0, mylist.size());
    EXPECT_EQ(true, mylist.is_empty());

}

TEST_F(FooTest, joinTail)
{
    double received;
    list<double> resultList;
    list<double> listToJoin;
    resultList.push_back(21);
    resultList.push_back(22);
    resultList.push_back(23);
    resultList.push_front(20);

    listToJoin.push_front(24);
    listToJoin.push_back(25);

    resultList.join_tail(std::move(listToJoin));

    EXPECT_EQ(6, resultList.size());
    EXPECT_EQ(0, listToJoin.size());

    received = resultList.pop_back();
    EXPECT_EQ(25, received);

    received = resultList.pop_back();
    EXPECT_EQ(24, received);

    received = resultList.pop_back();
    EXPECT_EQ(23, received);
    received = resultList.pop_back();
    EXPECT_EQ(22, received);
}

TEST_F(FooTest, detach_head)
{
    double received;
    list<double> resultList;
    list<double> listToJoin;
    resultList.push_back(21);
    resultList.push_back(22);
    resultList.push_back(23);
    resultList.push_front(20);

    listToJoin.push_front(24);
    listToJoin.push_back(25);

    resultList.join_tail(std::move(listToJoin.detach_head()));
    resultList.join_tail(std::move(listToJoin.detach_head()));

    EXPECT_EQ(6, resultList.size());
    EXPECT_EQ(0, listToJoin.size());

    received = resultList.pop_back();
    EXPECT_EQ(25, received);

    received = resultList.pop_back();
    EXPECT_EQ(24, received);

    received = resultList.pop_back();
    EXPECT_EQ(23, received);
    received = resultList.pop_back();
    EXPECT_EQ(22, received);
}

TEST_F(FooTest, detach_half)
{
    double received;
    mylist.push_back(21);
    mylist.push_back(22);
    mylist.push_back(23);
    mylist.push_front(20);
    mylist.push_back(24);
    mylist.push_back(25);

    list<double> resultList;

    resultList.join_tail(std::move(mylist.detach_half()));

    EXPECT_EQ(3, resultList.size());
    EXPECT_EQ(3, mylist.size());

    received = resultList.pop_back();
    EXPECT_EQ(25, received);

    received = resultList.pop_back();
    EXPECT_EQ(24, received);

    received =resultList.pop_front();
    EXPECT_EQ(23, received);


    EXPECT_EQ(true, resultList.is_empty());
}



TEST_F(FooTest, merge_sortTwoElems)
{
    double received;
    mylist.push_back(22);
    mylist.push_back(21);

    mylist = merge_sort(std::move(mylist));


    EXPECT_EQ(2, mylist.size());
    received = mylist.pop_front();
    EXPECT_EQ(21, received);
    received = mylist.pop_front();
    EXPECT_EQ(22, received);


    EXPECT_EQ(1, 1);
}

TEST_F(FooTest, merge_sortElevenElems)
{
    double received;
    mylist.push_back(0);
    mylist.push_back(111);
    mylist.push_back(21);
    mylist.push_back(22);
    mylist.push_back(23);
    mylist.push_back(24);
    mylist.push_back(0);
    mylist.push_back(29);
    mylist.push_back(111);
    mylist.push_back(26);
    mylist.push_back(20);

    mylist = merge_sort(std::move(mylist));

    EXPECT_EQ(11, mylist.size());

    while(not mylist.is_empty())
    {
        std::cout<<mylist.pop_front()<<", ";
    }
    //received = mylist.pop_front();
    //EXPECT_EQ(21, received);
    //received = mylist.pop_front();
    //EXPECT_EQ(22, received);
    //received = mylist.pop_front();
    //EXPECT_EQ(23, received);
    //received = mylist.pop_front();
    //EXPECT_EQ(24, received);
    //received = mylist.pop_front();
    //EXPECT_EQ(25, received);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
