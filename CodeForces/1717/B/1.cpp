/*
・自力AC！
・実装
・実装ゲーする。等間隔に斜め線引けたらいい。
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
    ll N, K, r, c;
    cin >> N >> K >> r >> c;

    r--; c--;
    ll dh = r, dw = c;
    while (dh > 0) {
        dh--;
        dw = modulo(dw-1, N);
    }
    vector<string> ans(N, string(N, '.'));
    rep(h, N) {
        rep(w, 0, N, K) {
            ans[h][(w+dw)%N] = 'X';
        }
        dw++;
    }
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
