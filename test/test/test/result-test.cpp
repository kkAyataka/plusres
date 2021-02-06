#include "gtest/gtest.h"

#include "plusres/result.hpp"


TEST(Result, void_r) {
    const plusres::Result<> res = plusres::Void();

    EXPECT_EQ(res.ok(), true);
    EXPECT_EQ(res.error(), plusres::Error(plusres::Succeeded));
    EXPECT_NO_THROW(res.throw_error());
}

TEST(Result, int_r) {
    plusres::Result<int> res = 11;

    EXPECT_EQ(res.value(), 11);
    EXPECT_EQ(res.ok(), true);
    EXPECT_EQ(res.error(), plusres::Error(plusres::Succeeded));
    EXPECT_NO_THROW(res.throw_error());
}

TEST(Result, bool_r) {
    plusres::Result<bool> res = true;

    EXPECT_EQ(res.value(), true);
    EXPECT_EQ(res.ok(), true);
    EXPECT_EQ(res.error(), plusres::Error(plusres::Succeeded));
    EXPECT_NO_THROW(res.throw_error());
}
