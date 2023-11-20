/*
参考：https://codeforces.com/contest/1899/submission/233146815
・別解。くでさんなど、これやった人も結構多かったぽい。
・順列、HLD*WM、部分木クエリ、range_freq
・HLDの軸と順列の軸で2次元平面に情報をプロットすると、
　長方形領域の点の存在判定に帰着できるので、これはWMのrange_freqで出来る。
　なおこちらの方法の場合は、順列側も区間としたいので、
　頂点の位置を変えておく必要がある。
　でもさ、Moだって区間作ってるのは同じな訳だし、
　なんでMoだと元の順列のままでうまくいって、
　こっちのWM解はrev作らないとダメなのかは、いまいち釈然としてない。
・よく見て番号の対応をMoの時と同じにしたら、ちゃんと通った。
　まあでもこっちだとHLDと順列Pで2重変換みたいになってゴチャるから、
　分かりやすさのために、順列の逆にする方で変換する方がいいのかな。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
#include "datastructure/WaveletMatrix.hpp"

void solve() {
    int N, Q;
    cin >> N >> Q;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<int> P(N);
    cin >> P;
    P--;

    vector<int> rev(N);
    rep(i, N) {
        rev[P[i]] = i;
    }
    HeavyLightDecomposition hld(nodes);
    WaveletMatrix<int> wm(N);
    rep(u, N) {
        wm.set(hld[P[u]], u);
        // これでもOK
        // wm.set(hld[u], rev[u]);
    }
    wm.build();
    rep(i, Q) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, x--;
        ll res = wm.range_freq(hld.in[x], hld.out[x], l, r);
        if (res > 0) {
            YES();
        } else {
            NO();
        }
    }
    print();
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
