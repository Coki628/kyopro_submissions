/*
参考：https://github.com/E869120/math-algorithm-book/blob/main/editorial/chap6-21_25/chap6-21_25.pdf
・幾何、点の多角形に対する内包判定
・点から適当に線引いて、交差する辺数の偶奇で判定する方針。
　こっちの方針も試したんだけど、めっちゃWAになったから棄却してた。
　後でよく見たら、しょうもない配列外参照やっちゃってただけ…。
　でもそれ直しても1WAで、結局ACはできなかったと思う。
・ダメなのは、判定する線と平行な辺があると、交差判定が正しくできないため。
　そこで適当にちょっとずらして何本か試して、多数決取る。
　ぴったり平行に当たってしまうことは少ないはずなので、
　何回かやれば正しい結果が多数派になって通せる。(証明AC…)
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

#include "geometry/Segment.hpp"
#include "geometry/intersect.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<ld>> P(N);
    rep(i, N) {
        cin >> P[i].x >> P[i].y;
    }
    ld sx, sy;
    cin >> sx >> sy;

    vector<ld> C(2);
    rep(offset, 0, 7) {
        ld tx = 1e9*2, ty = 1e9*2 + offset;
        Segment<ld> seg1 = {{sx, sy}, {tx, ty}};
        ll cnt = 0;
        rep(i, N) {
            Segment<ld> seg2 = {P[i], P[(i+1)%N]};
            if (intersect(seg1, seg2)) {
                cnt++;
            }
        }
        C[cnt%2]++;
    }
    ll ans = C[1] > C[0];
    if (ans) {
        print("INSIDE");
    } else {
        print("OUTSIDE");
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
