/*
・自力AC！Fより解かれてたけど、それでもボス問撃破は嬉しい。
・木DP、HLD、辺属性、累積和
・Aは前から木DP、BはHLD*累積和に突っ込んで、各頂点で根からのパス和をにぶたんした。
　絶対もっと簡単にやれそう。(通せたからまあOK)
・HLDに乗せるのをBITから累積和にしたんだけど、そこまで速度は変わらず。(BIT速いからね)
　0.39秒→0.30秒くらい。
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

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    vector<ll> A(N), B(N);
    rep(i, 1, N) {
        ll p, a, b;
        cin >> p >> a >> b;
        p--;
        nodes[p].eb(i);
        nodes[i].eb(p);
        A[i] = a;
        B[i] = b;
    }

    HeavyLightDecomposition hld(nodes);
    Accumulate<ll> acc(N);
    rep(i, N) {
        acc.add(hld.in[i], B[i]);
    }
    acc.build();
    vector<ll> ans(N), dpa(N);
    auto dfs = [&](auto&& f, ll u, ll prv, ll dep) -> void {
        dpa[u] += A[u];
        ll sub = bisearch_min(-1, dep, [&](ll m) {
            ll la = hld.la(u, m);
            ll b = hld.query(
                0, la, 0LL, [&](ll a, ll b) { return acc.query(a, b); },
                [](ll a, ll b) { return a + b; }, true
            );
            return dpa[u] >= b;
        });
        ans[u] = dep - sub;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            dpa[v] += dpa[u];
            f(f, v, u, dep+1);
        }
    };
    dfs(dfs, 0, -1, 0);
    ans.erase(ans.begin());
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
