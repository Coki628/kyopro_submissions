/*
・きっちり自力AC！
・使用回数毎に文字を持っとく。
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
    auto A = LIST(N);

    char c = 'a';
    string ans;
    vv<char> adj(N + 1);
    rep(i, N) {
        if (A[i] == 0) {
            ans += c;
            adj[1].eb(c);
            c++;
        } else {
            assert(adj[A[i]].size());
            char cc = adj[A[i]].back();
            adj[A[i]].pop_back();
            ans += cc;
            adj[A[i] + 1].eb(cc);
        }
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
    while (T--) solve();

    return 0;
}
