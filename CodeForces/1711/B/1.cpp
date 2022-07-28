/*
・終了後自力AC。本番終了3分前くらいに本質らしきものに気付き、終了3分後くらいで書き上げ…。
・辺の本数Mが偶数なら何もしなくていい。以下奇数の場合。
　結局、減らす頂点は1～2個でいい。次数が奇数の頂点があればそこ1つを外せばいいし、
　偶数の頂点しかなかったら、辺で隣接した2頂点を外せば、減る辺の本数は偶数+偶数-1となって奇数。
　よって全ての頂点と全ての辺を全探索すれば、最適な外す箇所が見つかる。
・C結局解けなかったし、こっち早くもっとちゃんと考えてればよかった…。
　とはいえこういうのいくら考えても思いつけない時もあるし悩ましい。
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    vvi nodes(N);
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        edges.eb(u, v);
    }

    if (M%2 == 0) {
        print(0);
        return;
    }

    ll ans = INF;
    rep(i, N) {
        if (nodes[i].size()%2 == 1) {
            chmin(ans, A[i]);
        }
    }
    for (auto [u, v] : edges) {
        if ((nodes[u].size()+nodes[v].size())%2 == 0) {
            chmin(ans, A[u]+A[v]);
        }
    }
    print(ans);
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
