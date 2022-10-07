/*
・なんとか自力AC。。
・こういうの疲れる。そのままソートして合えば即OK、それ以外はxかy単体でソートして、
　合えばそっちの軸でソートした時の逆側の軸でs,t真ん中の位置がN個全部一致してればOK、
　この時ソートした側が同値だったら逆側は逆から舐めたいので、正負いじったりしてソートの第2キーを調整する。
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
    vector<ll> sx(N), sy(N), tx(N), ty(N);
    vector<pll> sxy, txy;
    rep(i, N) {
        cin >> sx[i] >> sy[i];
        sxy.eb(sx[i], sy[i]);
    }
    rep(i, N) {
        cin >> tx[i] >> ty[i];
        txy.eb(tx[i], ty[i]);
    }

    if (sorted(sxy) == sorted(txy)) {
        Yes();
        return;
    }

    if (sorted(sx) == sorted(tx)) {
        vector<pll> sxy, txy;
        rep(i, N) {
            sxy.eb(sx[i], sy[i]);
            txy.eb(tx[i], -ty[i]);
        }
        sort(ALL(sxy));
        sort(ALL(txy));
        set<ld> se;
        rep(i, N) {
            se.insert((sxy[i].second-txy[i].second) / (ld)2);
        }
        if (se.size() == 1) {
            Yes();
        } else {
            No();
        }
    } elif (sorted(sy) == sorted(ty)) {
        vector<pll> syx, tyx;
        rep(i, N) {
            syx.eb(sy[i], sx[i]);
            tyx.eb(ty[i], -tx[i]);
        }
        sort(ALL(syx));
        sort(ALL(tyx));
        set<ld> se;
        rep(i, N) {
            se.insert((syx[i].second-tyx[i].second) / (ld)2);
        }
        if (se.size() == 1) {
            Yes();
        } else {
            No();
        }
    } else {
        No();
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
