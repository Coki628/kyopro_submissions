/*
・きっちり自力AC！
・逆操作、deque
・前からやろうとすると厳しいけど、逆操作を考えれば前後に足すだけなのでdequeでいける。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    string S;
    cin >> S;

    deque<ll> A = {N};
    rep(i, N-1, -1, -1) {
        if (S[i] == 'L') {
            A.pb(i);
        } else {
            A.push_front(i);
        }
    }
    print(A);
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
