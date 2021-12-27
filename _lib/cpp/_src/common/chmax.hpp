#pragma once

template<typename T> bool chmax(T &x, T y) {
    return (y > x) ? x = y, true : false;
}
