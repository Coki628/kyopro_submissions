/*
・自力AC！
・サンプルを見ると、まず1箇所に固めてbが正しい所まで増やして、
　残りの要素にK-1ずつ入れればbを変えずに総和が増やせるので、
　これでうまくいけばOK、みたいに見える。実際、そうやると通る。
　(まんべんなく作った場合よりこっちのが確実にうまくいく理由はよく分かってない。)
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
    ll N, K, b, s;
    cin >> N >> K >> b >> s;

    ll mn = K * b;
    ll mx = K * b + K - 1;
    if (s < mn) {
        print(-1);
        return;
    }
    if (mn <= s and s <= mx) {
        vector<ll> ans(N);
        ans[0] = s;
        print(ans);
    } else {
        vector<ll> ans(N);
        ans[0] = mx;
        ll sm = mx;
        rep(i, 1, N) {
            ll use = min(s-sm, K-1);
            ans[i] = use;
            sm += use;
        }
        if (sm == s) {
            print(ans);
        } else {
            print(-1);
        }
    }
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
