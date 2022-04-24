/*
・ハック対応。
・区間加算BITでサボってた所を累積和と下駄の変数addで対応した。
　これだとAC0.30秒、と思ったけどECR系のハックだとシステスに盛り込まれないみたい。
　ハックケースで通るか未検証。
　(システスだけだと、落とされたコードでも1.15秒で通る。)
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, x;
    cin >> N >> x;
    auto A = LIST(N);

    sort(ALL(A));
    A.eb(INF);
    Accumulate<ll> acc(A);
    ll cur = acc.bisearch_fore(0, N, x+1);
    ll ans = 0, add = 0;
    while (cur > 0) {
        ll res = bisearch_max(0, x+1, [&](ll m) {
            ll nxt = bisearch_min(-1, N+1, [&](ll r) {
                return acc.query(0, r+1) + (r+1)*(add+m) >= x+1;
            });
            return cur == nxt;
            // bit.add(0, N, m);
            // ll nxt = bit.bisearch_fore(0, N, x+1);
            // bit.add(0, N, -m);
            // return cur == nxt;
        }) + 1;
        ans += cur * res;
        // bit.add(0, N, res);
        add += res;
        cur = bisearch_min(-1, N+1, [&](ll r) {
            return acc.query(0, r+1) + (r+1)*add >= x+1;
        });
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
