/*
・自力AC。ちょっともたついた…。
・区間スケジューリング
・典型ド真ん中の区間スケジューリングで右端ソートなのに、
　なんか違う感じにしちゃって1ペナ。まじでしょうもない…。
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
    vector<pll> RL;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        RL.eb(r, l);
    }

    sort(ALL(RL));
    ll ans = 0, cur = 0;
    for (auto [r, l] : RL) {
        if (cur <= l) {
            ans++;
            cur = r;
        }
    }
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
