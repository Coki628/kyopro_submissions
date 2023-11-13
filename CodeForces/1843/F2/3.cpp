/*
・結局通せなかった、関数2つ作る方。こっちのが汎用性ありそうだし、
　使えるようにしたいんだけど、なんかうまくいかない…。
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

#include "graph/HeavyLightDecomposition.hpp"

struct Node {
    ll lmx, rmx, mx, lmn, rmn, mn, sm;
};
const Node T = Node({0, 0, 0, 0, 0, 0, 0});
auto f1 = [](Node a, Node b) {
    Node res = T;
    res.lmx = max(a.lmx, a.sm + b.lmx);
    res.rmx = max(b.rmx, b.sm + a.rmx);
    res.mx = max({a.mx, b.mx, a.rmx + b.lmx});
    res.lmn = min(a.lmn, a.sm + b.lmn);
    res.rmn = min(b.rmn, b.sm + a.rmn);
    res.mn = min({a.mn, b.mn, a.rmn + b.lmn});
    res.sm = a.sm + b.sm;
    return res;
};
auto f2 = [](Node b, Node a) {
    Node res = T;
    res.lmx = max(a.lmx, a.sm + b.lmx);
    res.rmx = max(b.rmx, b.sm + a.rmx);
    res.mx = max({a.mx, b.mx, a.rmx + b.lmx});
    res.lmn = min(a.lmn, a.sm + b.lmn);
    res.rmn = min(b.rmn, b.sm + a.rmn);
    res.mn = min({a.mn, b.mn, a.rmn + b.lmn});
    res.sm = a.sm + b.sm;
    return res;
};
 
void solve() {
    ll Q;
    cin >> Q;
 
    ll n = 1;
    vector<ll> C = {1};
    vector<tuple<char, ll, ll, ll>> qs;
    rep(i, Q) {
        char op;
        cin >> op;
        if (op == '+') {
            ll u, x;
            cin >> u >> x;
            u--;
            C.eb(x);
            qs.eb(op, u, n, x);
            n++;
        } else {
            ll u, v, k;
            cin >> u >> v >> k;
            u--, v--;
            qs.eb(op, u, v, k);
        }
    }
 
    ll N = n;
    assert(C.size() == N);
    vvi nodes(N);
    for (auto [op, a, b, c] : qs) {
        if (op == '+') {
            nodes[a].eb(b);
            nodes[b].eb(a);
        }
    }
    HeavyLightDecomposition hld(nodes);
    auto seg1 = get_segment_tree(N, f1, T);
    auto seg2 = get_segment_tree(N, f2, T);
    rep(u, N) {
        seg1.update(hld.in[u], {C[u], C[u], C[u], C[u], C[u], C[u], C[u]});
        seg2.update(hld.in[u], {C[u], C[u], C[u], C[u], C[u], C[u], C[u]});
    }
 
    for (auto [op, u, v, k] : qs) {
        if (op == '?') {
            ll lca = hld.lca(u, v);
            if (lca == u) {
                auto res = hld.query(u, v, T, [&](ll a, ll b) { return seg1.query(a, b); }, [](Node a, Node b) { return f1(a, b); });
                if (res.mn <= k and k <= res.mx) {
                    YES();
                } else {
                    NO();
                }
            } else {
                ll d = hld.dist(v, lca);
                ll w = hld.la(v, d - 1);
                auto res2 = hld.query(
                    u, lca, T,
                    [&](ll a, ll b) { return seg2.query(a, b); },
                    [](Node a, Node b) { return f2(a, b); }
                );
                swap(res2.lmn, res2.rmn);
                swap(res2.lmx, res2.rmx);
                auto res1 = hld.query(
                    w, v, T,
                    [&](ll a, ll b) { return seg1.query(a, b); },
                    [](Node a, Node b) { return f1(a, b); }
                );
                auto res = f1(res2, res1);
                if (res.mn <= k and k <= res.mx) {
                    YES();
                } else {
                    NO();
                }
            }
        }
    }
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
