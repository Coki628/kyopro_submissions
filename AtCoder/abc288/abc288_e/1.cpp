/*
参考：https://hackmd.io/@carrot46/BkwfZUZTj
・本番もむずいと思ったけどupsolveでもむずい。
・状態の決め方がむずいDP、sparse tableで高速化
・Cを使える範囲について検討してみる。
　すると、元位置でjならば、jより後ろにはできないことが分かる。
　で、よく考察すると、買う順序をうまく前後させればこのjが前に動かせると分かる。
　どこまで前に動かせるかさらに検討すると、売れ残った商品より前にはできないとなる。
　ここから状態として売れ残った商品、つまり「買わないと決めた商品の数」を
　状態に持つと、遷移で取りうるCの範囲が区間になり、
　セグ木などで最小値取得を高速化しておけば、2乗のDPに落とし込める。
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

#include "datastructure/SparseTable.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), C(N), X(M);
    cin >> A >> C >> X;
    X--;

    vector<ll> need(N);
    rep(i, M) {
        need[X[i]] = 1;
    }
    auto st = get_sparse_table(C, [](ll a, ll b) { return min(a, b); }, INF);

    // dp[i][j] := i番目まで見て、買わないと決めた商品がj個ある時の最大値
    auto dp = listnd(N + 1, N + 1, INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, i + 1) {
            if (not need[i]) {
                chmin(dp[i + 1][j + 1], dp[i][j]);
            }
            // rep(k, j, i + 1) {
            //     chmin(dp[i + 1][j], dp[i][j] + A[i] + C[k]);
            // }
            chmin(dp[i + 1][j], dp[i][j] + A[i] + st.query(j, i + 1));
        }
    }
    ll ans = min(dp[N]);
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
