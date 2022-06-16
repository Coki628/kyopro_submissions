/*
・自力AC。
・順列、構築
・なんか普通に前から順に探してスワップしてくるんでも
　案外うまく行きそうに見えたのでぶん投げると、さすがにWA。
　どういうケースでダメか検討すると、
　移動先がスワップ時に大,小,中→大,中,小となるとダメそう。
　手前と予めスワップして小,大,中にしておけば大丈夫そう。これで通った。
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
    ll N;
    cin >> N;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vector<pll> ans;
    rep(i, N) {
        ll j = find(ALL(P), i) - P.begin();
        if (j == i) continue;
        if (i != j-1 and P[j-1] > P[i]) {
            swap(P[j-1], P[j]);
            ans.eb(j, j+1);
            swap(P[i], P[j-1]);
            ans.eb(i+1, j);
        } else {
            swap(P[i], P[j]);
            ans.eb(i+1, j+1);
        }
    }
    print(ans.size());
    print(ans, '\n');
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
