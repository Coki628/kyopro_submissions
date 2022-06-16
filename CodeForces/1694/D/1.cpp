/*
・なんとか自力AC！
・木DP
・右端めいっぱいまで使ったとしてsumを集めてくる感じ。
　左端に足りなかったら操作回数++する。
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
    vvi nodes(N);
    rep(i, 1, N) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i);
    }
    vector<ll> L(N), R(N);
    rep(i, N) {
        cin >> L[i] >> R[i];
    }

    vector<ll> sm(N);
    auto dfs = [&](auto&& f, ll u) -> ll {
        ll res = 0;
        for (auto v : nodes[u]) {
            res += f(f, v);
            sm[u] += sm[v];
        }
        if (sm[u] < L[u]) {
            res++;
            sm[u] = R[u];
        } else {
            chmin(sm[u], R[u]);
        }
        return res;
    };
    ll ans = dfs(dfs, 0);
    print(ans);
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
