/*
・きっちり自力AC！
・場合分け祭り。行って戻ったりを色々検討する。0,1,2,3,-1の5パターンになる。
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
    ll l, r, x;
    cin >> l >> r >> x;
    ll a, b;
    cin >> a >> b;

    if (a > b) {
        swap(a, b);
    }
    if (a == b) {
        print(0);
    } elif (abs(a-b) >= x) {
        print(1);
    } elif (abs(a-l) >= x or abs(b-r) >= x) {
        print(2);
    } elif (abs(a-r) >= x and abs(b-l) >= x) {
        print(3);
    } else {
        print(-1);
    }
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
