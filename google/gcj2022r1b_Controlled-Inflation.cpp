/*
・きっちり自力AC！
・その行を処理し終わった時には両端のどちらかにいるとしていいはず。このことから、
　dp[i][j] := i行目まで終わって、j=左端/右端にいる時の最小値
　みたいなDPを作れる。その行の区間長分は必ずかかるので予め足しておく。
　(DPしながら足しても大丈夫だろうけど。)
　この片道全部見る動作はどっちにしてもかかるので、遷移時の移動コストは、
　状態として行き着く方とは逆側までのコストになる。
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
    ll N, P;
    cin >> N >> P;
    vvl A(N);
    ll ans = 0;
    rep(i, N) {
        A[i] = LIST(P);
        sort(ALL(A[i]));
        ans += A[i][P-1] - A[i][0];
    }

    auto dp = list2d(N, 2, INF);
    dp[0][0] = A[0][P-1];
    dp[0][1] = A[0][0];
    rep(i, N-1) {
        chmin(dp[i+1][0], dp[i][0] + abs(A[i][0]-A[i+1][P-1]));
        chmin(dp[i+1][1], dp[i][0] + abs(A[i][0]-A[i+1][0]));
        chmin(dp[i+1][0], dp[i][1] + abs(A[i][P-1]-A[i+1][P-1]));
        chmin(dp[i+1][1], dp[i][1] + abs(A[i][P-1]-A[i+1][0]));
    }
    ans += min(dp[N-1]);
    print(ans);
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
    rep(i, 1, T+1) {
        cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
