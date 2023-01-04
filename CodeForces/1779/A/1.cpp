/*
・きっちり自力AC！
・累積取ってチェック。結局'LR'って場所のスワップしか改善しない。
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
    string S;
    cin >> S;

    vector<ll> okl(N), okr(N), ok(N);
    rep(i, N - 1) {
        okr[i + 1] = okr[i] | (S[i] == 'R');
    }
    rep(i, N - 1, 0, -1) {
        okl[i - 1] = okl[i] | (S[i] == 'L');
    }
    rep(i, N) {
        ok[i] = okl[i] | okr[i];
    }
    ll cnt = count(ALL(ok), 1);
    if (cnt == N) {
        print(0);
        return;
    }
    rep(i, N - 1) {
        if (S[i] == 'L' and S[i + 1] == 'R') {
            if (cnt + (ok[i] == 0) + (ok[i + 1] == 0) == N) {
                print(i + 1);
                return;
            }
        }
    }
    print(-1);
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
