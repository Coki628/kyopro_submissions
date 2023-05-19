/*
・別方針が立ったので合ってるか確認のため書いた。無事AC。
・bitDP、部分集合列挙
・先に1本の鍵単体で開けれる全ての部分集合で最小コストを出しておく。
　あとは各ビットの状態で部分集合マージを全部やれば最終的な最小コストも出る、はず。
　数えるコストが重複しないか心配だったけど、やってみたらちゃんと合ってた。
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
    vector<ll> A(M), C(M);
    rep(i, M) {
        cin >> A[i];
        ll sz;
        cin >> sz;
        vector<ll> tmp(sz);
        cin >> tmp;
        tmp--;
        for (auto b : tmp) {
            C[i] += 1 << b;
        }
    }

    vector<ll> dp(1 << N, INF);
    rep(i, M) {
        chmin(dp[C[i]], A[i]);
        ll T = C[i];
        while (T > 0) {
            T = (T - 1) & C[i];
            chmin(dp[T], A[i]);
        }
    }
    rep(S, 1 << N) {
        ll T = S;
        while (T > 0) {
            T = (T - 1) & S;
            chmin(dp[S], dp[T] + dp[S ^ T]);
        }
    }
    ll ans = dp[(1 << N) - 1];
    if (ans == INF) {
        ans = -1;
    }
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
