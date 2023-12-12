/*
ライブラリ整備：燃やす埋める
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

#include "graph/PSP.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> P(N);
    cin >> P;

    PSP psp(N);
    rep(i, N) {
        // この駅を選ばない/選ぶ
        psp.add(i, 0, P[i]);
    }
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        // 駅aを選ぶなら駅bも選ぶ
        psp.a_right_then_b_right(a, b);
    }
    auto ans = psp.solve();
    print(ans);
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
