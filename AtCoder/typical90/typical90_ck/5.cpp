/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・BITによる転倒数取得、区切るDPとの複合的な尺取りの問題。
　DPとの兼ね合いでどうしても添字も必要になるが、
　それでも左端はdequeから受け取ればいいだけだし、
　尺取りがバグらないかどうかに使う神経はだいぶ減らせているのでは。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    Compress<ll> cp(A);
    ll M = cp.size();
    A = cp.zip(A);
    BIT<ll> bit(M);

    deque<ll> que;
    ll inv = 0;
    BIT<mint> dp(N + 1);
    dp.add(0, 1);
    rep(i, N) {
        inv += bit.query(A[i] + 1, M);
        bit.add(A[i], 1);
        que.pb(i);
        while (que.size() and inv > K) {
            inv -= bit.query(0, A[que.front()]);
            bit.add(A[que.front()], -1);
            que.pop_front();
        }
        assert(que.size());
        ll j = que.front();
        dp.add(i + 1, dp.query(j, i + 1));
    }
    mint ans = dp[N];
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
