/*
・これは結構すんなり自力AC！
・文字aから順に貪欲に埋めてく。陽に最初から構築すると計算量がダメなので、
　使うかどうかだけ配列に全部持っておいて、最後に作る。
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
    ll P;
    cin >> P;

    ll L = 26, cost = 0;
    vector<bool> used(N);
    rep(c, L) {
        rep(i, N) {
            if (S[i]-'a' == c and cost+c+1 <= P) {
                used[i] = true;
                cost += c + 1;
            }
        }
    }
    string ans;
    rep(i, N) {
        if (used[i]) {
            ans += S[i];
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
