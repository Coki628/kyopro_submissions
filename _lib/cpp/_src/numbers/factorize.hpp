#include "../base.hpp"

// 素因数分解(vectorベース)
template<typename T>
vector<pair<T, int>> factorize(T n) {
    vector<pair<T, int>> ret;
    for (T i=2; i*i<=n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        if (cnt) ret.emplace_back(i, cnt);
    }
    if (n > 1) ret.emplace_back(n, 1);
    return ret;
}
