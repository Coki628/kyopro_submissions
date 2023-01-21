/*
・きっちり自力AC！
・サイクルシフト、回文
・サイクルシフト全探索の内側で回文の文字一致チェック。
　まあ2乗大丈夫なので普通にやってOK。
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
    ll N, a, b;
    cin >> N >> a >> b;
    string S;
    cin >> S;

    ll ans = INF;
    rep(x, N) {
        ll cnt = a * x;
        rep(i, N / 2) {
            if (S[i] != S[N - i - 1]) {
                cnt += b;
            }
        }
        chmin(ans, cnt);
        S = S.substr(1) + S[0];
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
