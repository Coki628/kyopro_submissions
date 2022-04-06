/*
参考：https://www.nttpc.co.jp/technology/number_algorithm.html
・自力ならず…。相当粘ったけど1WAが取れず。
・幾何、点の多角形に対する内包判定
・点から見て周囲を辿って、1回転するかどうかみたいな判定方法を使ったんだけど、
　多分これでも合ってると思うんだけど、なんかコーナーでやられてる。
　テストケース公開されてないし、落ちるケースが見つけられないので、
　これ以上調べられず断念。制約的に180度ギリギリみたいなのは作れないはずで、
　まじでどういうので落ちてるのか分からない。
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

#include "geometry/get_degree.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<ld>> P(N);
    rep(i, N) {
        cin >> P[i].x >> P[i].y;
    }
    ld sx, sy;
    cin >> sx >> sy;

    ld sm = 0;
    rep(i, N) {
        assert(!(sx == P[i].x and sy == P[i].y));
        // 近い側回りに向かう角度を取得
        sm += get_degree(P[i], {sx, sy}, P[(i+1)%N]);
    }
    if (abs(sm) < EPS) {
        print("OUTSIDE");
    } else {
        print("INSIDE");
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
