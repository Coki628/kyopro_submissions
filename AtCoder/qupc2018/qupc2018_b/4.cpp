/*
・dojo set_e_5_d
・きっちり自力AC。
・大きい方から、
　・前の桁で差分が出てればなるべく相殺する
　・奇数枚あるなら今少ない方に1枚多く渡す
　・最後までやって合わなければNG
　みたいなお気持ち貪欲やって祈ったら通った。
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
    ll a, b, c;
    cin >> a >> b >> c;

    ll cnt = 0;
    if (a%2 == 1) {
        cnt += 100;
    }
    ll use = min(cnt/10, b);
    cnt -= use*10;
    b -= use;
    if (b%2 == 1) {
        cnt = cnt > 0 ? cnt-10 : cnt+10;
    }
    use = min(cnt, c);
    cnt -= use;
    c -= use;
    if (c%2 == 1) {
        cnt = cnt > 0 ? cnt-1 : cnt+1;
    }
    if (cnt == 0) Yes();
    else No();
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
