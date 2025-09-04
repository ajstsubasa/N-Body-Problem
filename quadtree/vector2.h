#pragma once

#include <cmath>

namespace quadtree {

template <typename T> class PVector {
  public:
    T x;
    T y;

    constexpr PVector() noexcept : x(T(0)), y(T(0)) {}
    constexpr PVector(T X, T Y) noexcept : x(X), y(Y) {}

    // Compound vector ops
    constexpr PVector &operator+=(const PVector &other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr PVector &operator-=(const PVector &other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Compound scalar ops
    constexpr PVector &operator*=(T s) noexcept {
        x *= s;
        y *= s;
        return *this;
    }
    constexpr PVector &operator/=(T s) noexcept {
        x /= s;
        y /= s;
        return *this;
    }

    // Unary ops
    constexpr PVector operator+() const noexcept { return *this; }
    constexpr PVector operator-() const noexcept { return PVector(-x, -y); }

    // Length utilities
    constexpr T lengthSquared() const noexcept { return x * x + y * y; }
    T length() const noexcept {
        using std::sqrt;
        return sqrt(x * x + y * y);
    }

    // Normalization
    PVector normalized() const noexcept {
        T len = length();
        if (len == T(0))
            return PVector(T(0), T(0));
        return PVector(x / len, y / len);
    }
    void normalizeInPlace() noexcept {
        T len = length();
        if (len != T(0)) {
            x /= len;
            y /= len;
        }
    }

    // Backward-compat alias if you previously used norm()
    T norm() const noexcept { return length(); }

    // Helpers
    static constexpr PVector zero() noexcept { return PVector(T(0), T(0)); }
    static constexpr PVector unitX() noexcept { return PVector(T(1), T(0)); }
    static constexpr PVector unitY() noexcept { return PVector(T(0), T(1)); }
};

// Free operators (non-mutating)
template <typename T> constexpr PVector<T> operator+(PVector<T> lhs, const PVector<T> &rhs) noexcept {
    lhs += rhs;
    return lhs;
}

template <typename T> constexpr PVector<T> operator-(PVector<T> lhs, const PVector<T> &rhs) noexcept {
    lhs -= rhs;
    return lhs;
}

template <typename T> constexpr PVector<T> operator*(PVector<T> v, T s) noexcept {
    v *= s;
    return v;
}

template <typename T> constexpr PVector<T> operator*(T s, PVector<T> v) noexcept {
    v *= s;
    return v;
}

template <typename T> constexpr PVector<T> operator/(PVector<T> v, T s) noexcept {
    v /= s;
    return v;
}

// Comparisons

template <typename T> constexpr bool operator==(const PVector<T> &a, const PVector<T> &b) noexcept { return a.x == b.x && a.y == b.y; }

template <typename T> constexpr bool operator!=(const PVector<T> &a, const PVector<T> &b) noexcept { return !(a == b); }

// Dot product

template <typename T> constexpr T dot(const PVector<T> &a, const PVector<T> &b) noexcept { return a.x * b.x + a.y * b.y; }

} // namespace quadtree
