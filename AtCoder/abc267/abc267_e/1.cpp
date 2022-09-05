/*
・これはTLE。set重い…。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    vvi nodes(N);
    vector<ll> cost(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        cost[u] += A[v];
        cost[v] += A[u];
    }
    
    set<pll> se;
    rep(i, N) {
        se.insert({cost[i], i});
    }
    ll mx = max(cost);
    ll res = bisearch_min(-1, mx, [&](ll x) {
        auto curse = se;
        auto curcost = cost;
        vector<bool> removed(N);
        rep(_, N) {
            auto itr = curse.upper_bound({x, mx});
            // もう取れない
            if (itr == curse.begin()) {
                return false;
            }
            itr--;
            auto [__, u] = *itr;
            curse.erase(itr);
            removed[u] = true;
            for (auto v : nodes[u]) {
                if (removed[v]) continue;
                curse.erase({curcost[v], v});
                curcost[v] -= A[u];
                curse.insert({curcost[v], v});
            }
        }
        return true;
    });
    print(res);
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
