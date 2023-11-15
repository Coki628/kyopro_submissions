/*
・自力AC！
・3乗の区間DP、定数倍高速化、QCFium法
・普通に3乗の区間DPだけど、区切り位置を毎回2箇所入れる感じ。
　区間DPは毎回添字に苦しむ印象があったけど、今回は全部半開区間を意識して、
　区間が0~2になった時の処理も適切に書いたら、結構すんなり仕上がった。
　計算量が4乗になって、Nが2Nで実質400なので数字上は相当きついが、
　半分になる所や通らない部分も多いので、定数倍は軽いと見て一応やってみた。
　普通にやったら2024msでTLEだけど打ち切りの2200msはクリアしていたので、
　ll全部intにしてQCFium法を解放すると、無事AC1.60秒。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    int N;
    cin >> N;
    N *= 2;
    vector<int> A(N);
    cin >> A;

    auto memo = listnd(N + 1, N + 1, -1);
    auto rec = [&](auto &&f, int l, int r) -> int {
        if (memo[l][r] != -1) return memo[l][r];
        int len = r - l;
        if (len == 0) return 0;
        if (len == 1) return MOD;
        if (len == 2) {
            return abs(A[l] - A[l + 1]);
        }
        int res = MOD;
        rep(i, l, r) {
            int lval = f(f, l, i);
            if (lval >= MOD) continue;
            rep(j, i + 1, r) {
                int mval = f(f, i + 1, j);
                if (mval >= MOD) continue;
                int rval = f(f, j + 1, r);
                if (rval >= MOD) continue;
                chmin(res, lval + mval + rval + abs(A[i] - A[j]));
            }
        }
        return memo[l][r] = res;
    };
    int res = rec(rec, 0, N);
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
