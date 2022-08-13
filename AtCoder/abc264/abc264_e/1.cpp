/*
・きっちり自力AC！
・クエリ先読み、後ろからUF
・何度も見てきた後ろからUF。発電所は先に全部繋いどくと楽。
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
    ll N, M, E;
    cin >> N >> M >> E;
    vector<pii> edges;
    rep(i, E) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges.eb(u, v);
    }
    ll Q;
    cin >> Q;
    vector<ll> qs;
    vector<bool> removed(E);
    rep(i, Q) {
        ll x;
        cin >> x;
        x--;
        qs.eb(x);
        removed[x] = true;
    }

    UnionFind uf(N+M);
    rep(i, E) {
        if (removed[i]) continue;
        auto [u, v] = edges[i];
        uf.merge(u, v);
    }
    rep(i, N, N+M-1) {
        uf.merge(i, i+1);
    }
    vector<ll> ans(Q);
    rep(i, Q-1, -1, -1) {
        ans[i] = uf.size(N) - M;
        auto [u, v] = edges[qs[i]];
        uf.merge(u, v);
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
