#include "gtest/gtest.h"

#include "plusres/result.hpp"


TEST(Result, void_r) {
    const plusres::Result<> res = plusres::Void();

    EXPECT_EQ((bool)res, true);
    EXPECT_EQ(res.error(), plusres::Error(false));
    EXPECT_NO_THROW(res.throw_error());
}

TEST(Result, int_r) {
    plusres::Result<int> res = 11;

    EXPECT_EQ(res.value(), 11);
    EXPECT_EQ((bool)res, true);
    EXPECT_EQ(res.error(), plusres::Error(false));
    EXPECT_NO_THROW(res.throw_error());

    plusres::Result<int> res = false;
}
