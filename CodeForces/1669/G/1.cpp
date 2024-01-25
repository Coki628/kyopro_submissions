/*
・自力AC！
・グリッド、愚直シミュ
・制約がグリッドの2乗は効かないように見えて、線形でやろうとしてもたついた。
　通され過ぎなので愚直シミュに切り替えたら通った…。
　でも終わってからよく考えると、内側のループは行数にしか係らないはずで、
　(H*W)^2じゃなくてH^2*Wっぽいね、それなら確かに通りそう。
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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    auto ans = grid;
    rep(w, W) {
        rep(h, H - 1, -1, -1) {
            if (ans[h][w] == '*') {
                ll nh = h + 1;
                while (nh < H and ans[nh][w] == '.') {
                    swap(ans[nh - 1][w], ans[nh][w]);
                    nh++;
                }
            }
        }
    }
    print(ans, "\n");
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
