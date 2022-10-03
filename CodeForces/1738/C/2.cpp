/*
・なんとか自力AC！
・ゲームDP、メモ化再帰、ミニマックス法
・ミニマックス法でもやってみた。ちゃんと通った。
　これだと戻り値返す時に状態ひっくり返すとかしなくていいし、
　手番によって多少でも行動に差異があるなら、やっぱこっちのが分かりやすいかな。
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
        if (i == N) {
            return oe == 0;
        }
        if (memo[oe][i][cnt1] != -1) {
            return memo[oe][i][cnt1];
        }
        int turn = i % 2;
        ll cnt0 = (N-i) - cnt1;
        if (turn == 0) {
            ll res = 0;
            if (cnt0 < 0) return res;
            if (cnt0 > 0) {
                chmax(res, f(f, oe, i+1, cnt1));
            }
            if (cnt1 > 0) {
                chmax(res, f(f, 1-oe, i+1, cnt1-1));
            }
            memo[oe][i][cnt1] = res;
            return res;
        } else {
            ll res = 1;
            if (cnt0 < 0) return res;
            if (cnt0 > 0) {
                chmin(res, f(f, oe, i+1, cnt1));
            }
            if (cnt1 > 0) {
                chmin(res, f(f, oe, i+1, cnt1-1));
            }
            memo[oe][i][cnt1] = res;
            return res;
        }
    };
    ll ans = rec(rec, 0, 0, K);
    if (ans) {
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
