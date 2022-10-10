/*
・なんとか自力AC！
・式変形、BFS
　abs(x)^2+abs(y)^2 = M を式変形して、
　abs(x)^2 = M-abs(y)^2 みたいにすると、dxを全探索してdyを一意にできるので、
　これをxy両方でやると、グリッドN*Nで遷移のループがNなのでN^3で間に合う。
　なんだけどTLかなり厳しかった。isqrtのlogが乗るのがきつくて、
　精度犠牲は覚悟して純正の実数sqrt使ったら何とか間に合ってAC1.64秒。
　誰か(多分hamamuさん)がにぶたんベースのisqrtより
　C++純正sqrtが速いみたいなツイートをしていたのを思い出せて良かった。
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
    ll N, M;
    cin >> N >> M;

    vector<pii> src = {{0, 0}};
    auto res = list2d(N, N, -1);
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        res[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        rep(dh, -N, N) {
            ll dw2 = M - dh*dh;
            ll dw = sqrt(dw2);
            if (dw*dw != dw2) continue;
            for (auto a : {-1, 1}) {
                ll nh = h + dh;
                ll nw = w + dw*a;
                if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
                if (res[nh][nw] == -1) {
                    res[nh][nw] = res[h][w] + 1;
                    que.push({nh, nw});
                }
            }
        }
        rep(dw, -N, N) {
            ll dh2 = M - dw*dw;
            ll dh = sqrt(dh2);
            if (dh*dh != dh2) continue;
            for (auto a : {-1, 1}) {
                ll nh = h + dh*a;
                ll nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
                if (res[nh][nw] == -1) {
                    res[nh][nw] = res[h][w] + 1;
                    que.push({nh, nw});
                }
            }
        }
    }
    print(res, '\n');
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
