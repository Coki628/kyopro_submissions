/*
・きっちり自力AC。
・ソートしてゲームDP。でもこれもきっと簡単に解くやつあったんだよね？
　→あったよ。最大値だけ見れば良かったらしい…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll M;
    cin >> M;
    auto B = LIST(M);

    A.eb(0);
    B.eb(0);
    N++; M++;
    sort(ALL(A));
    sort(ALL(B));
    auto memo = list3d(N, M, 2, -1);
    auto rec = [&](auto&& f, ll n, ll m, ll turn) -> ll {
        if (memo[n][m][turn] != -1) {
            return memo[n][m][turn];
        }
        ll res = 1;
        if (turn == 0) {
            rep(i, n+1, N) {
                if (A[i] > B[m]) {
                    res &= f(f, i, m, 1-turn);
                }
            }
        } else {
            rep(i, m+1, M) {
                if (B[i] > A[n]) {
                    res &= f(f, n, i, 1-turn);
                }
            }
        }
        res = 1 - res;
        memo[n][m][turn] = res;
        return res;
    };

    ll ans1 = rec(rec, 0, 0, 0);
    if (ans1 == 1) {
        print("Alice");
    } else {
        print("Bob");
    }
    ll ans2 = rec(rec, 0, 0, 1);
    if (ans2 == 0) {
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
