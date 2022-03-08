/*
・dojo set_e_4_6
・きっちり自力AC！
・場合分けして二分探索
・次元が同じ側2パターンと違う側4パターンで分けて処理する。
　同じ側はx,y座標の片側が一致してるのをチェック、
　違う側は斜めの位置みたいのが一致してるとぶつかるので、
　x+y,x-yが一致してる同士でそれぞれチェックする。
　実際にぶつかるかどうかはにぶたんで一番近い場所見つける。
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
    const ll M = 200000;
    vvl uadj(M+1), dadj(M+1), ladj(M+1), radj(M+1);
    map<ll, vector<ll>> urmp, ulmp, drmp, dlmp;
    vector<pll> xyl, xyr;
    rep(i, N) {
        ll x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'U') {
            uadj[x].eb(y);
            urmp[x+y].eb(x);
            ulmp[x-y].eb(x);
        } elif (c == 'D') {
            dadj[x].eb(y);
            drmp[x-y].eb(x);
            dlmp[x+y].eb(x);
        } elif (c == 'L') {
            ladj[y].eb(x);
            xyl.eb(x, y);
        } else {
            radj[y].eb(x);
            xyr.eb(x, y);
        }
    }
    rep(i, M+1) {
        sort(ALL(uadj[i]));
        sort(ALL(dadj[i]));
        sort(ALL(ladj[i]));
        sort(ALL(radj[i]));
    }
    for (auto& [k, v] : urmp) {
        sort(ALL(v));
    }
    for (auto& [k, v] : ulmp) {
        sort(ALL(v));
    }
    for (auto& [k, v] : drmp) {
        sort(ALL(v));
    }
    for (auto& [k, v] : dlmp) {
        sort(ALL(v));
    }

    ll ans = INF;
    rep(i, M+1) {
        // U - D
        for (ll y1 : uadj[i]) {
            ll j = bisect_left(dadj[i], y1);
            if (j < dadj[i].size()) {
                ll y2 = dadj[i][j];
                chmin(ans, y2-y1);
            }
        }
        // R - L
        for (ll x1 : radj[i]) {
            ll j = bisect_left(ladj[i], x1);
            if (j < ladj[i].size()) {
                ll x2 = ladj[i][j];
                chmin(ans, x2-x1);
            }
        }
    }
    for (auto [x1, y1] : xyr) {
        // R - U
        ll i = bisect_left(urmp[x1+y1], x1);
        if (i < urmp[x1+y1].size()) {
            ll x2 = urmp[x1+y1][i];
            chmin(ans, (x2-x1)*2);
        }
        // R - D
        i = bisect_left(drmp[x1-y1], x1);
        if (i < drmp[x1-y1].size()) {
            ll x2 = drmp[x1-y1][i];
            chmin(ans, (x2-x1)*2);
        }
    }
    for (auto [x1, y1] : xyl) {
        // L - U
        ll i = bisect_right(ulmp[x1-y1], x1)-1;
        if (i >= 0) {
            ll x2 = ulmp[x1-y1][i];
            chmin(ans, (x1-x2)*2);
        }
        // L - D
        i = bisect_right(dlmp[x1+y1], x1)-1;
        if (i >= 0) {
            ll x2 = dlmp[x1+y1][i];
            chmin(ans, (x1-x2)*2);
        }
    }
    ans = ans*10/2;
    if (ans < INF) {
        print(ans);
    } else {
        print("SAFE");
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
