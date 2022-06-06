/*
・きっちり自力AC。ランクBに昇格。
・集合をビットと対応付けると、場合分け要らなくてすっきり。
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
#include "common/print.hpp"
#include "common/input.hpp"

void solve() {
    map<char, ll> mp = {{'R', 1}, {'G', 2}, {'B', 4}, {'Y', 3}, {'M', 5}, {'C', 6}, {'W', 7}};
    ll Q;
    cin >> Q;
    auto A = LIST(3);

    rep(i, Q) {
        char t, c;
        cin >> t >> c;

        ll bit = mp[c];
        rep(k, 3) {
            if (bit>>k & 1) {
                A[k] += (t == 'L') ? -1 : 1;
            }
        }
        if (A[0] == A[1] and A[1] == A[2]) {
            print(A[0]);
            return;
        }
    }
    print("no");
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
