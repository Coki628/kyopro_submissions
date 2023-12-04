/*
・これはまだTLE。
・頂点被覆、2-SATの勉強のためにまずは愚直に。
　これをベースに区間辺にしていく。
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

#include "acl/twosat.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        edges.eb(u, v);
    }

    ll res = bisearch_max(1, N + 1, [&](ll x) {
        atcoder::two_sat ts(N);
        // 頂点被覆を満たすための条件
        for (auto [u, v] : edges) {
            // A or B
            ts.add_clause(u, true, v, true);
        }
        // min(|Ai-Aj|)>=xを満たすための条件
        rep(u, N) {
            rep(v, u + 1, min(u + x, N)) {
                // not (A and B) 
                ts.add_clause(u, false, v, false);
            }
        }
        return ts.satisfiable();
    });
    print(res);
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
