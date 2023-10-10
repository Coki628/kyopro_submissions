/*
・自力AC！
・部分和DP、決め打ちにぶたん
・微妙に小さい制約から、何か状態持ってDPできないか考える。
　水魔法か炎魔法のどちらかで敵を倒すんだけど、
　どっちで倒すさえ決めてしまえば後は数値が足りれば倒せるので、
　これには部分和DPで和の取り方を網羅するといい。
　経過時間は決め打ちにぶたんでちょうどいい所を探せる。
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
    ll W, F;
    cin >> W >> F;
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll M = sum(A);
    auto dp = listnd(2, M + 1, 0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, M + 1) {
            if (dp[i % 2][j]) {
                dp[(i + 1) % 2][j] = 1;
                dp[(i + 1) % 2][j + A[i]] = 1;
                dp[i % 2][j] = 0;
            }
        }
    }

    ll res = bisearch_min(0, INF, [&](ll x) {
        if (mul_overflow(W, x) or mul_overflow(F, x)) {
            return true;
        }
        ll wval = W * x, fval = F * x;
        if (wval > fval) swap(wval, fval);
        rep(i, M + 1) {
            if (dp[N % 2][i]) {
                ll a = i;
                ll b = M - a;
                if (a > b) swap(a, b);
                if (a <= wval and b <= fval) {
                    return true;
                }
            }
        }
        return false;
    });
    print(res);
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
