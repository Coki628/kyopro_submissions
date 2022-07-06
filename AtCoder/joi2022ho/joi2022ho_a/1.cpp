/*
・JOI埋め
・きっちり自力AC！
・ランレングス圧縮、累積和、二分探索
・さすがにこれはね。やることきっちりやる。
　にぶたん境界の微調整に少しもたついてイマイチ。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<pll> ans;
    rep(i, N) {
        ll cnt = 0;
        while (A[i]%2 == 0) {
            A[i] /= 2;
            cnt++;
        }
        ans.eb(pow(2, cnt), A[i]);
    }
    vector<ll> B(N);
    rep(i, 1, N) {
        B[i] = B[i-1] + ans[i-1].first;
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll x;
        cin >> x;
        ll i = bisect_left(B, x) - 1;
        print(ans[i].second);
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
