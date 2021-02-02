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

class Error : public std::exception {
public:
    explicit Error(const bool is_failed = true) noexcept : Error(is_failed, "") {}
    explicit Error(const char * what_a) noexcept : Error(true, what_a) {}
    explicit Error(const std::string & what_a) noexcept : Error(true, what_a) {}

    Error(
        const std::string & what_a,
        const Error & e
    ) : Error(true, what_a) {
        stack_ = std::move(e.stack());
    }

    virtual ~Error() {
    }

protected:
    Error(
        const bool is_failed,
        const std::string & what_a
    ) : is_failed_(is_failed),
        what_(what_a) {
    }

public:
    inline  operator bool() const noexcept {
        return !ok();
    }

public:
    virtual bool ok() const noexcept {
        return !is_failed_;
    }

    virtual bool ng() const noexcept {
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

protected:
    bool is_failed_;
    std::string what_;
    std::deque<std::shared_ptr<Error>> stack_;
};

} // namespace plusres

#endif // PLUSRES_ERROR_HPP__
