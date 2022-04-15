/*
参考：https://twitter.com/shiro537/status/1513151258676264962
・なんと愚直も通る…。最大3万回まともにフロー流してんのかな？
　まあ全部やることはほぼなさそうだけど、それでもすごいな…。AC1.35秒。
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

#include "acl/mincostflow.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    vector<array<ll, 3>> ABC;
    rep(i, N) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        ABC.pb({a, b, c});
    }

    ll M = 150;
    ll offset = 1e9;
    vector<ll> ans;
    rep(k, 1, N+1) {
        mcf_graph<ll, ll> mcf(M*2+2);
        ll s = M * 2;
        ll t = M * 2 + 1;
        for (auto [a, b, c] : ABC) {
            mcf.add_edge(a, M+b, 1, offset-c);
        }
        rep(i, M) {
            mcf.add_edge(s, i, 1, 0);
            mcf.add_edge(M+i, t, 1, 0);
        }
        auto [cap, cost] = mcf.flow(s, t, k);
        if (cap < k) break;
        ans.eb(offset*k - cost);
    }
    print(ans.size());
    for (auto a : ans) print(a);
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
