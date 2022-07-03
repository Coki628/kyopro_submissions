/*
参考：https://www.youtube.com/watch?v=nAnN5fBjEqA&list=PLLeJZg4opYKZMA68O5LKWyNEJEulInKAi&index=3
・ABC高難度埋め
・45度回転、疎な2次元BIT、二分探索
・やってみたけど、ただmapにするだけじゃやっぱダメなのね…。
　座圧パートなくしてみたけど、変わらず。。
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

#include "segment/SparseBIT2D.hpp"

void solve() {
    int N;
    cin >> N;
    vector<int> U, V;
    int offset = 100000;
    rep(i, N) {
        int x, y;
        cin >> x >> y;
        int u = x - y + offset;
        int v = x + y;
        U.eb(u);
        V.eb(v);
    }

    int MX = 200007;
    SparseBIT2D<int> bit(MX, MX);
    rep(i, N) {
        bit.add(U[i], V[i], 1);
    }

    int Q;
    cin >> Q;
    rep(i, Q) {
        int x, y, k;
        cin >> x >> y >> k;
        int u = x - y + offset;
        int v = x + y;
        int res = bisearch_min(-1, MX, [&](int m) {
            // (u,v)を中心とした1辺が2mの正方形領域の中にある点の個数
            int lu = max(u - m, 0);
            int ru = min(u + m + 1, MX);
            int lv = max(v - m, 0);
            int rv = min(v + m + 1, MX);
            int cnt = bit.query(lu, lv, ru, rv);
            return cnt >= k;
        });
        print(res);
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
