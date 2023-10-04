/*
・自力AC！
・グリッド、縦横独立、ゲーム、複数山Nim、Grundy数
・縦と横を全く別のNim山だと思えば普通の複数山Nimに帰着する。
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
    ll N, H, W;
    cin >> N >> H >> W;
    vector<ll> A;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        A.eb(h - 1);
        A.eb(w - 1);
    }

    ll res = 0;
    rep(i, N * 2) {
        res ^= A[i];
    }
    if (res) {
        print("First");
    } else {
        print("Second");
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
