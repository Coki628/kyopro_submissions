/*
・まあすぐ通せるんだけど、こういう数値文字列変換系は、
　C++だとどうやるのが楽なんだろうねって思いながらやってる。
　Pythonだと楽そう。
・一応公式解説見た。文字列のまんまソートして比較は確かにそうだね。
　1桁だからcharでそんな感じにしてもバグらないね。
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
    string S;
    cin >> S;

    vector<ll> A = {toint(S[0]), toint(S[1]), toint(S[2])};
    sort(ALL(A));
    ll ans = A[2] - A[0];
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
