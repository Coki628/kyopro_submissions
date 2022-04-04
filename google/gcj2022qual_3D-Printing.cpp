/*
・きっちり自力AC！
・3色になるべく大きく割当、4色目やって余るならNG、
　足りなくなったら割当済の3色からぴったりになるまで融通してもらう、ってやった。
　何かゴチャゴチャしちゃったけど絶対もっと簡単にできそう…
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
    ll N = 4, M = 3;
    auto A = list2d(N, M, 0LL);
    rep(j, M) {
        rep(i, N) {
            cin >> A[i][j];
        }
    }

    vector<ll> ans(N);
    ll sm = 0;
    rep(i, N-1) {
        ans[i] = min(A[i]);
        sm += ans[i];
    } 
    ans[N-1] = 1e6 - sm;
    if (ans[N-1] > min(A[N-1])) {
        print("IMPOSSIBLE");
        return;
    }
    if (ans[N-1] < 0) {
        rep(i, N-1) {
            ll use = min(-ans[N-1], ans[i]);
            ans[N-1] += use;
            ans[i] -= use;
        }
    }
    assert(sum(ans) == 1e6);
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
    rep(i, 1, T+1) {
        cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
