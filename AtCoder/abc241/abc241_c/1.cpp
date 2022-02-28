/*
・きっちり自力AC！
・グリッド、実装
・実装。6*6の全箇所を縦横斜めチェックした。
　これだと縦横は何回も同じ所チェックすることになるけど、
　それは別に問題にはならないし、斜めが楽にできる。
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
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    auto check = [&](ll lh, ll lw) {
        ll rh = lh+6;
        ll rw = lw+6;
        // 横
        rep(ch, lh, rh) {
            ll cnt = 0;
            rep(cw, lw, rw) {
                if (grid[ch][cw] == '#') {
                    cnt++;
                }
            }
            if (cnt >= 4) {
                return true;
            }
        }
        // 縦
        rep(cw, lw, rw) {
            ll cnt = 0;
            rep(ch, lh, rh) {
                if (grid[ch][cw] == '#') {
                    cnt++;
                }
            }
            if (cnt >= 4) {
                return true;
            }
        }
        // 斜め
        ll cnt = 0;
        rep(d, 6) {
            if (grid[lh+d][lw+d] == '#') {
                cnt++;
            }
        }
        if (cnt >= 4) {
            return true;
        }
        cnt = 0;
        rep(d, 6) {
            if (grid[lh+d][rw-d-1] == '#') {
                cnt++;
            }
        }
        if (cnt >= 4) {
            return true;
        }
        return false;
    };

    rep(h, N-5) {
        rep(w, N-5) {
            if (check(h, w)) {
                Yes();
                return;
            }
        }
    }
    No();
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
