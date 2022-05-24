/*
参考：https://ei1333.hateblo.jp/entry/2017/12/14/000000
　　　https://ei1333.github.io/luzhiled/snippets/other/offline-dynamic-connectivity.html
・オフラインダイコネ
・これも有名データ構造だけど使ったことなかったのでこの機会にやってみた。
・使い方はUFundoとか永続UFよりはちょい複雑め。
　色々ソース内コメントに書いておいた。特に経過時間の進め方として、
　辺追加・削除・回答クエリそれぞれで1ずつ進めると良さそう。
　回答クエリで状態変わらないからって時間そのままにしたらWAになった。
・この問題についてはさすがに冗長なことしてるのでちょい遅くて、AC2.13秒。
　でも40万クエリでこのくらいなら、十分使える可能性はある。
・ライブラリ整備で仕上げてきた。これでやってみると、AC1.35秒。
　内部的にUFundo使ってるのにUFundo単体より速くなっててうける。
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

    ll Q;
    cin >> Q;
    OfflineDynamicConnectivity dc(N, Q*2+1);
    map<pii, vector<pii>> adj;
    int t = 0;
    for (auto [u, v] : edges) {
        if (S[u] == S[v]) {
            dc.insert(t, u, v);
        } else {
            if (S[u] > S[v]) swap(u, v);
            adj[{S[u], S[v]}].eb(u, v);
        }
    }

    map<pii, vector<tuple<int, int, int>>> qs;
    vector<vector<tuple<int, int, int>>> qs2(Q*2+1);
    vector<ll> ans(Q);
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (S[a] == S[b]) {
            qs2[t].eb(a, b, i);
        } else {
            if (S[a] > S[b]) swap(a, b);
            qs[{S[a], S[b]}].eb(a, b, i);
        }
    }
    t++;

    for (auto& [k, li] : qs) {
        auto [sa, sb] = k;
        auto tmp = adj[{sa, sb}];
        for (auto [u, v] : tmp) {
            dc.insert(t, u, v);
        }
        t++;
        qs2[t++] = li;
        for (auto [u, v] : tmp) {
            dc.erase(t, u, v);
        }
    }
    dc.run([&](int t) -> void {
        for (auto [a, b, i] : qs2[t]) {
            ans[i] = dc.uf.same(a, b);
        }
    });
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
