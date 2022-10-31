/*
・なんとか自力AC！
・とりあえずグリッドが小さいので4点全探索できる。
　まず4点とも#じゃなければダメ。で、斜めの正方形をどう判定するか。
　すぐ思いつかなくていったんスキップしたけど、戻ってきて落ち着いて考えて、
　「自分以外の3点との距離」がどの点でも同じで、かつそのうち2つは等しい距離、ってやった。
　必要だとは思ったけど十分かは自信なくて、祈りながらぶん投げて無事AC。
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

void solve() {
    ll H = 9, W = 9;
    vector<string> grid(H);
    cin >> grid;

    auto check = [](array<Point<ll>, 4> P) {
        ll d1 = P[0].abs2(P[1]);
        ll d2 = P[0].abs2(P[2]);
        ll d3 = P[0].abs2(P[3]);
        vector<ll> vec = sorted(vector<ll>{d1, d2, d3});
        if (vec[0] != vec[1] and vec[1] != vec[2]) {
            return false;
        }
        rep(i, 1, 4) {
            ll d1 = P[i].abs2(P[(i+1)%4]);
            ll d2 = P[i].abs2(P[(i+2)%4]);
            ll d3 = P[i].abs2(P[(i+3)%4]);
            if (sorted(vector<ll>{d1, d2, d3}) != vec) {
                return false;
            }
        }
        return true;
    };

    ll N = H * W;
    ll ans = 0;
    rep(a, N) {
        auto [h1, w1] = idtogrid(a, W);
        if (grid[h1][w1] == '.') continue;
        rep(b, a+1, N) {
            auto [h2, w2] = idtogrid(b, W);
            if (grid[h2][w2] == '.') continue;
            rep(c, b+1, N) {
                auto [h3, w3] = idtogrid(c, W);
                if (grid[h3][w3] == '.') continue;
                rep(d, c+1, N) {
                    auto [h4, w4] = idtogrid(d, W);
                    if (grid[h4][w4] == '.') continue;
                    if (check({{{h1, w1}, {h2, w2}, {h3, w3}, {h4, w4}}})) {
                        ans++;
                    }
                }
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
