/*
・きっちり自力AC！
・分かりやすさのため、グラフの形にして処理した。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    A--;
    vvi nodes(N);
    ll s = -1;
    rep(i, N) {
        if (A[i] == -2) {
            s = i;
        } else {
            nodes[A[i]].eb(i);
        }
    }

    vector<ll> ans = {s};
    ll cur = s;
    rep(i, N - 1) {
        assert(nodes[cur].size() == 1);
        cur = nodes[cur][0];
        ans.eb(cur);
    }
    ans++;
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
