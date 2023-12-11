/*
参考：https://codeforces.com/blog/entry/123160
・自力ならず。
・場合分け、にぶたん
・操作3回以上で常に0達成のギャグは予想できたんだけど、
　K=2の場合を詰め切れていなかった。
　最初の操作で隣接以外も全部試した上で、
　2回目の操作でどれと組ませるかを全部見ればOK。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    if (K >= 3) {
        print(0);
        return;
    }
    vector<ll> nxt;
    sort(ALL(A));
    rep(i, A.size() - 1) {
        nxt.eb(A[i + 1] - A[i]);
    }
    ll ans = min(min(A), min(nxt));
    if (K == 1) {
        print(ans);
        return;
    }
    // 1回目の操作を(ソート済隣接だけでなく)全通り試す
    vector<ll> nxt2;
    rep(i, N) {
        rep(j, i + 1, N) {
            nxt2.eb(A[j] - A[i]);
        }
    }
    // 2回目の操作でnxt2[i]を一番値が近いA[j]と組ませるとする
    rep(i, nxt2.size()) {
        ll j = bisect_left(A, nxt2[i]);
        chmin(ans, abs(nxt2[i] - A[j]));
        if (j > 0) {
            chmin(ans, abs(nxt2[i] - A[j - 1]));
        }
        // rep(j, N) {
        //     chmin(ans, abs(nxt2[i] - A[j]));
        // }
    }
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
    while (T--) solve();

    return 0;
}
