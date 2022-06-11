/*
・きっちり自力AC！
・これもにぶたん。ソートして累積和取って、にぶたんしてxより大小に分けて足し引き。
　足し引きする部分は、二次元平面で考えて、
　四角の所と三角の所で分けるみたいな図を書くと分かりやすいやつ。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    sort(ALL(A));
    Accumulate<ll> acc(A);
    rep(_, Q) {
        ll x;
        cin >> x;

        ll i = bisect_left(A, x);
        ll res = 0;
        res += x*i - acc.query(0, i);
        res += acc.query(i, N) - x*(N-i);
        print(res);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
