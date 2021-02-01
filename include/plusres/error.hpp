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
    explicit Error(const char * message) noexcept : Error(true, message) {}
    explicit Error(const std::string & message) noexcept : Error(true, message) {}

    Error(
        const std::string & message,
        const Error & e
    ) : Error(true, message) {
        stack_ = std::move(e.stack());
    }

    virtual ~Error() {
    }

protected:
    Error(
        const bool is_failed,
        const std::string & message
    ) : is_failed_(is_failed),
        message_(message) {
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

    inline const std::string & message() const noexcept {
        return message_;
    }

    inline std::deque<std::shared_ptr<Error>> stack() const noexcept {
        auto s = stack_;
        s.push_back(std::make_shared<Error>(*this));
        return s;
    }

protected:
    bool is_failed_;
    std::string message_;
    std::deque<std::shared_ptr<Error>> stack_;
};

} // namespace plusres

#endif // PLUSRES_ERROR_HPP__
