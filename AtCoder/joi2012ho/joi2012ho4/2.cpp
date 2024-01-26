/*
・類題復習
・三角形の2次元いもす
・こどふぉで三角形の2次元累積和をやったので、これ復習してみた。
　累積和の時と同じようなアプローチ(長方形領域を分けて対応)はできなくて、
　結局これはこれで類題というか別物として解く感じになった。
・点打つ位置、自力で導出できるかと思ったら無理だった…。
　結局公式解説熟読しながらになった。どうすれば自力で導けるのか考えた。
　必要な領域に全部1を打って、そこから逆算してどうすればいいか考える、
　みたいなのがいくらかうまくいきそうだった。(自分ノート参照)
・あとこれ、累積の順番って変えても結果同じになるのね、なんか非自明だったけど。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve() {
    ll N, M;
    cin >> N >> M;
    auto imos = listnd(N + 2, N + 2, 0);
    rep(i, M) {
        ll h, w, x;
        cin >> h >> w >> x;
        w--, h--, x++;
        imos[h][w]++;
        imos[h][w + 1]--;
        imos[h + x][w]--;
        imos[h + x + 1][w + 1]++;
        imos[h + x][w + x + 1]++;
        imos[h + x + 1][w + x + 1]--;
    }

    rep(h, N + 1) {
        rep(w, N + 2) {
            imos[h + 1][w] += imos[h][w];
        }
    }
    rep(h, N + 2) {
        rep(w, N + 1) {
            imos[h][w + 1] += imos[h][w];
        }
    }
    rep(h, N + 1) {
        rep(w, N + 1) {
            imos[h + 1][w + 1] += imos[h][w];
        }
    }

    ll ans = 0;
    rep(h, N) {
        rep(w, h + 1) {
            assert(imos[h][w] >= 0);
            if (imos[h][w] > 0) {
                ans++;
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
