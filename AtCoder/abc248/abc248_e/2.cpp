/*
・自力ならず…。
・幾何、誤差対策、有理数
・直線y=ax+bを被りなく集めて、線上にある点の数を数える、
　ができればいいんだけど、これがまあ大変で…。
・最適化なら被りは適当でいいんだけど、数え上げなのでちゃんとやる必要がある。
　a,bの値は普通にやると実数になってしまうので、分数クラスを使う。とした。
・WAが取れなかったのはK=1の別処理をN=1でいいと思い込んでしまったミスで、
　これはまあ論外なんだけど、気付けなかったのでしょうがない。
・TLEなのは分数クラスFractionが結構重いから？と思って、
　終了後ゆっくりC++の分数クラスを自作してみることにした。
　そのうちやろうと思って、やってなかったやつの1つだしね…。
・さて、C++のFracionを作ってみたものの、それでもTLEする。
　300^3ってそんなに重いか？全ペアで半分になってるから/2あるし…。
　って思ったんだけど、よくよく検討すると、300^3/2は1350万もあってまあ大きくて、
　これに分数を演算するためにgcdのlogが乗ってるはずなので、それはまあ無理かぁとなった。
・ちなみにWAも出てて、llをint128にしたらそれは消えた。
　10^9まであるから、a,bを求める時と、y=ax+bの一致をチェックする時で、
　計2回掛け算やるとすると、場合によっては10^18はオーバーフローするんかなと思った。
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

#include "common/int128.hpp"
#include "geometry/Point.hpp"
#include "geometry/get_a_and_b.hpp"
#include "numbers/Fraction.hpp"
using fraction = Fraction<int128>;

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

    set<pair<fraction, fraction>> AB;
    map<fraction, ll> zeros;
    rep(i, N) {
        // a == INFな直線は別処理
        zeros[XY[i].x]++;
        rep(j, i+1, N) {
            if (XY[i].x == XY[j].x) {
                continue;
            }
            AB.insert(get_a_and_b(XY[i], XY[j]));
        }
    }

    ll ans = 0;
    for (auto [a, b] : AB) {
        ll cnt = 0;
        rep(i, N) {
            ll rest = N - i;
            ll need = K - cnt;
            if (rest < need) break;
            if (XY[i].y == a*XY[i].x + b) {
                cnt++;
                if (cnt >= K) {
                    ans++;
                    break;
                }
            }
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
