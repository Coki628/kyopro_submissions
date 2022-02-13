#include "../FormalPowerSeries.hpp"

// 繰り返し二乗法
template<typename T>
FPS<T> pow(FPS<T> A, ll k, int deg=-1) {
    int n = deg;
    if (deg == -1) n = A.size();
    FPS<T> res(deg);
    res[0] = 1;
    while (k > 0) {
        if (k & 1) {
            res *= A;
            res.shrink(deg);
        }
        A *= A;
        A.shrink(deg);
        k >>= 1;
    }
    return res;
}
