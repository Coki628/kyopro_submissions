/*
・自力AC！
・基本的に隣と同じものを選び続ける貪欲。
　最初をどっちにするかだけ両方試す。
・こちらも最初別方針引いてしまってタイムロス…。
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

    string ans;
    ll mn = INF;
    rep(x, 2) {
        string cur = S;
        ll cost = 0;
        rep(i, N) {
            if (cur[i] == '?') {
                if (i == 0) {
                    cur[i] = '0' + x;
                } else {
                    cur[i] = cur[i - 1];
                }
            }
            if (i > 0 and cur[i - 1] != cur[i]) {
                cost++;
            }
        }
        if (chmin(mn, cost)) {
            ans = cur;
        }
    }
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
