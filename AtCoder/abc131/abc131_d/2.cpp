/*
・区間スケジューリング
・直感的に所要時間Aiを加味して引いた方がいい気がしちゃったんだけど、
　ごくごく普通に右端ソートの区間スケジューリングが正解だった。
　こういうの適当じゃなくてちゃんと一発で見抜くにはどうしたらいいんだろうか…。
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
    vector<array<ll, 2>> AB(N);
    rep(i, N) {
        cin >> AB[i][0] >> AB[i][1];
    }

    sort(ALL(AB), [](array<ll, 2> a, array<ll, 2> b) {
        // return (a[1] - a[0] < b[1] - b[0]);
        return a[1] < b[1];
    });
    ll t = 0;
    rep(i, N) {
        auto [a, b] = AB[i];
        t += a;
        if (t > b) {
            No();
            return;
        }
    }
    Yes();
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
