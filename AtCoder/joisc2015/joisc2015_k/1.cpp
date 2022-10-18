/*
参考：https://www.ioi-jp.org/camp/2015/2015-sp-tasks/2015-sp-d4-inheritance-review.pdf
・JOI埋め
・自力ならず。。これは悔しい。
・MST、二分探索
・K*NでUF作ってMSTの辺マージをKが小さい方から試す。ここまではできた。
　でもこれににぶたんが効くとは思わなかった。公式解説の証明聞いてもまだピンと来てない。
　だって各K全然違う辺が付いてる訳だから、iでu,vが連結でもi-1でu,vが連結とは限らなくない？
　って書きながらもなんか言われたら確かにそれはそうな気もしてきたし、もう何も分からん。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<tuple<ll, ll, ll, ll>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.pb({c, u, v, i});
    }

    sort(edges.rbegin(), edges.rend());
    vector<UnionFind> uf(K, {N});
    vector<ll> ans(M);
    for (auto& edge : edges) {
        ll c, u, v, i;
        tie(c, u, v, i) = edge;
        ll j = bisearch_min(-1, K, [&](ll x) {
            return (not uf[x].same(u, v));
        });
        if (j < K) {
            uf[j].merge(u, v);
            ans[i] = j + 1;
        }
        // rep(j, K) {
        //     if (not uf[j].same(u, v)) {
        //         uf[j].merge(u, v);
        //         ans[i] = j + 1;
        //         break;
        //     }
        // }
    }
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
