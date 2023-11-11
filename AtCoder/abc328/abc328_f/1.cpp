/*
・きっちり自力AC！
・重み付きUF
・これはすぐだった。重み付きUF、ついこの前Div.3バチャでやったしね。。
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

#include "graph/WeightedUnionFind.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    WeightedUnionFind<ll> uf(N);
    vector<ll> ans;
    rep(i, Q) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        if (uf.same(a, b)) {
            if (uf.validate(b, a, d)) {
                ans.eb(i);
            }
        } else {
            uf.merge(b, a, d);
            ans.eb(i);
        }
    }
    ans++;
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
