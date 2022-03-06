/*
・dojo set_e_4_1
・きっちり自力AC！
・最初、Aiが1か2だってとこ読んでなくて無理じゃん、ってなってた。。
　偶奇は分かるので、UFして連結成分数でOK。
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

    UnionFind uf(N);
    rep(i, M) {
        ll x, y, z;
        cin >> x >> y >> z;
        x--; y--;
        uf.merge(x, y);
    }

    ll ans = uf.size();
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
