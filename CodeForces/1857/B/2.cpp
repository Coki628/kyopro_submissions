/*
参考：https://codeforces.com/contest/1857/submission/217773626
・ちゃんと下から繰り上げて見て行く方針。これがやりたかった。
　下位桁の0埋めを最後にまとめてやると、色々うまくいった。
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
    string S;
    cin >> S;
    ll N = S.size();

    string ans = S;
    ll carry = 0, zero = N;
    rep(i, N - 1, -1, -1) {
        // この桁を答えに使うことになった時のために、繰り上げ後の結果を保持しておく
        if (S[i] + carry > '9') {
            ans[i] = '0';
        } else {
            ans[i] = S[i] + carry;
        }
        if (S[i] + carry >= '5') {
            carry = 1;
            zero = i;
        } else {
            carry = 0;
        }
    }
    // 一番最後に繰り上がった所が強いので、そこより下位桁は後から0埋め
    rep(i, zero, N) {
        ans[i] = '0';
    }
    if (carry) {
        ans.insert(ans.begin(), '1');
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
