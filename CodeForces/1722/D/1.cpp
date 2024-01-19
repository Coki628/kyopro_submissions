/*
・きっちり自力AC！
・利得が大きい方から貪欲にやる。
　列挙なので、ソートしといて1個ずつやる。
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
    string S;
    cin >> S;

    vector<ll> diff;
    ll cur = 0;
    rep(i, N) {
        ll lcnt = i;
        ll rcnt = N - i - 1;
        if (S[i] == 'L') {
            cur += lcnt;
            diff.eb(max(lcnt, rcnt) - lcnt);
        } else {
            cur += rcnt;
            diff.eb(max(lcnt, rcnt) - rcnt);
        }
    }
    sort(ALL(diff));
    vector<ll> ans(N);
    rep(i, N) {
        cur += diff.back();
        diff.pop_back();
        ans[i] = cur;
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
