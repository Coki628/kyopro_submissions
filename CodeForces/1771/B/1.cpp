/*
・きっちり自力AC！
・辺がない所を数える。辺をu<vとして、左端iを固定すると、
　i以降の頂点uと繋がる頂点vが最初に出現する手前、までが右端jとできる。
　後ろから、今見ている頂点をuとした時のvをBITに全部追加した後、
　[u,N)をにぶたんして一番左の出現位置を見つける、みたいにした。
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
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v)
            swap(u, v);
        nodes[u].eb(v);
    }

    BIT<ll> bit(N + 1);
    bit.add(N, 1);
    ll ans = 0;
    rep(u, N - 1, -1, -1) {
        for (auto v : nodes[u]) {
            bit.add(v, 1);
        }
        ll x = bit.bisearch_fore(u, N, 1);
        ll cnt = x - u;
        ans += cnt;
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
    while (T--)
        solve();

    return 0;
}
