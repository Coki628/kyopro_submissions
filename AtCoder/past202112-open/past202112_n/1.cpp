/*
参考：https://atcoder.jp/contests/past202112-open/editorial/3210
　　　https://ikatakos.com/pot/programming_algorithm/geometry/convex_intersection
・自力は全然無理。
・幾何、凸多角形、共通部分の面積
・公式解説のフレンズさんの方針で。言われてみると確かに、
　交点と互いに内包する点を押さえればそれが全てだねって思う。
・で、求め方。交点は、2直線の交点を求めるやつがライブラリ化してあったので使う。
　内包されている点は、ググったらyaketakeさんのやつが出てきたので参考に。
　ベクトルとか外積うまく使って求める。
　これで必要な頂点は揃ったので、後はちゃんと囲むような順に並べる。
　方法は色々ありそうだけど、今回は凸包ライブラリに突っ込んだ。
　多角形の面積は典型90の41で求めていたのでその方法を使った。
　(線分の外積の和/2で求まるそうだ)
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

#include "geometry/Point.hpp"
#include "geometry/Segment.hpp"
#include "geometry/get_cross_point.hpp"
#include "geometry/cross.hpp"
#include "geometry/monotone_chain.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<Point<ld>> S, T;
    rep(i, N) {
        ld a, b;
        cin >> a >> b;
        S.eb(a, b);
    }
    rep(i, M) {
        ld c, d;
        cin >> c >> d;
        T.eb(c, d);
    }

    vector<Point<ld>> A;
    // 交点
    rep(i, N) {
        Segment<ld> seg1({S[i], S[(i + 1) % N]});
        rep(j, M) {
            Segment<ld> seg2({T[j], T[(j + 1) % M]});
            try {
                auto p = get_cross_point(seg1, seg2);
                A.eb(p);
            } catch (int e) {
            }
        }
    }
    // Tに内包されるSの頂点
    // 参考：https://tjkendev.github.io/procon-library/python/geometry/point_inside_convex_polygon.html
    rep(i, N) {
        auto p1 = S[i];
        ld mn = INF, mx = -INF;
        rep(j, M) {
            auto p2 = T[j];
            auto p3 = T[(j + 1) % M];
            auto v1 = p3 - p2;
            auto v2 = p1 - p2;
            chmin(mn, cross(v1, v2));
            chmax(mx, cross(v1, v2));
        }
        if (mn < 0 and mx <= 0 or mx > 0 and mn >= 0) {
            A.eb(p1);
        }
    }
    // Sに内包されるTの頂点
    rep(i, M) {
        auto p1 = T[i];
        ld mn = INF, mx = -INF;
        rep(j, N) {
            auto p2 = S[j];
            auto p3 = S[(j + 1) % N];
            auto v1 = p3 - p2;
            auto v2 = p1 - p2;
            chmin(mn, cross(v1, v2));
            chmax(mx, cross(v1, v2));
        }
        if (mn < 0 and mx <= 0 or mx > 0 and mn >= 0) {
            A.eb(p1);
        }
    }
    UNIQUE(A);

    if (A.size() < 2) {
        print(0);
        return;
    }
    // 1つの凸包にする
    auto res = monotone_chain(A);
    ll L = res.size();
    // 多角形の面積(線分の外積の和/2で求まる)
    ld ans = 0;
    rep(i, L) {
        ans += cross(res[i].first, res[(i + 1) % L].first);
    }
    ans = abs(ans) / 2;
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
