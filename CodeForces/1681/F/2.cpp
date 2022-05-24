/*
参考：https://twitter.com/KaikeyPro/status/1528778831158743040
・木グラフ、主客転倒、オフラインダイコネ
・最近仕入れたやつが早速使えるとのことで、やってみた。
　問題見てもぱっと活用方法が浮かばず、かいけーさんのツイートから解法を理解。
　こういう使い方ができるんだねー。
・まず、全パスでの通り数が求めたい答えだけど、パスを1つずつ見るのは無理なので、
　各辺に注目して「その辺を使えるようなパス」の通り数を全ての辺で求める。いつもの主客転倒。
・この見方で行くと、ある色cについて考える時、色cの辺を全て取り除いたグラフで見れば、
　ある辺eの両端点それぞれの連結成分の要素数が、他の色cの辺を跨がずにその辺まで到達できるので、
　これを掛け合わせると、求めたかった辺eを使えるようなパスの通り数になる。
・オフラインダイコネは、(多分)クエリ*セグ木のlogと頂点数*UFのlogでlog2つ乗るのでまあ重い。
　今回は制約が50万(クエリは実質200万相当)と大きいのもあって、ACだけど4秒ちょい。(制約6秒)
　セグ木のパート非再帰にしたりしたらちょっと速くなるかな？(やりたくはない)
・ちょっと高速化。次のクエリまでの辺の追加削除は同時刻にまとめていいことが分かった。
　これでクエリ数が半分まで減らせた。AC3.45秒。
・NyaanさんのHashMapを導入。めちゃ速くなった。AC2.20秒。
　log2つ乗ってるのはrunの部分だからあんま変わらないと思ったのに全然違った。
　やっぱmapのlogは重いんだな…。
・Nyaanさんのを参考にセグ木パートの非再帰化もやった。AC2.03秒。
　50万のグラフで2秒ちょいなら十分他のグラフ問でも通用しそうでいい感じ。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<vector<pii>> adj(N);
    OfflineDynamicConnectivity odc(N, N*2+1);
    ll t = 0;
    rep(i, N-1) {
        ll u, v, x;
        cin >> u >> v >> x;
        u--; v--; x--;
        adj[x].eb(u, v);
        odc.insert(t, u, v);
    }
    t++;

    vector<int> ttoc(N*2+1, -1);
    rep(c, N) {
        for (auto [u, v] : adj[c]) {
            odc.erase(t, u, v);
        }
        t++;
        ttoc[t++] = c;
        for (auto [u, v] : adj[c]) {
            odc.insert(t, u, v);
        }
    }

    ll ans = 0;
    odc.run([&](int t) {
        if (ttoc[t] != -1) {
            int c = ttoc[t];
            for (auto [u, v] : adj[c]) {
                ans += (ll)odc.uf.size(u) * odc.uf.size(v);
            }
        }
    });
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
