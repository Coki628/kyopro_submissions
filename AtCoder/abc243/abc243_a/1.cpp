/*
・周期
・ループ回らない制約だったら相当攻めてるAだけど、
　まあループ回せる制約なので愚直シミュする。
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
    ll v;
    cin >> v;
    auto A = LIST(3);

    vector<char> ans = {'F', 'M', 'T'};
    while (1) {
        rep(i, 3) {
            if (v-A[i] < 0) {
                print(ans[i]);
                return;
            }
            v -= A[i];
        }
    }
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
