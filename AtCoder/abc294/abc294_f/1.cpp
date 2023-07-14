/*
参考：https://atcoder.jp/contests/abc294/editorial/6007
・upsolve、自力ならず。
・決め打ちにぶたん、K番目の値、式変形
・射撃王みたいなやつ。この式変形アプローチも何回か見てるけど、
　いつも見抜けなくて終わってる。。
・目指す濃度xを決め打つと、式変形をうまくやれば必要な砂糖量が定まるので、
　ここから自身の砂糖を引いた値をキーにしてソート。
　これで必要な砂糖量に基づいた単調性が作れるので、
　他方の列の値で内側のにぶたんすれば、K番目の値を求めるいつものになる。
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

#include "common/bisearch_real.hpp"

ld calc(ld x, ld y) {
    return x / (x + y);
}

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(N), B(N), C(M), D(M);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }
    rep(i, M) {
        cin >> C[i] >> D[i];
    }

    ld res = bisearch_max(0, 1, [&](ld x) {
        vector<tuple<ld, ll, ll>> vec;
        rep(i, M) {
            // 濃度xを達成するために必要な砂糖量need
            ld need = x * D[i] / (1.0 - x);
            vec.eb(C[i] - need, C[i], D[i]);
        }
        sort(ALL(vec));
        ll k = 0;
        rep(i, N) {
            ll m = bisearch_min(-1, M, [&](ll j) {
               auto [_, c, d] = vec[j];
               ld val = calc(A[i] + c, B[i] + d);
               return val >= x;
            });
            k += M - m;
        }
        return k >= K;
    }, 100) * 100;
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
