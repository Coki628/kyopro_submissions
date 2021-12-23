/*
・自力AC。でも手こずりすぎ。。
・順列全探索
・順列全探索はすぐ分かるんだけど、中の判定がまあまあ面倒。
　最初、各頂点毎に生やす辺変えて一致判定してたら合わなくて、
　全部グラフ作り直してからのチェックにしても合わなくて、
　隣接リストから辺リストに持ち方変えたらやっと通った。。
・公式解説は隣接行列でやってた。確かにグラフサイズ小さいんだし、
　その方が安パイだったかも。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pll> edges1, edges2;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges1.eb(u, v);
        edges1.eb(v, u);
    }
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges2.eb(u, v);
        edges2.eb(v, u);
    }

    if (M == 0) {
        Yes();
        return;
    }

    sort(ALL(edges1));
    sort(ALL(edges2));
    vector<ll> V(N);
    iota(ALL(V), 0);
    for (auto& P : permutations(V)) {
        vector<pll> tmp;
        for (auto [u, v] : edges2) {
            tmp.eb(P[u], P[v]);
        }
        sort(ALL(tmp));
        if (tmp == edges1) {
            Yes();
            return;
        }
    }
    No();
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
