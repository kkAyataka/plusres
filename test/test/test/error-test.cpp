#include "gtest/gtest.h"

#include "plusres/error.hpp"


TEST(Error, init_def) {
    plusres::Error e;
    const auto stack = e.stack();

    EXPECT_EQ(e, true);
    EXPECT_EQ(e.ok(), false);
    EXPECT_EQ(e.ng(), true);
    EXPECT_EQ(e.what(), std::string(""));
    EXPECT_EQ(stack.size(), 1);
}

struct InitTestParam {
    std::string desc;
    bool is_error;
    std::string what;
};

std::ostream & operator<<(std::ostream & os, const InitTestParam & p) {
    return os << p.desc;
}

class InitTest : public testing::TestWithParam<InitTestParam> {
};

TEST_P(InitTest, init_error) {
    const auto p = this->GetParam();

    const plusres::Error e(p.is_error);
    const auto stack = e.stack();

    EXPECT_EQ(e, p.is_error);
    EXPECT_EQ(e.ok(), !p.is_error);
    EXPECT_EQ(e.ng(), p.is_error);
    EXPECT_EQ(e.what(), std::string(""));
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack[0]->what(), std::string(""));
}

TEST_P(InitTest, init_what_s) {
    const auto p = this->GetParam();

    const plusres::Error e(p.what);
    const auto stack = e.stack();

    EXPECT_EQ(e, true);
    EXPECT_EQ(e.ok(), false);
    EXPECT_EQ(e.ng(), true);
    EXPECT_EQ(e.what(), std::string(p.what));
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack[0]->what(), std::string(p.what));
}

TEST_P(InitTest, init_what_c) {
    const auto p = this->GetParam();

    const plusres::Error e(p.what.c_str());
    const auto stack = e.stack();

    EXPECT_EQ(e, true);
    EXPECT_EQ(e.ok(), false);
    EXPECT_EQ(e.ng(), true);
    EXPECT_EQ(e.what(), std::string(p.what));
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack[0]->what(), std::string(p.what));
}

INSTANTIATE_TEST_SUITE_P(
    Error,
    InitTest,
    testing::Values(
        InitTestParam{"false", false, "error"},
        InitTestParam{"true", true, "not error"}
    ),
    testing::PrintToStringParamName()
);

TEST(Error, stack) {
    const plusres::Error e1("1");
    const auto s1 = e1.stack();
    EXPECT_EQ(s1.size(), 1);
    EXPECT_EQ(s1[0]->what(), std::string("1"));

    const plusres::Error e2("2", e1);
    const auto s2 = e2.stack();
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2[0]->what(), std::string("1"));
    EXPECT_EQ(s2[1]->what(), std::string("2"));

    const plusres::Error e3("3", e2);
    const auto s3 = e3.stack();
    EXPECT_EQ(s3.size(), 3);
    EXPECT_EQ(s3[0]->what(), std::string("1"));
    EXPECT_EQ(s3[1]->what(), std::string("2"));
    EXPECT_EQ(s3[2]->what(), std::string("3"));
}
