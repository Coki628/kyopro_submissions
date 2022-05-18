/*
・なんとか自力AC！
・まともに区切り位置を全部試すことはできない。どうするか考える。
　まず最初の1つを決めると、他は全てそれに合わせないといけないので、
　例えば左上を含む部分を適当に区切れば、そこが基準になる。
　で、他の場所もその数ぴったりになるように切る。具体的には、
　最初に切った部分と縦横のどちらかが同じ位置で進めて行く。
　この部分は逆側にそれ以上切れないので、ここで一意にできる。
　反対側も同じようにやる。すると縦横両方に多数の切れ目が入った状態になって、
　これ以上切れない。この状態で、他の残った部分もOKかチェックする。
　残り部分のOK判定には、部分点で使ったパートがほぼ流用できた。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "segment/Accumulate2D.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = list2d(H, W, 0LL);
    rep(i, H) {
        rep(j, W) {
            cin >> grid[i][j];
        }
    }

    auto check = [&](ll bit1, ll bit2) -> bool {
        if (bit1 == 0 and bit2 == 0) return false;
        ll n = popcount(bit1)+1;
        ll m = popcount(bit2)+1;
        auto C = list2d(n, m, 0);
        ll i = 0;
        rep(h, H) {
            ll j = 0;
            rep(w, W) {
                C[i][j] += grid[h][w];
                if (bit2>>w & 1) {
                    j++;
                }
            }
            if (bit1>>h & 1) {
                i++;
            }
        }
        vector<ll> V;
        rep(i, n) {
            rep(j, m) {
                V.eb(C[i][j]);
            }
        }
        UNIQUE(V);
        return V.size() == 1;
    };

    Accumulate2D<ll> acc(grid);
    ll ans = 0;
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            ll bit1 = i < H ? 1LL<<(i-1) : 0;
            ll bit2 = j < W ? 1LL<<(j-1) : 0;
            bool ok = true;
            ll x = acc.query(0, 0, i, j);
            ll cur = 0, l = i;
            rep(r, i, H+1) {
                cur = acc.query(l, 0, r, j);
                if (cur == x) {
                    if (r < H) bit1 |= 1LL<<(r-1);
                    l = r;
                } elif (cur > x) {
                    ok = false;
                    break;
                }
            }
            if (l < H) {
                if (acc.query(l, 0, H, j) < x) {
                    ok = false;
                }
            }
            if (not ok) continue;
            cur = 0;
            l = j;
            rep(r, j, W+1) {
                cur = acc.query(0, l, i, r);
                if (cur == x) {
                    if (r < W) bit2 |= 1LL<<(r-1);
                    l = r;
                } elif (cur > x) {
                    ok = false;
                    break;
                }
            }
            if (l < W) {
                if (acc.query(0, l, i, W) < x) {
                    ok = false;
                }
            }
            if (ok and check(bit1, bit2)) {
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
