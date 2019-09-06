#include "gtest/gtest.h"
#include "../RTC_lib/Tuple.h"

class TupleFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        tuple = new Tuple();
    }

    virtual void TearDown() {
        delete tuple;
    }

    Tuple * tuple;
    Tuple point;
    Tuple vector;
};

TEST_F(TupleFixture, IsPoint) {
    ASSERT_FALSE(tuple->isPoint());
}

TEST_F(TupleFixture, IsVector) {
    ASSERT_TRUE(tuple->isVector());
}

TEST_F(TupleFixture, CreatePoint) {
    point = createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(point.isPoint());
}

TEST_F(TupleFixture, CreateVector) {
    vector = createVector(1.0, 1.0, 1.0);
    ASSERT_TRUE(vector.isVector());
}

TEST_F(TupleFixture, VerifyEquality) {
    point = createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(isEqual(point, point));
}

TEST_F(TupleFixture, TupleAddition) {
    Tuple t1{3, -2, 5, 1};
    Tuple t2{-2, 3, 1, 0};
    Tuple result{1, 1, 6, 1};
    ASSERT_EQ(result, t1 + t2);
}