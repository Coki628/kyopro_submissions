/*
参考：https://atcoder.jp/contests/yahoo-procon2018-final-open/submissions/3144817
ライブラリ整備：重心分解
・CFで久しぶりにやった(cf1790F)ので、もう1問くらい使ってみる。
　基本的には重心分解の木で親が分かれば、祖先側に情報集めるでいいんだけど、
　今回は数え上げなので、取得で祖先の情報を取り込む時に、
　自身を含んだ部分木の寄与を取り除く必要がある。
　(前のは最適化だったから気にしなくてよかったんだね。)
　で、これがまあ結構面倒で、自分の一段下からいくつ来てるかを、
　子頂点の数だけ持っておく必要があった。重そうだけど2重mapでやった。
・計算量は木の深さlogに、mapのlog、最短距離取得のlogと色々乗っているが、
　なんとかAC1.53秒(制約4秒)。
・最短距離取得に線形LCA作ってみたら、なんかめちゃ遅くなって3.58秒。
　さすがにおかしいだろってもう1回投げたら2.66秒。ブレすぎ。。
　別の問題で試しても遅くなることはなかったので、これは本当によく分からん…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/LowestCommonAncestor.hpp"
#include "graph/centroid_decomposition.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    LowestCommonAncestor lca(nodes);
    auto par = centroid_decomposition(nodes);

    // C[u][d] := 頂点uの部分木でuへの距離がdの頂点数
    vector<map<int, int>> C(N);
    // C2[u][v][d] := 頂点uの子vの部分木でuへの距離がdの頂点数
    vector<map<int, map<int, int>>> C2(N);
    rep(u, N) {
        ll v = u;
        while (v != -1) {
            C[v][lca.dist(u, v)]++;
            if (par[v] != -1) {
                C2[par[v]][v][lca.dist(u, par[v])]++;
            }
            v = par[v];
        }
    }

    rep(_, Q) {
        ll u, k;
        cin >> u >> k;
        u--;
        ll cnt = 0;
        if (C[u].count(k)) {
            cnt += C[u][k];
        }
        ll prvv = u, v = par[u];
        while (v != -1) {
            ll d1 = lca.dist(u, v);
            ll d2 = k - d1;
            if (d2 >= 0 and C[v].count(d2)) {
                cnt += C[v][d2];
                // 自身が通った部分木からの寄与を引く
                if (C2[v][prvv].count(d2)) {
                    cnt -= C2[v][prvv][d2];
                }
            }
            prvv = v;
            v = par[v];
        }
        print(cnt);
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
