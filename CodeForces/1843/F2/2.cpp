/*
参考：https://ei1333.github.io/library/test/verify/aoj-2450.test.cpp
・自力ならず。
・HLD、セグ木、最大部分配列問題、マージ方向のあるHLD*セグ木
・さて、モノイド作ってセグ木に乗せるところまではF1で書いたのでその続き。
　通らない原因は乗せてるモノイドがマージ方向関係あるやつだったからなんだけど、
　このタイプのやつ久しくやってなかったし、経験も浅くて大変だった。
　library checkerにあるやつ(librarychecker_vertex_set_path_composite)
　みたいに関数とセグ木2つ作って、上りと下りで分けてやるやつも
　試してみたんだけど、なんかそれだとうまくいかなかった。
　結局、うしさんがHLDをverifyしてる中に同じような左右端を持ったやつがあったので、
　それと同じやり方にしたら通った。今まで使ったことなかった、
　最後のマージをやる関数Sみたいのを使う。
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
auto f = [](const Node &a, const Node &b) {
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
    auto seg = get_segment_tree(N, f, T);
    rep(u, N) {
        seg.set(hld.in[u], {C[u], C[u], C[u], C[u], C[u], C[u], C[u]});
    }
    seg.build();

    for (auto [op, u, v, k] : qs) {
        if (op == '?') {
            auto res = hld.query(u, v, T,
                [&](ll a, ll b) { return seg.query(a, b); },
                [](const Node &a, const Node &b) { return f(a, b); },
                [](Node a, const Node &b) {
                    // ここで列をreverseさせる
                    swap(a.lmn, a.rmn);
                    swap(a.lmx, a.rmx);
                    return f(a, b);
                }
            );
            if (res.mn <= k and k <= res.mx) {
                YES();
            } else {
                NO();
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
