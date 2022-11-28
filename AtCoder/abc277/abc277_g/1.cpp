/*
・自力ならず。
・期待値DP
・3乗から落とせず。ワンチャン状態数が～、って一応書いたけど。これはTLE。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<ll> C(N);
    cin >> C;

    vector<mint> inv(N);
    rep(i, N) {
        inv[i] = (mint)1 / nodes[i].size();
    }
    auto memo = listnd(K, HashMap<pii, mint>());
    auto rec = [&](auto&& f, ll k, ll u, ll x) -> mint {
        if (k == K) return 0;
        if (memo[k].count({u, x})) {
            return memo[k][{u, x}];
        }
        mint res = 0;
        for (auto v : nodes[u]) {
            if (C[v] == 0) {
                res += f(f, k+1, v, x+1) * inv[u];
            } elif (C[v] == 1) {
                res += (f(f, k+1, v, x)+x*x) * inv[u];
            }
        }
        memo[k][{u, x}] = res;
        return res;
    };
    mint ans = rec(rec, 0, 0, 0);
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
