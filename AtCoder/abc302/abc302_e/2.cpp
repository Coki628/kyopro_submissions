/*
・オフラインダイコネ
・本番中通らなかったダイコネ解。
　バグってた原因は隣接リストの逆辺削除してないからだった…。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<set<ll>> nodes(N);
    OfflineDynamicConnectivity odc(N, Q);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            nodes[u].insert(v);
            nodes[v].insert(u);
            odc.insert(i, u, v);
        } else {
            ll u;
            cin >> u;
            u--;
            for (auto v : nodes[u]) {
                nodes[v].erase(u);
                odc.erase(i, u, v);
            }
            nodes[u].clear();
        }
    }
    vector<ll> ans(Q);
    odc.run([&](ll i) { ans[i] = odc.single; });
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
