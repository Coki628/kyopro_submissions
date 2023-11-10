/*
・きっちり自力AC！
・隣接K以内が長く続くほど良いというもの。
　ソートして繋げるだけ繋いで、一番長い所を使う。
　ちょうど似た考察でUF使ったばっかりだったのですぐ出た。(cf1873F)
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    UnionFind uf(N);
    sort(ALL(A));
    rep(i, N - 1) {
        if (A[i + 1] - A[i] <= K) {
            uf.merge(i, i + 1);
        }
    }
    ll mx = 1;
    for (auto r : uf.get_roots()) {
        chmax(mx, uf.size(r));
    }
    ll ans = N - mx;
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
