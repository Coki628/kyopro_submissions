/*
・ライブラリ整備：永続UF
・永続セグ木の方を触った後、実体をコピーするよりノードのポインタで持っておいた方が、
　永続UFの方にしてもいいんじゃないか、と思ってやってみた。
　速度はほぼ変わらなかったけど、メモリが改善して796MBくらいだったのが568MBに。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/PersistentUnionFind.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges.eb(u, v);
    }
    auto S = LIST(N);
    rep(i, N) S[i]--;

    PersistentUnionFind uf(N);
    map<pii, vector<pii>> adj;
    for (auto [u, v] : edges) {
        if (S[u] == S[v]) {
            uf.merge(u, v);
        } else {
            if (S[u] > S[v]) swap(u, v);
            adj[{S[u], S[v]}].eb(u, v);
        }
    }

    ll Q;
    cin >> Q;
    map<pii, vector<tuple<int, int, int>>> qs;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        if (S[a] == S[b]) {
            ans[i] = uf.same(a, b);
        } else {
            if (S[a] > S[b]) swap(a, b);
            qs[{S[a], S[b]}].eb(a, b, i);
        }
    }

    for (auto& [k, li] : qs) {
        auto [sa, sb] = k;
        auto tmp = uf.get_root_node();
        for (auto [u, v] : adj[{sa, sb}]) {
            uf.merge(u, v);
        }
        for (auto [a, b, i] : li) {
            ans[i] = uf.same(a, b);
        }
        uf.set_root_node(tmp);
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
