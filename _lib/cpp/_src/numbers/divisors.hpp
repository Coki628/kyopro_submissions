#include "../macros.hpp"

// 約数列挙
template<typename T>
vector<T> divisors(T n) {
    vector<T> res;
    for (T i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.eb(i);
            if (n/i != i) res.eb(n/i);
        }
    }
    // sort(ALL(res));
    return res;
}
