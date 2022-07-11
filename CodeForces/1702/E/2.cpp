/*
参考：みんなのツイート
・自力ならず…。
・二部グラフ判定
・そういう目で見て再度考察したら理解できた。
　番号が2個ずつあるのは前提として、うまく割り振れるかどうかは、
　ペアの番号iを頂点、同じ数字同士に辺を張ったグラフを構成して、
　これが二部グラフになるかどうかで判断できる。
　同じ側に来る番号があると、それは両側に分けることができないことになるのでNG、
　そういった箇所が1つもなければ分けられるのでOK。二部グラフ判定でチェックできる。
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

void solve() {
    ll N;
    cin >> N;
    vector<pll> AB;
    rep(i, N) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        AB.eb(a, b);
    }

    vector<ll> C(N);
    for (auto [a, b] : AB) {
        C[a]++;
        C[b]++;
    }
    rep(i, N) {
        if (C[i] != 2) {
            NO();
            return;
        }
    }

    vvl edges(N);
    rep(i, N) {
        auto [a, b] = AB[i];
        edges[a].eb(i);
        edges[b].eb(i);
    }
    vvi nodes(N);
    rep(i, N) {
        assert(edges[i].size() == 2);
        ll u = edges[i][0], v = edges[i][1];
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<ll> P(N, -1);
    auto dfs = [&](auto&& f, ll u, ll p) -> bool {
        if (P[u] != -1) {
            return P[u] == p;
        }
        P[u] = p;
        for (auto v : nodes[u]) {
            if (!f(f, v, 1-p)) {
                return false;
            }
        }
        return true;
    };
    rep(i, N) {
        if (P[i] != -1) continue;
        if (!dfs(dfs, i, 0)) {
            NO();
            return;
        }
    }
    YES();
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
