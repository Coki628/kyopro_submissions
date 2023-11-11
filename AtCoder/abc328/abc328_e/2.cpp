/*
・別解。これなんでやらなかったんだろ…。
・組み合わせ全列挙
・なんかビットでpopcountしても2^Mが無理だしー、
　とかは考えたんだけど、組み合わせ全列挙を思い出さなかったんだよな。
　ちゃんとnCrのnが大きくても動くようにビットじゃなくて再帰版作ってあったのに。。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<array<ll, 3>> edges;
    rep(e, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edges.pb({u, v, c});
    }

    vector<ll> P(M);
    iota(ALL(P), 0);
    ll ans = INF;
    for (auto comb : combinations(P, N - 1)) {
        UnionFind uf(N);
        ll sm = 0;
        for (auto i : comb) {
            auto [u, v, c] = edges[i];
            uf.merge(u, v);
            sm = (sm + c) % K;
        }
        if (uf.size() == 1) {
            chmin(ans, sm);
        }
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
