/*
・順列の逆みたいな配列作っとくやつ。
　これBで聞く？って思ったけど、よく見ると制約が緩かった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N;
    cin >> N;
    vector<ll> P(N);
    cin >> P;
    P--;

    vector<ll> rev(N);
    rep(i, N) {
        rev[P[i]] = i;
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        ll res = rev[a] < rev[b] ? a : b;
        print(res + 1);
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
