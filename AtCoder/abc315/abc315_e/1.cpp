/*
・きっちり自力AC！
・DFS。これは秒殺。
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
    rep(i, N) {
        ll sz;
        cin >> sz;
        rep(j, sz) {
            ll p;
            cin >> p;
            p--;
            nodes[i].eb(p);
        }
    }

    vector<ll> visited(N, 0);
    vector<ll> ans;
    auto dfs = [&](auto &&f, ll u) {
        if (visited[u] != 0) {
            return;
        }
        visited[u] = 1;
        for (auto v : nodes[u]) {
            f(f, v);
        }
        ans.eb(u);
    };
    dfs(dfs, 0);
    ans++;
    ans.pop_back();
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
