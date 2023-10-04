/*
・ゲーム、Grundy数
・Grundy数のメモ化再帰、久々に書いたけどちゃんとソラで書けて良かった。
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
    ll N, x, y;
    cin >> N >> x >> y;
    vector<ll> A(N);
    cin >> A;

    ll M = 100000;
    vector<ll> memo(M + 1, -1LL);
    auto rec = [&](auto &&f, ll i) -> ll {
        if (i == 0) {
            return 0;
        }
        if (memo[i] != -1) {
            return memo[i];
        }
        set<ll> se;
        if (i - x >= 0) {
            se.insert(f(f, i - x));
        }
        if (i - y >= 0) {
            se.insert(f(f, i - y));
        }
        ll g = 0;
        while (se.count(g)) {
            g++;
        }
        return memo[i] = g;
    };
    
    ll res = 0;
    rep(i, N) {
        res ^= rec(rec, A[i]);
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
