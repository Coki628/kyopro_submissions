/*
・きっちり自力AC！
・決め打ちにぶたん、オーバーフロー対策
・一見して決め打ちにぶたんでいけそうではある。
　雑にやるとINFがN回足されて死にそうな感じなので、
　上限を小さく整えようと思ったけど、案外大きめじゃないとダメそうだったので、
　考えるよりオーバーフロー判定入れて通した。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, X;
    cin >> N >> X;
    vector<ll> A(N);
    cin >> A;

    ll res = bisearch_max(0, INF, [&](ll h) {
        ll cnt = 0;
        rep(i, N) {
            if (add_overflow(cnt, max(h - A[i], 0LL))) {
                return false;
            }
            cnt += max(h - A[i], 0LL);
        }
        return cnt <= X;
    });
    print(res);
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
