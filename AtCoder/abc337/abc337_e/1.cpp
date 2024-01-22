/*
・これは自力WA。
・1~4,2~5,3~6,,,みたいに1個ずつずらしてやった。
　なんでこんな素人っぽい方針しか生えなかったんだろ。
　何年競プロやってんだかな…。
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
    ll M = N / 2 + 1;
    cout << M << endl;

    ll K = ceil(N, 2LL);
    vvl A = listnd(M, K, 0LL);
    rep(i, M) {
        cout << K << ' ';
        rep(j, K) {
            A[i][j] = i + j;
        }
        A[i]++;
        cout << A[i] << endl;
        A[i]--;
    }

    string S;
    cin >> S;
    vector<ll> C(N);
    ll scnt = 0;
    rep(i, M) {
        if (S[i] == '1') {
            scnt++;
            for (auto a : A[i]) {
                C[a]++;
            }
        }
    }
    rep(i, N) {
        if (C[i] == scnt) {
            cout << i + 1 << endl;
            return;
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
