#include "../base.hpp"

// x = p で反転
template<typename T>
vector<vector<T>> flip_x(T p) {
    const vector<vector<T>> res = {
        {-1, 0, 2*p},
        {0, 1, 0},
        {0, 0, 1},
    };
    return res;
}
// y = p で反転
template<typename T>
vector<vector<T>> flip_y(T p) {
    const vector<vector<T>> res = {
        {1, 0, 0},
        {0, -1, 2*p},
        {0, 0, 1},
    };
    return res;
}
