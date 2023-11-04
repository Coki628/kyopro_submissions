/*
・自力AC！ちょっと時間かかった。
・幾何、線分の交差判定
・まず曲線Cとかいう難しいこと言ってるけども、
　ようはS,Tをまっすぐ結ぶ線分を考えればよくて、曲げる必要なんてない。
　これに気付くのに大分時間を取られた。
　で、後はこの線分が与えられるN本の直線の式と交わるかどうか判定すればいい。
　直線の式は適当に変形して十分長い線分にする。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "geometry/Point.hpp"
#include "geometry/Segment.hpp"
#include "geometry/intersect.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    ld sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    Point<ld> S(sx, sy), T(tx, ty);
    Segment<ld> ST({S, T});

    vector<Segment<ld>> segs;
    vector<ll> W(N);
    rep(i, N) {
        ld p, q, r;
        cin >> p >> q >> r >> W[i];
        if (p != 0) {
            // 十分長い直線にする
            ld y1 = INF;
            ld x1 = (r - q * y1) / p;
            ld y2 = -INF;
            ld x2 = (r - q * y2) / p;
            segs.pb({{x1, y1}, {x2, y2}});
        } else {
            ld x1 = INF;
            ld y1 = (r - p * x1) / q;
            ld x2 = -INF;
            ld y2 = (r - p * x2) / q;
            segs.pb({{x1, y1}, {x2, y2}});
        }
    }

    vector<ll> vec(N);
    rep(i, N) {
        if (intersect(ST, segs[i])) {
            vec[i] = W[i];
        }
    }
    sort(ALL(vec));
    ll ans = sum(subarray(vec, 0, K));
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
