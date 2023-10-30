/*
・キュー
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, X;
    cin >> N >> X;
    X--;
    string S;
    cin >> S;
    Deque<ll> que = {X};
    S[X] = '@';
    while (que.size()) {
        ll i = que.pop_front();
        if (i > 0 and S[i - 1] == '.') {
            que.pb(i - 1);
            S[i - 1] = '@';
        }
        if (i < N - 1 and S[i + 1] == '.') {
            que.pb(i + 1);
            S[i + 1] = '@';
        }
    }
    print(S);
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
