/*
・きっちり自力AC！
・決め打ちにぶたん
・ロゴ入りは明らかに上位互換なので、両方ある時は無地を使う、の貪欲が効く。
　買う枚数を決め打ちにぶたんでシミュ、最後までできたか？でOK。
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
    ll N, M;
    cin >> N >> M;
    string S;
    cin >> S;

    ll res = bisearch_min(-1, INF, [&](ll x) {
        ll a = M, b = x;
        rep(i, N) {
            if (S[i] == '0') {
                a = M, b = x;
            } else if (S[i] == '1') {
                if (a > 0) {
                    a--;
                } else if (b > 0) {
                    b--;
                } else {
                    return false;
                }
            } else {
                if (b > 0) {
                    b--;
                } else {
                    return false;
                }
            }
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
