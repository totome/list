#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "list.hpp"
#include "quick_sort.h"
#include "merge_sort.h"

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

TEST_F(FooTest, RandomAccesIteratorGivesHisValue)
{
    mylist.push_back(10);//0
    mylist.push_back(11);//1
    mylist.push_back(12);//2
    mylist.push_back(13);//3
    mylist.push_back(14);//4
    mylist.push_back(15);//5
    mylist.push_back(16);//6
    mylist.push_back(17);//7
    mylist.push_back(18);//8
    mylist.push_back(19);//9
    mylist.push_back(20);//10

    EXPECT_EQ(11, mylist.size());

    EXPECT_EQ(10, mylist[0]);
    EXPECT_EQ(20, mylist[10]);
    using std::swap;
    swap(mylist[1], mylist[2]);
    EXPECT_EQ(12, mylist[1]);
    EXPECT_EQ(11, mylist[2]);

    mylist[10]=mylist[7];
    EXPECT_EQ(17, mylist[10]);
    EXPECT_EQ(17, mylist[7]);
}





TEST_F(FooTest, merge_sortOneElem)
{
    mylist.push_back(111);

    mylist = merge_sort(std::move(mylist));

    EXPECT_EQ(1, mylist.size());
    EXPECT_EQ(111, mylist[0]);
}

TEST_F(FooTest, merge_sortTwoElems)
{
    mylist.push_back(222);
    mylist.push_back(111);

    mylist = merge_sort(std::move(mylist));

    EXPECT_EQ(2, mylist.size());


    EXPECT_EQ(111, mylist[0]);
    EXPECT_EQ(222, mylist[1]);
}

TEST_F(FooTest, merge_sortElevenElems)
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

    mylist = merge_sort(std::move(mylist));

    EXPECT_EQ(11, mylist.size());

    EXPECT_EQ(0, mylist[0]);
    EXPECT_EQ(0,  mylist[1]);
    EXPECT_EQ(20,  mylist[2]);
    EXPECT_EQ(21, mylist[3]);
    EXPECT_EQ(22, mylist[4]);
    EXPECT_EQ(23, mylist[5]);
    EXPECT_EQ(24, mylist[6]);
    EXPECT_EQ(26, mylist[7]);
    EXPECT_EQ(29, mylist[8]);
    EXPECT_EQ(111, mylist[9]);
    EXPECT_EQ(111, mylist[10]);
}

TEST_F(FooTest, quick_sortOneElem)
{
    mylist.push_back(111);

    int n = mylist.size();
    EXPECT_EQ(1, mylist.size());
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(1, mylist.size());
    EXPECT_EQ(111, mylist[0]);
}

TEST_F(FooTest, quick_sortTwoElems)
{
    mylist.push_back(222);
    mylist.push_back(111);

    int n = mylist.size();
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(2, mylist.size());


    EXPECT_EQ(111, mylist[0]);
    EXPECT_EQ(222, mylist[1]);
}
TEST_F(FooTest, quick_sortThreElems)
{
    mylist.push_back(222);
    mylist.push_back(111);
    mylist.push_back(333);

    int n = mylist.size();
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(3, mylist.size());


    EXPECT_EQ(111, mylist[0]);
    EXPECT_EQ(222, mylist[1]);
    EXPECT_EQ(333, mylist[2]);
}

TEST_F(FooTest, quick_sortFourElems)
{

    mylist.push_back(444);
    mylist.push_back(333);
    mylist.push_back(222);
    mylist.push_back(111);

    int n = mylist.size();
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(4, mylist.size());


    EXPECT_EQ(111, mylist[0]);
    EXPECT_EQ(222, mylist[1]);
    EXPECT_EQ(333, mylist[2]);
    EXPECT_EQ(444, mylist[3]);
}

TEST_F(FooTest, quick_sortFiveElems)
{

    mylist.push_back(555);
    mylist.push_back(444);
    mylist.push_back(333);
    mylist.push_back(222);
    mylist.push_back(111);

    int n = mylist.size();
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(5, mylist.size());


    EXPECT_EQ(111, mylist[0]);
    EXPECT_EQ(222, mylist[1]);
    EXPECT_EQ(333, mylist[2]);
    EXPECT_EQ(444, mylist[3]);
    EXPECT_EQ(555, mylist[4]);
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

    int n = mylist.size();
    quick_sort(mylist, 0, n-1);

    EXPECT_EQ(11, mylist.size());

    EXPECT_EQ(0, mylist[0]);
    EXPECT_EQ(0,  mylist[1]);
    EXPECT_EQ(20,  mylist[2]);
    EXPECT_EQ(21, mylist[3]);
    EXPECT_EQ(22, mylist[4]);
    EXPECT_EQ(23, mylist[5]);
    EXPECT_EQ(24, mylist[6]);
    EXPECT_EQ(26, mylist[7]);
    EXPECT_EQ(29, mylist[8]);
    EXPECT_EQ(111, mylist[9]);
    EXPECT_EQ(111, mylist[10]);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
