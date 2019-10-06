#include "utils.h"

#include "gtest/gtest.h"

class GenFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        gen = new raytracer::Gen();

    }

    virtual void TearDown() {
        delete gen;

    }

    raytracer::Gen * gen;

};

TEST_F(GenFixture, TestSequence) {
    std::vector<float> s{0.1, 0.5, 1.0};
    gen->sequence = s;
    ASSERT_FLOAT_EQ(0.1, gen->next());
    ASSERT_FLOAT_EQ(0.5, gen->next());
    ASSERT_FLOAT_EQ(1.0, gen->next());
    ASSERT_FLOAT_EQ(0.1, gen->next());

}