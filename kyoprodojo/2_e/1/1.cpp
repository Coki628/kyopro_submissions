/*
・arc037_c
・これはさすがに自力AC！
・決め打ち二分探索、K番目の値
・今となってはド典型のやつ。それでも境界の微調整バグらせてもたついたのは本当に反省ね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);
    auto B = LIST(N);

    sort(ALL(A));
    sort(ALL(B));
    // x以下の数はK個以上あるか
    ll res = bisearch_min(0, INF, [&](ll x) {
        ll cnt = 0;
        rep(i, N) {
            cnt += bisect_right(A, x/B[i]);
        }
        return cnt >= K;
    });
    print(res);
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
