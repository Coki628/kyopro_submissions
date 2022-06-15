/*
・きっちり自力AC！
・セグ木、inplace DP
・ようは毎回、直前に同じ種類を使った場合以外から最大を取りたい。
　なので直前に使った種類をセグ木で状態に持ってDP。
　自分と同じ種類以外から遷移する最大+V[i]でchmaxすればOK。
　実装上は一旦前の値をprvに逃がしてINFに戻して、全体から最大値取る形にした。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), V(N);
    rep(i, N) {
        cin >> A[i] >> V[i];
        A[i]--;
    }

    auto dp = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    dp.build(vector<ll>(N+1, -INF));
    dp.update(N, 0);
    rep(i, N) {
        ll prv = dp[A[i]];
        dp.update(A[i], -INF);
        dp.update(A[i], max(prv, dp.all() + V[i]));
    }
    ll ans = dp.all();
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
