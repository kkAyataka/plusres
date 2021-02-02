// Copyright (C) 2020 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSRES_RESULT_HPP__
#define PLUSRES_RESULT_HPP__

#include "error.hpp"


namespace plusres {

/** Base class of the Result */
template<typename V, typename E>
class ResultBase {
public:
    ResultBase(
        const V & v,
        const E & e
    ) noexcept : value_(v),
        error_(e) {
    }

    ResultBase(
        const V && v,
        const E && e
    ) noexcept : value_(std::move(v)),
        error_(std::move(e)) {
    }

    virtual ~ResultBase() {}

public:
    inline operator bool() const {
        return error_;
    }

    inline operator V() noexcept(false) {
        if (error_) {
            throw error_;
        }
        else {
            return value_;
        }
    }

public:
    inline const E & error() const { return error_; }
    inline V & value() { return value_; }

private:
    V value_;
    E error_;
};

/** Default empty value class */
struct Void {
};

/**
 * Default Result class with plusres::Error
 */
template<typename V = Void>
class Result : public ResultBase<V, plusres::Error> {
public:
    Result(const V & v) noexcept : ResultBase<V, Error>(v, Error(false)) {}
    Result(const V && v) noexcept : ResultBase<V, Error>(std::move(v), Error(false)) {}
    Result(const Error & e) noexcept : ResultBase<V, Error>(V(), e) {}

    virtual ~Result() {}
};

} // namespace plusres

#endif // PLUSRES_RESULT_HPP__