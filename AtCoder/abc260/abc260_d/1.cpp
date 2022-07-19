/*
・きっちり自力AC！
・BITにぶたんと隣接リストでシミュった。
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
    auto P = LIST(N);
    rep(i, N) P[i]--;

    BIT<ll> bit(N);
    vvl adj(N);
    vector<ll> ans(N, -1);
    rep(i, N) {
        ll x = P[i];
        ll j = bit.bisearch_fore(x, N-1, 1);
        if (j == -1) {
            bit.add(x, 1);
            adj[x].eb(x);
        } else {
            adj[j].eb(x);
            swap(adj[j], adj[x]);
            bit.add(j, -1);
            bit.add(x, 1);
        }
        if (adj[x].size() == K) {
            for (auto a : adj[x]) {
                ans[a] = i + 1;
            }
            adj[x].clear();
            bit.add(x, -1);
        }
    }
    print(ans, '\n');
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
