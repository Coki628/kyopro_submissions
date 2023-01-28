/*
・自力AC！
・操作を整理すると、1回の変化は2箇所だけなので、
　その時抜けるやつと入るやつが一致なのか判定、で全体の一致数を持ち回る。
・TLとか公式解説見たけど、1点チェックよりは前後から累積した方が楽だったぽいかも。
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
    string S, T;
    cin >> S >> T;
    ll N = S.size();
    ll M = T.size();

    auto check = [&](ll i, ll j) {
        return S[i] == '?' or T[j] == '?' or S[i] == T[j];
    };
    ll cnt = 0;
    rep(i, N - M, N) {
        ll j = i - (N - M);
        if (check(i, j)) cnt++;
    }
    if (cnt == M) {
        Yes();
    } else {
        No();
    }
    rep(i, M) {
        if (check(i + (N - M), i)) {
            cnt--;
        }
        if (check(i, i)) {
            cnt++;
        }
        if (cnt == M) {
            Yes();
        } else {
            No();
        }
    }
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
