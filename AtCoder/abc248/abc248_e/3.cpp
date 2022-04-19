/*
参考：https://blog.hamayanhamayan.com/entry/2022/04/16/232237
・これははまやんさんの方針を参考に。
・幾何、誤差対策、有理数、二項係数
・さて、自力実装のやつはTLEするので、N^3を落としてN^2でやりきるようにする。
　点ペアで作った直線を、直線毎に出現数を集計しておくと、
　そういうペアが何回出たかが分かる。
　これはnC2の解なので、nC2(i)となるiが何だったのかを前計算しておけば、
　ペア数から点の数を逆算できる。
　これで直線毎の点の数は実際にN個チェックしなくても求まる。
・ちなみに2乗の方針にしたらllでもWAにならなくなったので、int128から戻しておいた。
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

#include "geometry/Point.hpp"
#include "geometry/get_a_and_b.hpp"
#include "numbers/Fraction.hpp"
using fraction = Fraction<ll>;

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<Point<fraction>> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.pb({x, y});
    }

    if (K == 1) {
        print("Infinity");
        return;
    }

    map<pair<fraction, fraction>, ll> AB;
    map<fraction, ll> zeros;
    rep(i, N) {
        // a == INFな直線は別処理
        zeros[XY[i].x]++;
        rep(j, i+1, N) {
            if (XY[i].x == XY[j].x) {
                continue;
            }
            AB[get_a_and_b(XY[i], XY[j])]++;
        }
    }

    map<ll, ll> nC2ton;
    rep(i, 2, N+1) {
        nC2ton[nC2(i)] = i;
    }
    ll ans = 0;
    for (auto [k, v] : AB) {
        // 二項係数からペア数→要素数を逆算する
        ll cnt = nC2ton[v];
        if (cnt >= K) {
            ans++;
        }
    }
    for (auto [y, cnt] : zeros) {
        if (cnt >= K) {
            ans++;
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
