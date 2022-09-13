/*
・きっちり自力AC！
・S[0]からS[N-1]までの文字種を全部通るといい。
　文字種毎の隣接リストにindex詰めた。
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
    string S;
    cin >> S;
    ll N = S.size();

    ll M = 26;
    vvl adj(M);
    rep(i, N) {
        adj[S[i]-'a'].eb(i);
    }
    char s = S[0]-'a', g = S[N-1]-'a';
    bool swapped = false;
    if (s > g) {
        swap(s, g);
        rep(c, M) {
            reverse(ALL(adj[c]));
        }
        swapped = true;
    }
    ll cost = g - s;
    vector<ll> routes;
    rep(c, s, g+1) {
        for (auto i : adj[c]) {
            routes.eb(i+1);
        }
    }
    if (swapped) {
        reverse(ALL(routes));
    }
    print(mkp(cost, routes.size()));
    print(routes);
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
