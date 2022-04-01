/*
・きっちり自力AC！
・0は全てを破壊するので、そこで予め区間を分けた。心配事を1つ減らす。
　で0がない区間で、マイナスが偶数個あれば全部使えばいいし、
　奇数個だったら最後のマイナスの手前までか最初のマイナスの次からを使う。短めにする得はない。
　区間を分解してたから、元indexの回収がちょい面倒だったりした。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vvpll adj;
    vector<pll> cur;
    rep(i, N) {
        if (A[i] == 0) {
            if (cur.size()) {
                adj.eb(cur);
                cur.clear();
            }
        } else {
            cur.eb(A[i], i);
        }
    }
    if (cur.size()) adj.eb(cur);

    ll mx = 0;
    pll ans = {N, 0};
    for (auto& li : adj) {
        ll n = li.size();
        ll minus = 0;
        ll l = -1, r = -1;
        rep(i, n) {
            if (li[i].first < 0) {
                minus++;
                if (l == -1) {
                    l = i;
                }
            }
        }
        rep(i, n-1, -1, -1) {
            if (li[i].first < 0) {
                if (r == -1) {
                    r = i;
                }
            }
        }
        if (minus%2 == 0) {
            ll cnt2 = 0;
            // 全区間OK
            rep(i, n) {
                if (abs(li[i].first) == 2) {
                    cnt2++;
                }
            }
            if (cnt2 > mx) {
                mx = cnt2;
                ll j = li[0].second;
                ll k = li[n-1].second;
                ans = {j, N-(k+1)};
            }
        } else {
            ll cntl2 = 0;
            // 最後のマイナスの手前まで
            rep(i, r) {
                if (abs(li[i].first) == 2) {
                    cntl2++;
                }
            }
            if (cntl2 > mx) {
                mx = cntl2;
                ll j = li[0].second;
                ll k = li[r-1].second;
                ans = {j, N-(k+1)};
            }
            // 最初のマイナスの次から
            ll cntr2 = 0;
            rep(i, l+1, n) {
                if (abs(li[i].first) == 2) {
                    cntr2++;
                }
            }
            if (cntr2 > mx) {
                mx = cntr2;
                ll j = li[l+1].second;
                ll k = li[n-1].second;
                ans = {j, N-(k+1)};
            }
        }
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
