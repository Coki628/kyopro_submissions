/*
・きっちり自力AC！残り20分しかない中、なんとか通し切った。
・ゲームDP、メモ化再帰、bitDP
・終わってから落ち着いて見て気付いたけど、
　これn番目まで見ての添字要らないね…。(popcount(bit)で分かる)
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
    vector<string> S(N);
    cin >> S;

    auto memo = listnd(N, N+1, 1<<N, -1);
    auto rec = [&](auto&& f, ll n, ll prv, ll bit) -> ll {
        if (n == N) {
            return 0;
        }
        if (memo[n][prv][bit] != -1) {
            return memo[n][prv][bit];
        }
        ll res = 1;
        rep(i, N) {
            if (bit>>i & 1) continue;
            if (prv == N or S[prv].back() == S[i][0]) {
                res &= f(f, n+1, i, bit|(1<<i));
            }
        }
        memo[n][prv][bit] = 1 - res;
        return 1 - res;
    };
    ll res = rec(rec, 0, N, 0);
    if (res == 1) {
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
