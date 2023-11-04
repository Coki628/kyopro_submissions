/*
・自力AC！
・主客転倒、HLD、辺属性
・数え上げ定番テクだけども、区間に含まれる頂点ではなくて、
　ある頂点が使われる区間の数を数え上げるようにする。
　すると頂点0からのパス上にある辺番号の最大最小が分かればよくなって、
　左端が最小以下、右端が最大以上になるように(l,r)を選ぶ数え上げになる。
・公式解説見た。最大最小を取りに行くパート、
　HLDやっぱ要らなくて普通にDFSとかBFSでDPみたいに求まるね…。
　根から決めていく木DPみたいなやつ。たまに出るといつも忘れてる。。
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

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    vector<pii> edges;
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        edges.eb(u, v);
    }

    HeavyLightDecomposition hld(nodes);
    auto segmn = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    auto segmx = get_segment_tree(N, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(e, N - 1) {
        auto [u, v] = edges[e];
        if (hld.dep[u] < hld.dep[v]) {
            segmn.set(hld.in[v], e);
            segmx.set(hld.in[v], e);
        } else {
            segmn.set(hld.in[u], e);
            segmx.set(hld.in[u], e);
        }
    }
    segmn.build();
    segmx.build();

    ll ans = N * (N - 1) / 2;
    rep(u, 1, N) {
        ll l = hld.query(u, 0, INF, [&](ll a, ll b) { return segmn.query(a, b); }, [](ll a, ll b) { return min(a, b); }, true);
        ll r = hld.query(u, 0, -INF, [&](ll a, ll b) { return segmx.query(a, b); }, [](ll a, ll b) { return max(a, b); }, true);
        ll lcnt = l + 1;
        ll rcnt = N - r - 1;
        ans += lcnt * rcnt;
    }
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
