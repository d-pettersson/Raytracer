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
};

TEST_F(TupleFixture, IsPoint) {
    ASSERT_TRUE(tuple->isPoint());
}

TEST_F(TupleFixture, IsVector) {
    ASSERT_TRUE(tuple->isVector());
}