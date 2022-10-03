/*
・なんとか自力AC！
・ゲームDP、メモ化再帰、後退解析
・dp[i][j][k] := j番目までやって、残りの奇数がk個、アリスの偶奇i=0/1
　って状態持った。ミニマックス法じゃなくて、戻り値で勝敗の逆側返すやつでやった。
　mod 2が負数もあるのに普通のやつでやっててWA。気付けてよかったけど。
・念のためcnt0が負数になる場合を考慮したけど、
　遷移時に場合分けであり得ない方に行かないようにしてるからか、
　コメントアウトしても普通に通った。
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    
    rep(i, N) {
        A[i] = modulo(A[i], 2LL);
    }
    ll K = count(ALL(A), 1);
    auto memo = listnd(2, N+1, K+1, -1);
    auto rec = [&](auto&& f, ll oe, ll i, ll cnt1) -> ll {
        int turn = i % 2;
        if (i == N) {
            if (turn == 0) {
                return oe == 1;
            } else {
                return oe == 0;
            }
        }
        if (memo[oe][i][cnt1] != -1) {
            return memo[oe][i][cnt1];
        }
        ll cnt0 = (N-i) - cnt1;
        // if (cnt0 < 0) {
        //     return 0;
        // }
        ll res = 0;
        if (turn == 0) {
            if (cnt0 > 0) {
                chmax(res, f(f, oe, i+1, cnt1));
            }
            if (cnt1 > 0) {
                chmax(res, f(f, 1-oe, i+1, cnt1-1));
            }
        } else {
            if (cnt0 > 0) {
                chmax(res, f(f, oe, i+1, cnt1));
            }
            if (cnt1 > 0) {
                chmax(res, f(f, oe, i+1, cnt1-1));
            }
        }
        memo[oe][i][cnt1] = !res;
        return !res;
    };
    ll ans = rec(rec, 0, 0, K);
    if (!ans) {
        print("Alice");
    } else {
        print("Bob");
    }
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
