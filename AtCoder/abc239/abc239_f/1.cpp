/*
・自力AC！やったね。
・この問題、本番中は確かほとんど見てなかったんだよな。Gのフローに賭けたんだ。(通せなかったけど)
・木グラフ、構築、UF、マージテク
・構築でうわぁってなるけど、確実なことを順々に積み上げていく。
　まず必要な辺の合計数sum(D)が木のサイズと合ってなければ即NG。これは即弾く。
　次に実際に既にある辺については張ってみて、Dからも数を引く。
　この時連結成分もUFで管理しておく。最終的に森を連結させていって1つの木にしたいけど、
　途中で連結成分同士をマージする時、必要な辺がDに残っているかは連結成分毎にまとめて考えればいいし、
　(同じ連結成分内からであれば、どの頂点を使っても同じことだし、
　逆に同じ連結成分から辺を張ったりしたら閉路になって即NGなので)
　変な閉路とかできたりしないかもチェックできるので、UFが色々と都合がいい。
　この時使える頂点の多重集合を、連結成分毎に持っておく。
　この状態で頂点を使える回数を優先度にしてPQ(両側使いたかったからsetにしたけど)に詰める。
　なるべく大きい所と小さい所でマージするようにしたけど、
　これは大きい2つでもよかったらしい。
　マージの際は使える頂点集合もマージするけど、きっちりマージテクする。
・細部が整えきれてなくて何回かWA叩いたけど、assertで原因に当たりをつけたりして、
　最終的にしっかり修正して自力で通せたのでいい感じ。
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

#include "mystl/my_set.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto D = LIST(N);
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges.eb(u, v);
    }

    if (sum(D) != (N-1)*2) {
        print(-1);
        return;
    }
    UnionFind uf(N);
    for (auto [u, v] : edges) {
        uf.merge(u, v);
        D[u]--;
        D[v]--;
    }
    vvi adj(N);
    rep(i, N) {
        if (not uf.is_tree(i) or D[i] < 0) {
            print(-1);
            return;
        }
        rep(_, D[i]) {
            adj[uf.find(i)].eb(i);
        }
    }

    my_set<pii> se;
    for (auto r : uf.get_roots()) {
        se.emplace(adj[r].size(), r);
    }
    vector<pll> ans;
    while (se.size() > 1) {
        auto [_, ra] = se.pop_front();
        auto [__, rb] = se.pop_back();
        if (adj[ra].empty()) {
            print(-1);
            return;
        }
        ll u = adj[ra].back(); adj[ra].pop_back();
        ll v = adj[rb].back(); adj[rb].pop_back();
        ans.eb(u+1, v+1);
        ll r = uf.merge(u, v);
        D[u]--; D[v]--;
        if (r == ra) {
            swap(adj[ra], adj[rb]);
            for (auto w : adj[rb]) {
                adj[ra].eb(w);
            }
        } else {
            for (auto w : adj[ra]) {
                adj[rb].eb(w);
            }
        }
        se.emplace(adj[r].size(), r);
    }
    rep(i, N) {
        assert(uf.is_tree(i));
        assert(D[i] == 0);
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
