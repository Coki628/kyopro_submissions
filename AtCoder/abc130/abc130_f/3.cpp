/*
・2年越しのバグ取り。
　当時誤差かもって書いてたけどオーバーフローだった。。
　特に細かいこと気にせずに雑に境界全部使う感じにしても、
　掛け算の前にldにキャストするだけで普通に通った。
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

    ll x_static_mn = INF, x_static_mx = -INF, y_static_mn = INF,
       y_static_mx = -INF;
    ll x_toleft_mn = INF, x_toleft_mx = -INF, y_todown_mn = INF,
       y_todown_mx = -INF;
    ll x_toright_mn = INF, x_toright_mx = -INF, y_toup_mn = INF,
       y_toup_mx = -INF;
    rep(i, N) {
        ll x, y;
        char d;
        cin >> x >> y >> d;
        x *= 2, y *= 2;

        if (d == 'L') {
            chmin(y_static_mn, y);
            chmax(y_static_mx, y);
            chmin(x_toleft_mn, x);
            chmax(x_toleft_mx, x);
        }
        elif (d == 'R') {
            chmin(y_static_mn, y);
            chmax(y_static_mx, y);
            chmin(x_toright_mn, x);
            chmax(x_toright_mx, x);
        }
        elif (d == 'D') {
            chmin(x_static_mn, x);
            chmax(x_static_mx, x);
            chmin(y_todown_mn, y);
            chmax(y_todown_mx, y);
        }
        else {
            chmin(x_static_mn, x);
            chmax(x_static_mx, x);
            chmin(y_toup_mn, y);
            chmax(y_toup_mx, y);
        }
    }

    auto get_x_mn = [&](ll t) -> ll {
        return min({x_static_mn, x_toleft_mn - t, x_toright_mn + t});
    };
    auto get_x_mx = [&](ll t) -> ll {
        return max({x_static_mx, x_toleft_mx - t, x_toright_mx + t});
    };
    auto get_y_mn = [&](ll t) -> ll {
        return min({y_static_mn, y_todown_mn - t, y_toup_mn + t});
    };
    auto get_y_mx = [&](ll t) -> ll {
        return max({y_static_mx, y_todown_mx - t, y_toup_mx + t});
    };

    vector<ll> T;
    ll t;
    t = bisearch_max(0, INF, [&](ll m) {
        return get_x_mn(m) < get_x_mn(m + 1);
    });
    T.pb(t), T.pb(t + 1);
    t = bisearch_min(0, INF, [&](ll m) {
        return get_x_mn(m - 1) > get_x_mn(m);
    });
    T.pb(t - 1), T.pb(t);
    t = bisearch_max(0, INF, [&](ll m) {
        return get_x_mx(m) > get_x_mx(m + 1);
    });
    T.pb(t), T.pb(t + 1);
    t = bisearch_min(0, INF, [&](ll m) {
        return get_x_mx(m - 1) < get_x_mx(m);
    });
    T.pb(t - 1), T.pb(t);
    t = bisearch_max(0, INF, [&](ll m) {
        return get_y_mn(m) < get_y_mn(m + 1);
    });
    T.pb(t), T.pb(t + 1);
    t = bisearch_min(0, INF, [&](ll m) {
        return get_y_mn(m - 1) > get_y_mn(m);
    });
    T.pb(t - 1), T.pb(t);
    t = bisearch_max(0, INF, [&](ll m) {
        return get_y_mx(m) > get_y_mx(m + 1);
    });
    T.pb(t), T.pb(t + 1);
    t = bisearch_min(0, INF, [&](ll m) {
        return get_y_mx(m - 1) < get_y_mx(m);
    });
    T.pb(t - 1), T.pb(t);

    ld ans = INF;
    for (ll t : T) {
        chmin(
            ans,
            (get_x_mx(t) - get_x_mn(t)) * (ld)(get_y_mx(t) - get_y_mn(t)) / (ld)4
        );
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
