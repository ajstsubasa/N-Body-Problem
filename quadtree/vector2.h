#pragma once

#include <cmath>
namespace quadtree {

template <typename T> class PVector {
  public:
    T x;
    T y;

    constexpr PVector(T X = 0, T Y = 0) noexcept : x(X), y(Y) {}

    constexpr PVector<T> &operator+=(const PVector<T> &other) noexcept {
        x += other.x;
        y += other.y;
        return PVector<T>(x, y);
    }

    constexpr PVector<T> &operator/=(T t) noexcept {
        x /= t;
        y /= t;
        return PVector<T>(x, y);
    }

    constexpr T norm() noexcept { return std::sqrt(x * x + y * y); }

    constexpr PVector<T> &operator-(const PVector<T> &other) noexcept {
        x -= other.x;
        y -= other.y;
        return PVector<T>(x, y);
    }
};

template <typename T> constexpr PVector<T> operator+(PVector<T> lhs, const PVector<T> &rhs) noexcept {
    lhs += rhs;
    return PVector<T>(lhs.x, lhs.y);
}

template <typename T> constexpr PVector<T> operator/(PVector<T> vec, T t) noexcept {
    vec /= t;
    return PVector<T>(vec.x, vec.y);
}

template <typename T> constexpr PVector<T> operator*(PVector<T> vec, T t) noexcept { return PVector<T>(vec.x * t, vec.y * t); }
} // namespace quadtree
