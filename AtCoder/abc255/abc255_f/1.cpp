/*
・これは自力WA。
・条件整えていけばなるようにならんかな、って思ったらならなかった…。
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<bool> visited(N+1);
    vector<pll> ans(N+1);
    ll i = 0, j = 0;
    auto dfs = [&](auto&& f, ll u, ll par) -> void {
        visited[u] = true;
        if (i+1 < N and j < N and A[i] != B[j] and not visited[B[j]]) {
            i++;
            ans[u].first = A[i];
            f(f, A[i], u);
        }
        if (i < N and j+1 < N and B[j] == u and not visited[B[j+1]]) {
            j++;
            i++;
            if (i == j) {
                ans[u].second = A[i];
                f(f, A[i], u);
            } elif (i > j) {
                ans[u].second = B[j];
                f(f, B[j], u);
            } else {
                assert(0);
            }
        } else {
            j++;
        }
    };
    if (A[0] != 1) {
        print(-1);
        return;
    }
    dfs(dfs, 1, 0);
    if (j < N) {
        print(-1);
        return;
    }
    ans.erase(ans.begin());
    print(ans, '\n');
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
