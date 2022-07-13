/*
参考：https://twitter.com/YFuka86/status/1546177034246041600
　　　https://smijake3.hatenablog.com/entry/2019/09/15/200200
・ライブラリ整備：Auxiliary Tree
・Yutaさんのツイートから、新しいデータ構造を履修。
　頂点数を減らした圧縮グラフみたいのを構築するというもの。
　そのグラフは指定した頂点集合と、それらのLCAのみで構成される。
　今回のようにクエリ単位で使う頂点が限られている時に、それらの頂点だけに注目してグラフを走査できる。
　今回は次数3以上の頂点がないかチェックするだけだけど、この圧縮したグラフで木DPとかもできる。
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

#include "graph/AuxiliaryTree.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    AuxiliaryTree aux(nodes);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll m;
        cin >> m;
        auto A = LIST<int>(m);
        rep(i, m) A[i]--;
        
        auto nodes2 = aux.build(A);
        bool ok = true;
        for (auto& [u, li] : nodes2) {
            if (li.size() > 2) {
                ok = false;
                break;
            }
        }
        if (ok) YES();
        else NO();
    }
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
