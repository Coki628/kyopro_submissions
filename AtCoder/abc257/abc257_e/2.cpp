/*
参考：https://atcoder.jp/contests/abc257/editorial
・自力ならず。。
・まじでこんな貪欲Eで通ったら許せねぇよみたいな貪欲で通るのね…。
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
    auto cost = LIST(9);
    cost.insert(cost.begin(), INF);

    string ans;
    ll mn = min(cost);
    ll mxd = N / mn;
    ll cur = 0;
    rep(i, mxd) {
        rep(j, 9, -1, -1) {
            if (cur+cost[j]+mn*(mxd-i-1) <= N) {
                ans += tochar(j);
                cur += cost[j];
                break;
            }
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
