/*
・自力AC。ちょいもたついて良くなかった。
・イチゴがある周囲の9マスだけチェックすればいい。
　正確には9マスを軸にしてさらに周囲9マス見るのでもうちょい広いけどまあ問題ない。
　同じ座標にもあるとのことなので、座標がキーのmapで個数持っておく。
・普通のmapで0.7秒かかっていたのがHashMapで0.16秒になった。
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

#include "common/HashMap.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    ll N;
    cin >> N;
    vector<pll> HW;
    HashMap<pll, ll> C;
    rep(i, N) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        HW.pb({a, b});
        C[HW[i]]++;
    }

    ll ans = 0;
    for (auto [h, w] : HW) {
        rep(ch, max(h-1, 0LL), min(h+2, H)) {
            rep(cw, max(w-1, 0LL), min(w+2, W)) {
                ll cnt = 0;
                rep(nh, max(ch-1, 0LL), min(ch+2, H)) {
                    rep(nw, max(cw-1, 0LL), min(cw+2, W)) {
                        if (C.count({nh, nw})) {
                            cnt += C[{nh, nw}];
                        }
                    }
                }
                chmax(ans, cnt);
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
