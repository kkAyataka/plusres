// Copyright (C) 2020 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSRES_ERROR_HPP__
#define PLUSRES_ERROR_HPP__

#include <deque>
#include <memory>
#include <stdexcept>


namespace plusres {

enum class Code {
    Succeeded = 0,
    Failed = 1,
};

static Code Succeeded = Code::Succeeded;
static Code Failed = Code::Failed;

class Error : public std::exception {
public:
    explicit Error(const Code code = Code::Failed) noexcept : Error(code, "") {}
    explicit Error(const char * what_a) noexcept : Error(Code::Failed, what_a) {}
    explicit Error(const std::string & what_a) noexcept : Error(Code::Failed, what_a) {}

    Error(
        const std::string & what_a,
        const Error & e
    ) : Error(Code::Failed, what_a) {
        stack_ = std::move(e.stack());
    }

    virtual ~Error() {
    }

protected:
    Error(
        const Code code,
        const std::string & what_a
    ) : code_(code),
        what_(what_a) {
    }

public:
    inline operator bool() const noexcept {
        return !ok();
    }

public:
    virtual bool ok() const noexcept {
        return (code_ == Code::Succeeded);
    }

    bool failed() const noexcept {
        return !ok();
    }

    virtual const char * what() const noexcept {
        return what_.c_str();
    }

    inline std::deque<std::shared_ptr<Error>> stack() const noexcept {
        auto s = stack_;
        s.push_back(std::make_shared<Error>(*this));
        return s;
    }

private:
    Code code_;
    std::string what_;
    std::deque<std::shared_ptr<Error>> stack_;
};

} // namespace plusres

#endif // PLUSRES_ERROR_HPP__
