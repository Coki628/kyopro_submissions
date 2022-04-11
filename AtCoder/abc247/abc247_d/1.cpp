/*
・きっちり自力AC！
・ランレングスっぽく持って、dequeでシミュる。
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

    deque<pll> que;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, c;
            cin >> x >> c;
            que.eb(x, c);
        } else {
            ll c;
            cin >> c;
            ll sm = 0;
            while (c) {
                if (c-que.front().second < 0) {
                    sm += que.front().first * c;
                    que.front().second -= c;
                    break;
                } else {
                    c -= que.front().second;
                    sm += que.front().first * que.front().second;
                    que.pop_front();
                }
            }
            print(sm);
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
