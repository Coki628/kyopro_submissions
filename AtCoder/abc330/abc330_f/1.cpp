/*
・自力ならず。悔しい。
・XY独立、決め打ちにぶたん、三分探索
・XY独立で、長lenに収めるためのコストはK以下か？でにぶたんする形は考えてた。
　けどそのlenを置く位置が、最初に考えた中央値のイメージから抜け出せなくて、
　最適な場所見つけ出せなくない？となっている間に終了してしまった。
　TL見た限り、見つけ出す方法は色々あるっぽくて、尺取りっぽく動かす、
　三分探索する、slope trickを使う、などがある模様。
　とりあえず一番考察が浅くても作れた三分探索で通した。
　20万ににぶたんとさぶたんのlog2つでも、結構普通に通るんだねー。
　外側のにぶたんの上限を雑にINFでも1.75秒、X,Yの最大値にしたら0.96秒だった。(制約3秒)
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

#include "common/trisearch.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }

    sort(ALL(X));
    sort(ALL(Y));
    ll res = bisearch_min(-1, max(X.back(), Y.back()), [&](ll len) {
        auto [xid, xval] = trisearch_min(X[0], X.back() + 1, [&](ll xl) {
            ll xr = xl + len;
            ll cnt = 0;
            for (auto x : X) {
                if (x < xl) {
                    cnt += abs(x - xl);
                } else if (x > xr) {
                    cnt += abs(x - xr);
                }
            }
            return cnt;
        }, 3);
        auto [yid, yval] = trisearch_min(Y[0], Y.back() + 1, [&](ll yl) {
            ll yr = yl + len;
            ll cnt = 0;
            for (auto y : Y) {
                if (y < yl) {
                    cnt += abs(y - yl);
                } else if (y > yr) {
                    cnt += abs(y - yr);
                }
            }
            return cnt;
        }, 3);
        return xval + yval <= K;
    });
    print(res);
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
