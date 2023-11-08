/*
・きっちり自力AC！
・ようは先頭と同じ色K個と末尾と同じ色K個を使って構築できるか。
　先頭と末尾が同じ色だと少し変わるので場合分け。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll scnt = 0, s = INF;
    rep(i, N) {
        if (A[i] == A[0]) {
            scnt++;
            if (scnt == K) {
                s = i + 1;
                break;
            }
        }
    }
    if (A[0] == A[N - 1]) {
        if (s < INF) {
            YES();
        } else {
            NO();
        }
    } else {
        ll tcnt = 0, t = -INF;
        rep(i, N - 1, -1, -1) {
            if (A[i] == A[N - 1]) {
                tcnt++;
                if (tcnt == K) {
                    t = i;
                    break;
                }
            }
        }
        if (s <= t) {
            YES();
        } else {
            NO();
        }
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
