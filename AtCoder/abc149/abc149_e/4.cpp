/*
・dojo set_e_4_2
・自力AC！
・決め打ち二分探索、端数処理
・定番の決め打ちにぶたん！と思ったら端数処理考えるのが地味に面倒だった。
　まあ結局、境界-1した値を余った個数分足せばよかったんだけど。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    sort(ALL(A));
    ll x = bisearch_min(0, INF, [&](ll m) {
        ll cnt = 0;
        rep(i, N) {
            cnt += N-bisect_left(A, m-A[i]);
        }
        return cnt <= M;
    });

    Accumulate<ll> acc(A);
    ll ans = 0, cnt = M;
    rep(i, N-1, -1, -1) {
        ll j = N-bisect_left(A, x-A[i]);
        cnt -= j;
        ans += acc.query(N-j, N)+A[i]*j;
    }
    // 端数
    ans += (x-1)*cnt;
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
