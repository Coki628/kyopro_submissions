/*
・きっちり自力AC！
・Functional Graphの閉路検出と復元
・訪問済まで進んで、繋がった所より手前は削るってやった。
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
    vector<ll> A(N);
    cin >> A;
    A--;

    vector<ll> visited(N);
    ll cur = 0;
    visited[cur] = 1;
    deque<ll> ans = {cur};
    while (not visited[A[cur]]) {
        cur = A[cur];
        ans.eb(cur);
        visited[cur] = 1;
    }
    while (ans.front() != A[cur]) {
        ans.pop_front();
    }
    for (auto &a : ans) a++;
    print(ans.size());
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
