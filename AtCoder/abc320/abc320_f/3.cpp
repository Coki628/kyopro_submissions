/*
・これはTLE。
　配列使い回しでメモリ節約するやつ。区間chminだからリセットがちょっと面倒だった。
　色々頑張ったけど惜しい所にも行かず。
　分かったのは、300^3=2700万に遅延セグ木のlogはまあ無理があるってことだった。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

#include "datastructure/LazySegmentTree.hpp"

// 区間chmin・区間最小値取得
auto f = [](int a, int b) -> int { return min(a, b); };
auto g = [](int a, int b) -> int { return min(a, b); };
auto h = [](int a, int b) -> int { return min(a, b); };
const int T = MOD;
const int E = MOD;

void solve() {
    int N, H;
    cin >> N >> H;
    vector<int> X(N);
    cin >> X;
    vector<int> P(N), F(N);
    rep(i, 1, N) {
        cin >> P[i] >> F[i];
    }
    X.insert(X.begin(), 0);
    P.eb(0);
    F.eb(0);

    auto dp = listnd(2, H + 1, get_lazy_segment_tree(H + 1, f, g, h, T, E));
    dp[0][H].update(0, H + 1, 0);
    rep(i, N) {
        int dist = X[i + 1] - X[i];
        rep(h1, H + 1) {
            if (dp[i % 2][h1].query(0, H + 1) >= MOD) continue;
            rep(h2, H + 1) {
                if (dp[i % 2][h1][h2] >= MOD) continue;
                // 給油しない
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    dp[(i + 1) % 2][h1 - dist].update(h2 + dist, dp[i % 2][h1][h2]);
                }
                // 行きに給油する
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    dp[(i + 1) % 2][min((int)h1 - dist + F[i + 1], H)].update(h2 + dist, dp[i % 2][h1][h2] + P[i + 1]);
                }
                // 帰りに給油する
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    int l = max((int)h2 + dist - F[i + 1], 0);
                    int r = h2 + dist;
                    dp[(i + 1) % 2][h1 - dist].update(l, r, dp[i % 2][h1][h2] + P[i + 1]);
                }
            }
            dp[i % 2][h1].data.assign(dp[i % 2][h1].sz * 2, MOD);
            dp[i % 2][h1].lazy.assign(dp[i % 2][h1].sz * 2, MOD);
        }
    }
    int ans = MOD;
    rep(h1, H + 1) {
        chmin(ans, dp[N % 2][h1].query(0, h1 + 1));
    }
    if (ans >= MOD) ans = -1;
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
