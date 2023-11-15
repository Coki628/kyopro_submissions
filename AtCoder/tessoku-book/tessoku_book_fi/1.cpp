/*
・自力AC！
・決め打ちにぶたん、実数にぶたん
・「全体でK議席以上になるような最大ボーダー」で決め打ちにぶたんする。
　比例代表の議席の配分が決め打ちにぶたんの問題になるって面白いね。
・公式解説見た。内側のにぶたん、割り算1回じゃん。。またやってしまったな。
　割り算やるだけのにぶたんは1回にできるか検討しないとな。
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

#include "common/bisearch_real.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ld border = bisearch_max(0, INF, [&](ld x) {
        ll cnt = 0;
        for (auto a : A) {
            cnt += bisearch_max(0, INF, [&](ld y) {
                return a / y >= x;
            });
        }
        return cnt >= K;
    }, 100);
    // print(border);
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = bisearch_max(0, INF, [&](ld y) {
            return A[i] / y >= border;
        });
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
