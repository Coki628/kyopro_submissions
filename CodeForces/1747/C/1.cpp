/*
・なんとか自力AC！
・ゲーム
・展開を逆から見ていく。先頭が0を渡されたら負け確定
　→先頭が1以上でどこかに0があれば(その0を持ってくればいいので)勝ち確定、
　その直前は1が先頭にあって-1されて0になって先頭以外に飛ばされたはずなので、
　先頭が1(で他も1以上)を渡されたら負け確定...としていくと、
　最小値が先頭にあるのが負け状態となる。よって初期状態でA[0] == min(A)ならアリス負け。
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

    if (A[0] == min(A)) {
        print("Bob");
    } else {
        print("Alice");
    }
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
