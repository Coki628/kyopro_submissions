/*
・dojo set_d_3_7
・なんとか自力AC！
・実験エスパー
・小さいケースで実験すると、構築できる種類はそう多くなさそう。
　なんとなく0から作るより完全グラフから引く方針のが楽そう。
　となって、(0,5),(1,4),(2,3)みたいに対角線ぽい位置から1個ずつ引いてくと合いそうで、
　(u,N-u)と(u,N-u-1)の2パターンのどちらかでいけそうなので、それでやってみると通った。
・解説によると、補グラフを意識すれば分かりやすいっぽい。
　確かに今回完全グラフから間引こうと思ったのも、その間引く辺は補グラフみたいなもんだね。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

pair<bool, ll> check(int N, const vector<pll> &edges) {
    vvi nodes(N);
    UnionFind uf(N);
    for (auto [u, v] : edges) {
        nodes[u].eb(v);
        nodes[v].eb(u);
        uf.merge(u, v);
    }
    set<ll> se;
    rep(u, N) {
        ll cnt = 0;
        for (auto v : nodes[u]) {
            cnt += v+1;
        }
        se.insert(cnt);
    }
    return {se.size() == 1 and uf.size() == 1, *se.begin()};
}

void solve() {
    ll N;
    cin >> N;

    vector<pll> edges;
    rep(i, N) {
        rep(j, i+1, N) {
            edges.eb(i, j);
        }
    }
    // ll M = edges.size();
    // rep(bit, 1LL<<M) {
    //     vector<pll> cur;
    //     rep(i, M) {
    //         if (bit>>i & 1) {
    //             cur.eb(edges[i]);
    //         }
    //     }
    //     auto [ok, cnt] = check(N, cur);
    //     if (ok) {
    //         debug(cnt);
    //         debug(cur.size());
    //         print(cur);
    //     }
    // }
    rep(i, 2) {
        auto cur = edges;
        rep(u, N) {
            ll v = N-u-1-i;
            if (u >= v) break;
            cur.erase(find(ALL(cur), mkp(u, v)));
        }
        auto [ok, _] = check(N, cur);
        if (ok) {
            print(cur.size());
            for (auto[u, v] : cur) {
                print(mkp(u+1, v+1));
            }
            return;
        }
    }
    assert(0);
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
