/*
・きっちり自力AC！
・期待値DP、メモ化再帰
・ちょっと題意のゲームのルールがややこしいが、
　期待値DPのいつもの手順通りに、遷移を丁寧に整えていけばOK。
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
    ll N, t, p;
    cin >> N >> t >> p;
    vector<ll> A(N);
    cin >> A;

    auto memo = listnd(N + 1, 2, -1.0);
    auto rec = [&](auto &&f, ll i, ll j) -> double {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        if (i == N) {
            return 0;
        }
        if (j == 1) {
            // ペナ中
            double res1 = f(f, i + 1, 0);
            return memo[i][j] = res1;
        } else {
            ll cnt = A[i] * t / 100;
            ll rest = A[i] - cnt;
            // 金貨を入れる
            double res1 = f(f, i + 1, 0) + rest;
            // 金貨を入れない
            double res2 = (f(f, i + 1, 1) + rest) * p / 100.0 + (f(f, i + 1, 0) + A[i]) * (100 - p) / 100.0;
            return memo[i][j] = max(res1, res2);
        }
    };
    double ans = rec(rec, 0, 0);
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
