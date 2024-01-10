/*
・きっちり自力AC！
・内包する区間
・片側をソート、反対を座圧BITで平面走査っぽくやる。
　本質はpast202212_lからほぼ持ってきた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<pll> LR;
    Compress<ll> cp;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        LR.eb(-l, r);
        cp.add(r);
    }
    cp.build();
    ll M = cp.size();
    BIT<ll> bit(M);
    // 左端で降順ソート
    sort(ALL(LR));
    ll ans = 0;
    rep(i, N) {
        auto [l, r] = LR[i];
        ll cpr = cp[r];
        ans += bit.query(0, cpr);
        bit.add(cpr, 1);
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
