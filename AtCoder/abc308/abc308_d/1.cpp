/*
・自力AC！
・mod 5の状態持ってグリッドBFS。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;
    string S = "snuke";
    ll N = S.size();

    vector<array<ll, 3>> src = {{0, 0, 0}};
    auto res = listnd(N, H, W, INF);
    queue<array<ll, 3>> que;
    for (auto [i, h, w] : src) {
        if (grid[h][w] == S[i]) {
            res[i][h][w] = 0;
            que.push({i, h, w});
        }
    }
    while (!que.empty()) {
        auto [i, h, w] = que.front();
        que.pop();
        for (auto [dh, dw] : dir4) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            ll j = (i + 1) % N;
            if (grid[nh][nw] != S[j]) continue;
            if (res[j][nh][nw] == INF) {
                res[j][nh][nw] = res[i][h][w] + 1;
                que.push({j, nh, nw});
            }
        }
    }
    ll ok = 0;
    rep(i, N) {
        if (res[i][H - 1][W - 1] < INF) {
            ok = 1;
            break;
        }
    }
    if (ok) {
        Yes();
    } else {
        No();
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
