/*
・きっちり自力AC！
・木DP
・部分木毎で集計したいので、葉から教科書通りの木DPをやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, 1, N) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i);
    }
    string S;
    cin >> S;

    vector<ll> C1(N), C2(N);
    ll ans = 0;
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        if (S[u] == 'W') {
            C1[u]++;
        } else {
            C2[u]++;
        }
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            C1[u] += C1[v];
            C2[u] += C2[v];
        }
        if (C1[u] == C2[u]) {
            ans++;
        }
    };
    dfs(dfs, 0, -1);
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
