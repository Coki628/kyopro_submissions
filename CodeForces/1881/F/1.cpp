/*
・自力AC！
・最遠点、全方位木DP
・普通に最遠点だと全方位で列挙するのは前にやったことがあって、
　今回はマークされた頂点のみ使うということで、どうするか考える。
　ちょっと悩んだけど、普通の木DPで葉から遷移してくる時、
　どうすればうまくいきそうか考えたら、いい感じの遷移が作れた。
　既に1個以上候補があるなら使うし、最初であれば使える頂点かをチェックする。
・なお、マークされた頂点で木の直径を求めれば、
　直径のどちらかがいずれの頂点からも最遠点になる模様。
　これだとBFSとかで何回か最短距離取るだけでほぼできるのね。。
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

#include "graph/ReRooting.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(K);
    cin >> A;
    A--;
    vector<ll> C(N);
    for (auto a : A) {
        C[a] = 1;
    }

    auto f1 = [](ll a, ll b) -> ll { return max(a, b); };
    auto f2 = [](ll a, bool x) -> ll {
        if (not x and a == 0) {
            return 0;
        } else {
            return a + 1;
        }
    };
    auto rr = get_rerooting(N, f1, f2, 0LL, false);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        rr.add_edge_bi(u, v, C[v], C[u]);
    }
    auto res = rr.build();
    ll ans = min(res);
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
