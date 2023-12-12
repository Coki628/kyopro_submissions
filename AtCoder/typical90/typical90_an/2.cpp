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
    ll N, W;
    cin >> N >> W;
    vector<ll> A(N);
    cin >> A;

    PSP psp(N);
    rep(i, N) {
        // 家iに入らない/入る
        psp.add(i, 0, A[i] - W);
    }

    rep(u, N) {
        ll K;
        cin >> K;
        rep(_, K) {
            ll v;
            cin >> v;
            v--;
            // vを選ぶならuも選ばないといけない
            psp.a_right_then_b_right(v, u);
        }
    }

    auto res = psp.solve();
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
