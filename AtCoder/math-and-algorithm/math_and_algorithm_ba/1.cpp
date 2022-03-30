/*
・きっちり自力AC
・規則性、ゲームDP
・なんか手元で書くだけじゃ見えなそうなのでゲームDP書く。
　すると、2冪-1だけ負け確定だとエスパーできる。
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
    ll N;
    cin >> N;

    // vector<ll> memo(N+1);
    // vector<bool> visited(N+1);
    // auto rec = [&](auto&& f, ll a) -> ll {
    //     if (visited[a]) {
    //         return 1-memo[a];
    //     }
    //     ll res = 0;
    //     rep(i, 1, a/2+1) {
    //         res |= f(f, a-i);
    //     }
    //     visited[a] = true;
    //     memo[a] = res;
    //     return 1-res;
    // };
    // rec(rec, N);
    // print(memo);

    // 2冪-1なら後手、それ以外先手
    if (popcount(N) == bit_length(N)) {
        print("Second");
    } else {
        print("First");
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
