/*
・通せたのはvisibleのみ。
・順列全探索、mapでDP
・各回で乗せる順序は全探索しても最大9!から重複割ったくらいになるので小さい(多分)。
　mapにvectorの状態乗せてDPで通った。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vvl A(N);
    rep(i, N) {
        A[i] = LIST(M);
    }

    vector<vvl> perms(N);
    rep(i, N) {
        vector<ll> nxts;
        rep(j, M) {
            rep(_, A[i][j]) {
                nxts.eb(j);
            }
        }
        perms[i] = permutations(nxts);
    }
    vector<defaultdict<vector<ll>, ll>> dp(N+1, {INF});
    dp[0][{}] = 0;
    rep(i, N) {
        for (auto& [li, val] : dp[i]) {
            for (auto& perm : perms[i]) {
                ll cost = 0;
                ll m = min(li.size(), perm.size());
                ll j = 0;
                while (j < m and li[j] == perm[j]) j++;
                cost += perm.size() - j;
                cost += li.size() - j;
                chmin(dp[i+1][perm], val+cost);
            }
        }
    }
    ll ans = INF;
    for (auto& [li, val] : dp[N]) {
        chmin(ans, (ll)li.size()+val);
    }
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
