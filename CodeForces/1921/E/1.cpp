/*
・きっちり自力AC！
・チェス、ゲーム、場合分け
・2人の縦の距離で最後の1手をかける方が変わるので、まずはそれで場合分け。
　勝てる方は自分の守備範囲に相手の範囲が全て収まってれば勝つし、
　少しでもカバーできてない相手の範囲があれば逃げられる。
　これを逆でもやればOK。
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
    ll H, W, ha, wa, hb, wb;
    cin >> H >> W >> ha >> wa >> hb >> wb;

    if (ha >= hb) {
        print("Draw");
        return;
    }
    ll dist = hb - ha;
    if (dist % 2 == 1) {
        // Alice or Draw
        ll amove = ceil(dist, 2LL);
        ll bmove = dist / 2;
        ll la = max(wa - amove, 1LL);
        ll ra = min(wa + amove, W);
        ll lb = max(wb - bmove, 1LL);
        ll rb = min(wb + bmove, W);
        if (la <= lb and rb <= ra) {
            print("Alice");
        } else {
            print("Draw");
        }
    } else {
        // Bob or Draw
        ll bmove = dist / 2;
        ll amove = dist / 2;
        ll lb = max(wb - bmove, 1LL);
        ll rb = min(wb + bmove, W);
        ll la = max(wa - amove, 1LL);
        ll ra = min(wa + amove, W);
        if (lb <= la and ra <= rb) {
            print("Bob");
        } else {
            print("Draw");
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
