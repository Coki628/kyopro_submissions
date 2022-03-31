/*
・二分探索、等差数列の和
・Kが大きくても(多分)通せる版。途中まで書いてたので一応書き切った。
・aを固定してbを動かす時、取るcの値の増加量は+1,0,-1みたいな区間になる。
　a = bで最大値を取ることも分かるので、
　ここより前と先でそれぞれ単調性があって二分探索できる。
　それぞれの区間の範囲が分かれば、等差数列の和と掛け算で一度に計算できる。
　なんだけど、添字がめっちゃバグってつらい。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    auto count = [&](ll a, ll b) -> ll {
        ll l = max({a-K+1, b-K+1, 1LL});
        ll r = min({a+K-1, b+K-1, N});
        ll res = max(r-l+1, 0LL);
        return res;
    };

    ll cnt = 0;
    rep(a, 1, N+1) {
        ll r1 = bisearch_min(max(a-K, 0LL), a, [&](ll m) {
            return count(a, m) == count(a, a);
        });
        ll l1 = bisearch_min(max(a-K, 0LL), r1, [&](ll m) {
            return count(a, m)+1 == count(a, m+1);
        });
        ll l2 = bisearch_max(a, min(a+K, N+1), [&](ll m) {
            return count(a, a) == count(a, m);
        });
        ll r2 = bisearch_max(l2, min(a+K, N+1), [&](ll m) {
            return count(a, m)-1 == count(a, m+1);
        });
        cnt += (
            arithmetic_sequence_sum(count(a, l1), 1LL, r1-l1) +
            count(a, a)*(l2-r1) +
            arithmetic_sequence_sum(count(a, l2), -1LL, r2-l2+1)
        );

        // rep(b, max(a-K+1, 1LL), min(a+K, N+1)) {
        //     ll cur = count(a, b);
        //     cnt += cur;
        //     debug(a);
        //     debug(b);
        //     debug(cur);
        // }
    }
    // debug(cnt);
    ll ans = pow(N, 3) - cnt;
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
