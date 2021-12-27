#pragma once

template<typename T> bool chmin(T &x, T y) {
    return (y < x) ? x = y, true : false;
}
