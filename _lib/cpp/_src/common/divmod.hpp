#pragma once
#include "../base.hpp"

template<typename T>
pair<T, T> divmod(T a, T b) {
    T d = a / b;
    T m = a % b;
    return {d, m};
}
