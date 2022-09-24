/*
・きっちり自力AC！
・ゲームDP
・今の個数は10000個で遷移するA[i]が100個だから間に合う。
　遷移先がなかった時はINFを0に直すみたいにした。
・後でTL見てて分かったけど、A1=1って制約があるのね。
　石残ってても、できる操作がなければ終了みたいなルールでやってた…。
　これなら別に遷移先がないって状況にはならないんだな。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(K);

    auto memo = listnd(2, N+1, -1);
    auto rec = [&](auto&& f, ll turn, ll i) -> ll {
        if (memo[turn][i] != -1) {
            return memo[turn][i];
        }
        ll res;
        if (turn == 0) {
            res = -INF;
            rep(j, K) {
                if (i+A[j] <= N) {
                    chmax(res, f(f, 1-turn, i+A[j])+A[j]);
                }
            }
        } else {
            res = INF;
            rep(j, K) {
                if (i+A[j] <= N) {
                    chmin(res, f(f, 1-turn, i+A[j]));
                }
            }
        }
        if (res == -INF or res == INF) {
            res = 0;
        }
        memo[turn][i] = res;
        return res;
    };
    ll ans = rec(rec, 0, 0);
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
