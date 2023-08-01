/*
参考：https://atcoder.jp/contests/past202206-open/editorial/4444
・自力ならず。さすがにボス問はむずいよね。
・クエリ、xy平面、点追加、点削除、三角形の面積
・クエリ先読み、偏角ソート、外積
・x,yの和を使って外積でまとめて計算しようとしたのは悪くなかった。
　偏角ソートが見えなかった…。
・クエリ先読みで角度を取っておいて、角度順で並べてBITの添字と紐付けておく。
　これで各クエリ毎にその時操作する点について、回転方向別にまとめられる。
　左回り側は外積が正、右回り側は負となるので、これらを分けて計算する。
　面積にするためにこれらの正負を適切に調整すると、答えが出る。
・ソートが実数なので誤差が心配だったが、今回は特に工夫しなくても普通に通った。
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
#include "geometry/angle.hpp"
#include "geometry/cross.hpp"

void solve() {
    ll Q;
    cin >> Q;

    Point<ld> base(1, 0), center(0, 0);
    vector<pair<ld, ll>> degs;
    vector<tuple<char, ll, ll>> qs;
    rep(i, Q) {
        char c;
        cin >> c;
        ll x, y;
        cin >> x >> y;
        qs.eb(c, x, y);
        auto deg = angle(base, center, {x, y});
        degs.eb(deg, i);
        degs.eb(deg + 360, i);
    }
    sort(ALL(degs));
    ll M = degs.size() / 2;
    vector<ll> mp(M);
    rep(i, M) {
        mp[degs[i].second] = i;
    }

    BIT<ll> bitx(M * 2), bity(M * 2);
    mint sm = 0;
    rep(i, Q) {
        auto [c, x, y] = qs[i];
        ll j = mp[i];
        auto [deg, _] = degs[j];
        if (c =='+') {
            bitx.add(j, x);
            bitx.add(j + M, x);
            bity.add(j, y);
            bity.add(j + M, y);
        } else if (c == '-') {
            bitx.add(j, -x);
            bitx.add(j + M, -x);
            bity.add(j, -y);
            bity.add(j + M, -y);
        }
        if (deg < 180) {
            j += M;
            deg += 360;
        }
        ll m = j;
        ll l = bisect_left(degs, {deg - 180, 0});
        ll r = bisect_left(degs, {deg + 180, 0});
        // (x,y)から見て右回り側の点の和
        ll smxl = bitx.query(l, m);
        ll smyl = bity.query(l, m);
        // (x,y)から見て左回り側の点の和
        ll smxr = bitx.query(m + 1, r);
        ll smyr = bity.query(m + 1, r);
        // 左回りは外積が正、右回りは負
        ll res = cross<ll>({x, y}, {smxr, smyr}) - cross<ll>({x, y}, {smxl, smyl});
        if (c =='+') {
            sm += res;
        } else if (c == '-') {
            sm -= res;
        }
        print(sm);
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
