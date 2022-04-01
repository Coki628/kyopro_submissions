/*
・なんとか自力AC。大変だった…。
・線形計画問題、幾何、2直線の交点
・N本の直線の式を考えると、交点しか最大値はなさそう、となる。
　全交点見て、それぞれ自分より下を通る直線がないかチェックして、OKなら最大値候補とする。
・x,yの最大値が正とは言ってるけど、直線がy = -xのものしかないみたいなケースはあるかもしれないので、
　交点ではない部分でも各直線1回ずつはチェックしてる。
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

#include "geometry/get_cross_point.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ld> A(N), B(N);
    rep(i, N) {
        ld p, q, r;
        cin >> p >> q >> r;
        // y = ax + b;
        A[i] = -p / q;
        B[i] = r / q;
    }

    // x,y最大は正って言ってるので、どこまでも行くやつはないはず
    assert(!(N == 1 and A[0] != -1));

    auto check = [&](int i, int j, Point<ld> p) -> bool {
        rep(k, N) {
            if (k == i or k == j) continue;
            // この交点のyより下に線があれば使えない
            ld y = A[k]*p.x + B[k];
            if (y < p.y-EPS) {
                return false;
            }
        }
        return true;
    };

    ld ans = -INF;
    rep(i, N) {
        // x,y最大は正って言ってるのでとりあえず第一象限めいっぱい
        // y = ax + b
        ld x1 = 0;
        ld y1 = A[i]*x1 + B[i];
        // x = (y-b) / a
        ld y2 = 0;
        ld x2 = (y2-B[i]) / A[i];
        // 一応交点じゃない所も1回チェックしておく
        if (check(i, i, {x1, y1})) {
            chmax(ans, x1+y1);
        }
        rep(j, i+1, N) {
            if (i == j) continue;
            ld x3 = 0;
            ld y3 = A[j]*x3 + B[j];
            ld y4 = 0;
            ld x4 = (y4-B[j]) / A[j];
            try {
                // 2直線の交点を取得
                auto p = get_cross_point<ld>({{x1, y1}, {x2, y2}}, {{x3, y3}, {x4, y4}});
                if (check(i, j, p)) {
                    chmax(ans, p.x+p.y);
                }
            } catch (int e) {
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
