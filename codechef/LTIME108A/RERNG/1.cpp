/*
・部分点1
・隣の要素を覚えておいて、並びの変わらない数だけ、切らなくて済む、としたらうまくいった。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    assert(N <= 1000 and Q <= 1000);

    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;

        auto cur1 = subarray(A, l, r);
        ll n = cur1.size();
        vector<ll> nxt(N, -1);
        rep(i, n-1) {
            nxt[cur1[i]] = cur1[i+1];
        }

        auto cur2 = sorted(cur1);
        ll cnt = 0;
        rep(i, n-1) {
            if (nxt[cur2[i]] == cur2[i+1]) {
                cnt++;
            }
        }
        ll res = n - cnt;
        print(res);
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
