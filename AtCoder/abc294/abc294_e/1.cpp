/*
・自力AC！
・両方の情報を合わせて座圧。
　やることは分かるけどまあまあ実装だるいので、
　これが茶パフォはまじかぁー、ってなる。
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
    ll L, N1, N2;
    cin >> L >> N1 >> N2;
    vector<pll> A1, A2;
    Compress<ll> cp;
    ll cur = 0;
    cp.add(cur);
    rep(i, N1) {
        ll val, len;
        cin >> val >> len;
        cur += len;
        A1.eb(val, cur);
        cp.add(cur);
    }
    cur = 0;
    rep(i, N2) {
        ll val, len;
        cin >> val >> len;
        cur += len;
        A2.eb(val, cur);
        cp.add(cur);
    }
    cp.build();
    ll M = cp.size();
    auto B = listnd(2, M, 0LL);
    ll i = 0;
    for (auto [val, cur] : A1) {
        while (cp.unzip(i) < cur) {
            B[0][i] = val;
            i++;
        }
    }
    i = 0;
    for (auto [val, cur] : A2) {
        while (cp.unzip(i) < cur) {
            B[1][i] = val;
            i++;
        }
    }
    ll ans = 0;
    rep(i, M - 1) {
        if (B[0][i] == B[1][i]) {
            ans += cp.unzip(i + 1) - cp.unzip(i);
        }
    }
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
