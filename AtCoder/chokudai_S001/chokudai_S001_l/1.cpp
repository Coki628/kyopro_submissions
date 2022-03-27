/*
・きっちり自力AC！
　ふらっと見かけて、通せそうな雰囲気を感じて、やってみたらできた。
・(隣接じゃない)2点スワップ、functional graph、連結成分数、UnionFind
・前に隣接じゃないスワップは連結成分数って知見を得ていたので、すぐ思い出せて良かった。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    rep(i, N) A[i]--;

    UnionFind uf(N);
    rep(i, N) {
        uf.merge(i, A[i]);
    }
    ll cnt = 0;
    for (auto r : uf.get_roots()) {
        cnt += uf.size(r) - 1;
    }
    if (N%2 == cnt%2) {
        YES();
    } else {
        NO();
    }
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
