/*
・きっちり自力AC！
・クエリ先読みで座圧してBITにぶたん
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
    ll Q;
    cin >> Q;

    vector<array<ll, 3>> qs;
    vector<ll> tmp;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            qs.pb({op, x, -1});
            tmp.eb(x);
        } else {
            ll x, k;
            cin >> x >> k;
            qs.pb({op, x, k});
            tmp.eb(x);
        }
    }

    Compress<ll> cp(tmp);
    ll N = cp.size();
    BIT<ll> bit(N);
    rep(i, Q) {
        auto [op, x, k] = qs[i];
        if (op == 1) {
            bit.add(cp[x], 1);
        } elif (op == 2) {
            ll res = bit.bisearch_back(0, cp[x], k);
            if (res != -1) {
                res = cp.unzip(res);
            }
            print(res);
        } else {
            ll res = bit.bisearch_fore(cp[x], N-1, k);
            if (res != -1) {
                res = cp.unzip(res);
            }
            print(res);
        }
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
