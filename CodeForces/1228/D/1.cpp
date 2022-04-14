/*
・dojo set_e_6_2
・なんとか自力AC！
・二部グラフ応用
・なんか、完全三部グラフ？みたいな色分けができるかって話。
　とりあえずそれっぽく塗って出来上がった分け方に、
　必要条件ぽいものをいくつか並べてNGチェックしたら通った…。
・塗り分けの時は「直前の頂点に向かう辺があるような頂点なら進む」
　って感じで行けるだけ行って1,2,3,1,2,3って塗る。
　これで作った塗り分けに、
　・全部の頂点塗れたか
　・各頂点で、必要な(他グループへの)辺が全てあるか
　・各頂点で、不要な(自グループへの)辺が1つもないか
　の3点を確認して、全部OKならOKとした。
　必要条件は並べたけど、十分である確証はないので祈るように提出…なんとかAC。
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
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<set<ll>> nodes(N);
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].insert(v);
        nodes[v].insert(u);
        uf.merge(u, v);
    }

    if (uf.size() > 1) {
        print(-1);
        return;
    }

    vector<ll> C(N, -1);
    auto dfs = [&](auto&& f, ll u, ll prv, ll c) -> void {
        if (C[u] >= 0) {
            return;
        }
        C[u] = c;
        for (auto v : nodes[u]) {
            if (v != prv and nodes[v].count(prv)) {
                f(f, v, u, (c+1)%3);
            }
        }
    };
    vector<ll> visited(N);
    ll i = *nodes[0].begin();
    dfs(dfs, i, 0, 1);

    if (count(ALL(C), -1)) {
        print(-1);
        return;
    }

    vector<ll> need(3);
    rep(i, 3) {
        need[i] = N - count(ALL(C), i);
    }
    rep(u, N) {
        if (nodes[u].size() != need[C[u]]) {
            print(-1);
            return;
        }
        for (auto v : nodes[u]) {
            if (C[u] == C[v]) {
                print(-1);
                return;
            }
        }
    }
    rep(i, N) C[i]++;
    print(C);
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
