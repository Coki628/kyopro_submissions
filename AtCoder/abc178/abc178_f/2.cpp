/*
参考：https://twitter.com/kichi2004_/status/1305139368596627457
・乱択スワップ
・結局自作の乱択ロジックでは通らず、kichiさんのをほぼ写経したら通った…。
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

#include "common/Timer.hpp"
#include "common/randrange.hpp"
#include "common/sample.hpp"

void solve() {
    Timer timer;
    const int TL = 1900;
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    vector<ll> C(N + 1);
    rep(i, N) {
        C[A[i]]++;
        C[B[i]]++;
    }
    if (max(C) > N) {
        No();
        return;
    }

    auto ans = B;
    reverse(ALL(ans));
    ll same = 0;
    rep(i, N) {
        if (A[i] == ans[i]) same++;
    }

    while (timer.get_elapse() < TL) {
        ll i = randrange(0, N);
        ll j = randrange(0, N);
        if (A[i] == ans[j] or A[j] == ans[i]) continue;

        if (A[i] == ans[i]) same--;
        if (A[j] == ans[j]) same--;
        swap(ans[i], ans[j]);

        if (same == 0) {
            Yes();
            print(ans);
            return;
        }
    }
    No();
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
