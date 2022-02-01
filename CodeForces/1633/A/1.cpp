/*
・自力AC。今日はここもたついたのが良くなかったな。。
・桁数の同じ数字全部見ればいいだけなのに、何か実装方針悩んでバグり散らかした。
　結局ループ1000まで全部回して判定した。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    if (toint(S)%7 == 0) {
        print(S);
        return;
    }
    ll N = S.size();
    ll mn = INF;
    string ans, cur;
    rep(i, 1, 1000) {
        auto T = tostr(i);
        if (T.size() != N) continue;
        if (i%7 == 0) {
            ll diff = 0;
            rep(j, N) {
                if (S[j] != T[j]) diff++;
            }
            if (chmin(mn, diff)) {
                ans = T;
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
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
