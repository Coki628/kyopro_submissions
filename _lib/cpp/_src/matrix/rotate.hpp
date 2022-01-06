#include "../base.hpp"

// 参考：https://imagingsolution.net/math/rotate-around-point/
// (x, y)を中心に時計回り90度回転
template<typename T>
vector<vector<T>> rot90(T x, T y) {
    const vector<vector<T>> res = {
        {0, 1, x-y},
        {-1, 0, y+x},
        {0, 0, 1},
    };
    return res;
}
// (x, y)を中心に反時計回り90度回転
template<typename T>
vector<vector<T>> rot270(T x, T y) {
    const vector<vector<T>> res = {
        {0, -1, x+y},
        {1, 0, y-x},
        {0, 0, 1},
    };
    return res;
}
