/*
・自力AC。ちょっともたついた。
・各シート間のスキマの長さlenとして、ceil(len, W)みたいのを総和。
　最初もっとゴチャゴチャさせてしまってタイムロス。。
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
    ll N, L, W;
    cin >> N >> L >> W;
    auto A = LIST(N);

    A.eb(L);
    ll need = A[0];
    ll ans = ceil(need, W);
    rep(i, N) {
        ll l = A[i];
        ll r = l+W;
        need = A[i+1]-r;
        if (need <= 0) continue;
        ans += ceil(need, W);
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
