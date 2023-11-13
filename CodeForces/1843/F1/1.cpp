/*
参考：https://hotman78.hatenablog.com/entry/2020/06/17/102519
・終了後自力AC！間に合わず。。
・HLD、セグ木、最大部分配列問題
・HLD*セグ木に乗せようとせっせとコードを書くも、なんかうまく合わない。
　そこで、今回始めて乗せる「連続部分列の総和の最大値」が
　普通にセグ木に乗るのものなのか不安になってくる。有名そうなテーマなのでググる。
　するとhotmanさんの記事が出てきた。乗せられるようだが、やり方は違った。
　思ってたより複雑で、左端・右端から連続する情報とか持たないといけないやつだった。
　そんなこんなでモノイド作ってる間くらいで時間切れ。
　これは間に合わせたかったなー。
・この後F2も同じコードですぐ通ると思ったら、想定外の事態になる。
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
auto f = [](Node a, Node b) {
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
        seg.update(hld.in[u], {C[u], C[u], C[u], C[u], C[u], C[u], C[u]});
    }

    for (auto [op, u, v, k] : qs) {
        if (op == '?') {
            auto res = hld.query(u, v, T, [&](ll a, ll b) { return seg.query(a, b); }, [](Node a, Node b) { return f(a, b); });
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
