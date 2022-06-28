/*
参考：https://atcoder.jp/contests/arc003/editorial
　　　https://www.slideshare.net/iwiwi/ss-13293754
・古のARC埋め
・自力ならず。。
・モンテカルロ法、乱択
・これは気付かなかった…。確かによく見ると誤差許容が緩い。
　全スワップ操作を乱択でシミュって成否を集計するのを時間めいっぱいまでぶん回すと通る。
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

#include "common/Timer.hpp"
#include "common/randrange.hpp"

void solve() {
    Timer timer;
    ll N, M, K;
    cin >> N >> M >> K;
    auto mat = list2d(N, N, false);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        mat[a][b] = true;
        mat[b][a] = true;
    }

    ll totalcnt = 0, okcnt = 0;
    auto elapsed = timer.get_elapse();
    const int TL = 9800;
    while (1) {
        elapsed = timer.get_elapse();
        if (elapsed >= TL) break;
        vector<ll> cur(N);
        iota(ALL(cur), 0);
        rep(_, K) {
            ll a = randrange(0, N);
            ll b = a;
            while (b == a) {
                b = randrange(0, N);
            }
            swap(cur[a], cur[b]);
        }
        bool ok = true;
        rep(i, N) {
            if (mat[cur[i]][cur[(i+1)%N]]) {
                ok = false;
                break;
            }
        }
        totalcnt++;
        if (ok) {
            okcnt++;
        }
    }
    ld ans = okcnt / (ld)totalcnt;
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
