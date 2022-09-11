/*
・ランダムテスト用愚直解
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
    ll N;
    cin >> N;
    auto P = LIST(N);

    vector<ll> cost(N);
    rep(i, N) {
        ll d = modulo(P[i]-i, N);
        ll l = d;
        ll r = min(l+N/2, N);
        ll b = 0;
        rep(j, l, r) {
            cost[j] += b;
            b++;
        }
        // seg.update(l, r, {1, 0});
        l = r;
        if (l < N and N%2 == 1) {
            cost[l] += N / 2;
            // seg.update(l, l+1, {1, N/2});
            l++;
        }
        if (l < N) {
            r = min(l+N/2, N);
            b = N / 2;
            rep(j, l, r) {
                cost[j] += b;
                b--;
            }
            // seg.update(l, r, {-1, N/2});
        }
        r = d;
        l = max(r-N/2, 0LL);
        ll len = r - l;
        b = len;
        rep(j, l, r) {
            cost[j] += b;
            b--;
        }
        // seg.update(l, r, {-1, len});
        r = l;
        if (r > 0 and N%2 == 1) {
            cost[r-1] += N / 2;
            // seg.update(r-1, r, {1, N/2});
            r--;
        }
        if (r > 0) {
            l = max(r-N/2, 0LL);
            len = r - l;
            b = N/2 - len;
            rep(j, l, r) {
                cost[j] += b;
                b++;
            }
            // seg.update(l, r, {1, N/2-len});
        }
    }
    ll ans = min(cost);
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
