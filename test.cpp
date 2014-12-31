#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "list.hpp"


namespace {

class FooTest : public ::testing::Test {
 protected:

  FooTest() {
  }

  virtual ~FooTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

    list<double> mylist;
};

TEST_F(FooTest, WhenListIsEmptyThenSizeIsZeroAndIsEmptyISTrue)
{
    EXPECT_EQ(0u, mylist.size());
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
    EXPECT_EQ(0, mylist.size());
    mylist.push_front(111);
    EXPECT_EQ(1, mylist.size());
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
    EXPECT_EQ(4, resultList.size());
    EXPECT_EQ(2, listToJoin.size());

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


TEST_F(FooTest, ReverseIteratorGivesHisValue)
{
    mylist.push_back(10);
    mylist.push_back(11);
    mylist.push_back(12);
    mylist.push_back(13);
    mylist.push_back(14);
    mylist.push_back(15);
    mylist.push_back(16);
    mylist.push_back(17);
    mylist.push_back(18);
    mylist.push_back(19);
    mylist.push_back(20);

    auto it = mylist.begin();

    EXPECT_EQ(11, mylist.size());

    EXPECT_EQ(10, *it);
    EXPECT_EQ(10, *it);
    EXPECT_EQ(10, *(it++));
    EXPECT_EQ(11, *it);
    it++;
    ++it;
    it++;
    EXPECT_EQ(14, *it);
}

TEST_F(FooTest, detach)
{
    double received;
    mylist.push_back(21);
    mylist.push_back(22);
    mylist.push_back(23);
    mylist.push_front(20);
    mylist.push_back(24);
    mylist.push_back(25);

    list<double>::iterator it = mylist.begin();

    EXPECT_EQ(6, mylist.size());

    ++it;
    ++it;
    ++it;

    list<double> toCheck(mylist.detach(it));

    EXPECT_EQ(1, toCheck.size());
    EXPECT_EQ(5, mylist.size());
    EXPECT_EQ(23, toCheck.pop_front());

    it = mylist.begin();

    toCheck.join_tail(std::move(mylist.detach(it)));

    EXPECT_EQ(1, toCheck.size());
    EXPECT_EQ(4, mylist.size());
    EXPECT_EQ(20, toCheck.pop_front());
}
/*
TEST_F(FooTest, quick_sortOneElem)
{
    mylist.push_back(111);

    EXPECT_EQ(1, mylist.size());

    mylist.quick_sort();

    EXPECT_EQ(1, mylist.size());
    EXPECT_EQ(111, mylist.pop_back());
}


TEST_F(FooTest, quick_sortTwoElems)
{
    mylist.push_back(222);
    mylist.push_back(111);

    mylist.quick_sort();

    ASSERT_EQ(2, mylist.size());


    EXPECT_EQ(111, mylist.pop_front());
    EXPECT_EQ(222, mylist.pop_front());
}
TEST_F(FooTest, quick_sortThreElems)
{
    mylist.push_back(222);
    mylist.push_back(111);
    mylist.push_back(333);

    mylist.quick_sort();
    EXPECT_EQ(3, mylist.size());


    EXPECT_EQ(111, mylist.pop_front());
    EXPECT_EQ(222, mylist.pop_front());
    EXPECT_EQ(333, mylist.pop_front());
}

TEST_F(FooTest, quick_sortFourElems)
{

    mylist.push_back(444);
    mylist.push_back(333);
    mylist.push_back(222);
    mylist.push_back(111);

    mylist.quick_sort();
    EXPECT_EQ(4, mylist.size());


    EXPECT_EQ(111, mylist.pop_front());
    EXPECT_EQ(222, mylist.pop_front());
    EXPECT_EQ(333, mylist.pop_front());
    EXPECT_EQ(444, mylist.pop_front());
}

TEST_F(FooTest, quick_sortFiveElems)
{

    mylist.push_back(555);
    mylist.push_back(444);
    mylist.push_back(333);
    mylist.push_back(222);
    mylist.push_back(111);

    mylist.quick_sort();
    EXPECT_EQ(5, mylist.size());


    EXPECT_EQ(111, mylist.pop_front());
    EXPECT_EQ(222, mylist.pop_front());
    EXPECT_EQ(333, mylist.pop_front());
    EXPECT_EQ(444, mylist.pop_front());
    EXPECT_EQ(555, mylist.pop_front());
}

TEST_F(FooTest, quick_sortElevenElems)
{
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

    mylist.quick_sort();
    EXPECT_EQ(11, mylist.size());

    EXPECT_EQ(0, mylist.pop_front());
    EXPECT_EQ(0, mylist.pop_front());
    EXPECT_EQ(20, mylist.pop_front());
    EXPECT_EQ(21, mylist.pop_front());
    EXPECT_EQ(22, mylist.pop_front());
    EXPECT_EQ(23, mylist.pop_front());
    EXPECT_EQ(24, mylist.pop_front());
    EXPECT_EQ(26, mylist.pop_front());
    EXPECT_EQ(29, mylist.pop_front());
    EXPECT_EQ(111, mylist.pop_front());
    EXPECT_EQ(111, mylist.pop_front());
}

TEST_F(FooTest, select0fromOneElemList)
{
    mylist.push_back(111);

    EXPECT_EQ(1, mylist.size());

    double selected_0 = mylist.select(0);

    EXPECT_EQ(1, mylist.size());
    EXPECT_EQ(111, selected_0);
}

TEST_F(FooTest, select0fromTwoElemList)
{
    mylist.push_back(222);
    mylist.push_back(111);

    EXPECT_EQ(2, mylist.size());

    double selected_0 = mylist.select(0);

    EXPECT_EQ(2, mylist.size());
    EXPECT_EQ(111, selected_0);
}

TEST_F(FooTest, select1fromTwoElemList)
{
    mylist.push_back(222);
    mylist.push_back(111);

    EXPECT_EQ(2, mylist.size());

    double selected_1 = mylist.select(1);

    EXPECT_EQ(2, mylist.size());
    EXPECT_EQ(222, selected_1);
}
*/

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
