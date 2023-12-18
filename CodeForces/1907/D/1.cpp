/*
・きっちり自力AC！
・区間のANDマージ、決め打ちにぶたん
・区間のORマージは場合分けがたくさんでつらい(のでRangeSetに投げる)けど、
　ANDマージはそんなでもない。(ソースコード内intersect関数を参照)
　今行ける範囲を持っておいて、[左端-K,右端+K]の範囲は全部行けるものとして、
　次の区間との共通部分を取るとすると、最後まで行けるかどうかが決め打ちにぶたんできる。
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
    auto intersect = [](pll a, pll b) -> pll {
        ll l = max(a.first, b.first);
        ll r = min(a.second, b.second);
        return {l, r};
    };
    ll N;
    cin >> N;
    vector<pll> LR;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        LR.eb(l, r);
    }

    ll res = bisearch_min(-1, 1e15, [&](ll K) {
        pll cur = {0, 0};
        for (auto [l, r] : LR) {
            auto [nxl, nxr] = intersect({cur.first - K, cur.second + K}, {l, r});
            if (nxl > nxr) {
                return false;
            }
            cur = {nxl, nxr};
        }
        return true;
    });
    print(res);
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
