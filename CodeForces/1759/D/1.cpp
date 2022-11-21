/*
・自力AC！
・素因数
・素因数で考えると、2,5が揃うと末尾0は1個増える。これで0の数は分かる。
　残りはこれを邪魔しないやつ全部使う感じ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    ll cnt2 = 0, cnt5 = 0;
    ll tmp = N;
    while (tmp%2 == 0) {
        tmp /= 2;
        cnt2++;
    }
    while (tmp%5 == 0) {
        tmp /= 5;
        cnt5++;
    }
    ll base = 1;
    while (cnt2 < cnt5 and base*2 <= M) {
        base *= 2;
        cnt2++;
    }
    while (cnt5 < cnt2 and base*5 <= M) {
        base *= 5;
        cnt5++;
    }
    ll cnt10 = min(cnt2, cnt5);
    while (base*10 <= M) {
        base *= 10;
        cnt10++;
    }
    // debug(cnt10);
    ll k = M / base * base;
    ll ans = N * k;
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
