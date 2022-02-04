/*
・ほぼ自力AC！？まあ時間かかったし、コーナー見つけられなかったんだけど、方針はほぼ自力。
・HLD、Sparse Table、最大値の最小化、二分探索、工夫してDFS
・内容盛りだくさんのグラフ問題で楽しかった。
・兎にも角にも最大値の所が小さくならないと最小化できないので、そこを起点に考える。
　すると、最大値の辺は1本絶対使うとして、そこから両側に伸ばしてうまくいくかを判定したくなる。
　最大値を決め打つと、全ての場所についてその値以下にするにはどうするかが形になってくる。
・先程の起点を根としたDFSで考える。すると、部分木に決め打った値より大きい値が存在する限り、
　潜らないといけないし、逆にそこの部分木にそういう値がなければ潜らなくていい。
　この判定でDFSを進めて、2つ以上の部分木に進んでしまった頂点があったら、
　それは1本のパスにできなくなるのでNG。また、このパスで減らせる値はパスに含まれる最小値なので、
　起点してある最大値から辺のコストを引いた時に、決め打った最大値を下回らなくなったらこれもNG。
・この方針で起点から両側にDFSを走らせて両方OKならOK。で判定して二分探索を進める。
・使う道具としては、部分木の辺から最大値を取りたいので、HLDと区間最大値取得を用意する。
・結局、にぶたんの最小値を0じゃなくて1にしていたのがコーナーに引っかかってたので、
　多分時間かけてもそれ以上自力では解けなかったんだけど、そこ以外は自力でやった。
・最初雑に作ったらTLEで、コスト取得のmapをやめて隣接リストのvectorに含めて、
　セグ木のlogも外すために最大値取得をSparse Tableにして、これで無事AC。1.43秒。(制約4秒)
・今回のこれのおかげで、HLDの根を0以外で初期化する機能の気運が高まったため、
　終了後色々整備して仕上げた。ちゃんと動いて良かった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/HeavyLightDecomposition.hpp"
#include "segment/SparseTable.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<tuple<ll, ll, ll>> edges;
    vvi nodes(N);
    vvpll nodes2(N);
    ll mxi = -1, mx = 0;
    rep(i, N-1) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        nodes2[u].eb(v, c);
        nodes2[v].eb(u, c);
        edges.pb({u, v, c});
        if (chmax(mx, c)) {
            mxi = i;
        }
    }

    // 最大の辺をつなぐ頂点を根にする
    ll root = get<0>(edges[mxi]);
    HeavyLightDecomposition hld(nodes, root);
    vector<ll> tmp(N);
    for (auto [u, v, c] : edges) {
        if (hld.dep[u] < hld.dep[v]) {
            tmp[hld.in[v]] = c;
        } else {
            tmp[hld.in[u]] = c;
        }
    }
    auto st = get_sparse_table(tmp, [](ll a, ll b) -> ll { return max(a, b); }, -INF);

    ll res = bisearch_min(-1, mx, [&](ll d) {
        auto [v1, v2, _] = edges[mxi];
        auto dfs = [&](auto&& f, ll u, ll prv) -> bool {
            ll subcnt = 0;
            for (auto [v, c] : nodes2[u]) {
                if (v == prv) continue;
                // 部分木のmaxがd以下ならこの先は取り込む必要なし
                if (hld.dep[u] < hld.dep[v]) {
                    if (max(st.query(hld.in[v]+1, hld.out[v]), c) <= d) continue;
                } else {
                    assert(0);
                }
                // 含む辺のminが小さくてmxを減らし切れない
                if (mx-c > d) {
                    return false;
                }
                subcnt++;
                if (!f(f, v, u)) {
                    return false;
                }
            }
            // 取り込んだ部分木が2つ以上に枝分かれしていたら無理
            return subcnt < 2;
        };
        // 両側とも正しく伸ばせたらOK
        return dfs(dfs, v1, v2) and dfs(dfs, v2, v1);
    });
    print(res);
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
