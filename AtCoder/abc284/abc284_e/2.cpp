/*
・自力AC！
・再帰全探索、バックトラック、打ち切り
・もっと早く気付けるべきだったな。愚直に再帰全探索して10^6で打ち切り。
　メモとかしないけど、状態戻しは適切にやる。
・終了後、set使うとやっぱ遅いなぁってことで訪問済み管理をvectorに。
　0.76秒→0.12秒でやっぱり相当速くなった。
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
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    const ll LIMIT = 1000000;
    ll ans = 0;
    vector<int> used(N);
    used[0] = true;
    auto dfs = [&](auto &&f, ll u) -> void {
        ans++;
        if (ans == LIMIT) {
            print(LIMIT);
            exit(0);
        }
        for (auto v : nodes[u]) {
            if (not used[v]) {
                used[v] = true;
                f(f, v);
                used[v] = false;
            }
        }
    };
    dfs(dfs, 0);
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
