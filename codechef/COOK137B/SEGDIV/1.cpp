/*
・自力AC！
・2乗が効くので愚直に手前と全ペア組ませて試す。
　全部OKならそれを追加。偶奇交互のがうまくいきそうだったから、一応偶奇で分けてやった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    vector<ll> ans = {3};
    if (N >= 2) ans.eb(2);
    rep(i, 2, N) {
        if (i%2 == 0) {
            ll a = 5;
            while (1) {
                bool ok = true;
                ll sm = a;
                rep(j, ans.size()-1, -1, -1) {
                    sm += ans[j];
                    ll len = i-j+1;
                    if (sm%len == 0) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    ans.eb(a);
                    break;
                }
                a += 2;
            }
        } else {
            ll a = 4;
            while (1) {
                bool ok = true;
                ll sm = a;
                rep(j, ans.size()-1, -1, -1) {
                    sm += ans[j];
                    ll len = i-j+1;
                    if (sm%len == 0) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    ans.eb(a);
                    break;
                }
                a += 2;
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
