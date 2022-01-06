#pragma once
#include "../macros.hpp"

template<typename T>
struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
    Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
    Point operator*(const Point &p) { return {x*p.x, y*p.y}; }
    Point operator/(const Point &p) { return {x/p.x, y/p.y}; }
    Point &operator+=(const Point &p) { x += p.x, y += p.y; return *this; }
    Point &operator-=(const Point &p) { x -= p.x, y -= p.y; return *this; }
    Point &operator*=(const Point &p) { x *= p.x, y *= p.y; return *this; }
    Point &operator/=(const Point &p) { x /= p.x, y /= p.y; return *this; }
    bool operator<(const Point &p) { return mkp(x, y) < mkp(p.x, p.y); }
    bool operator==(const Point &p) { return std::abs(x-p.x) < EPS and std::abs(y-p.y) < EPS; }
    bool operator!=(const Point &p) { return std::abs(x-p.x) >= EPS or std::abs(y-p.y) >= EPS; }
    Point operator*(T k) { return {x*k, y*k}; }
    Point operator/(T k) { return {x/k, y/k}; }
    T norm() { return x*x + y*y; }
    T abs() { return sqrt(norm()); }
    T abs(const Point &p) { return hypot(x-p.x, y-p.y); }
    T abs2(const Point &p) { return pow(x-p.x, 2)+pow(y-p.y, 2); }
    T manhattan(const Point &p) { return std::abs(x-p.x) + std::abs(y-p.y); }
    void print() { cout << x << ' ' << y << '\n'; }
};
