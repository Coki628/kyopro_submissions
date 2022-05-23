/*
参考：https://www.slideshare.net/chokudai/code-festival-2015-final
・木、行きがけ順、区間DP
・abc252_gで既出と紹介されていたもの。一応こっちも通しておいた。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    if (A[0] != 0) {
        print(0);
        return;
    }

    // dp[l][r][0] := 区間[l,r]の頂点集合からなる、頂点lを根とする部分木の通り数
    // dp[l][r][1] := 区間[l,r]の頂点集合からなる、一番左の木の根を頂点lとする(木ではない)森の通り数
    auto dp = list3d(N, N, 2, (mint)0);
    auto visited = list2d(N, N, false);
    auto rec = [&](auto&& f, ll l, ll r) -> void {
        if (visited[l][r]) return;
        visited[l][r] = true;
        if (l == r) {
            // 頂点1つの木
            dp[l][r][0] = 1;
            return;
        }
        rep(m, l, r) {
            f(f, l, m); f(f, m+1, r);
            // 頂点lを根とした部分木の隣に木(森)をくっつける
            // →絶対根が2つ以上になるので森に遷移
            if (A[l] < A[m+1]) {
                dp[l][r][1] += dp[l][m][0] * (dp[m+1][r][0] + dp[m+1][r][1]);
            }
        }
        // 頂点lを部分木の根として、その下に木(森)をくっつける
        // →頂点lを根とした1本の木になるので木に遷移
        dp[l][r][0] += dp[l+1][r][0] + dp[l+1][r][1];
    };
    rec(rec, 0, N-1);
    mint ans = dp[0][N-1][0];
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
