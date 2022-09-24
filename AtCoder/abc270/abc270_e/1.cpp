/*
・自力AC！
・二分探索
・1からNまでの1周を、個数が変化する所までひとまとめにしてにぶたん。
　K未満の最大まで進んで、途中で終わる所に来たらそこから愚直シミュ。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    auto C = Counter(A);
    ll acnt = N - C[0];
    auto keys = A;
    keys.eb(0);
    UNIQUE(keys);
    ll M = keys.size();
    ll cur = 0;
    rep(i, 1, M) {
        ll h = keys[i] - keys[i-1];
        ll res = bisearch_max(0, h+1, [&](ll x) {
            return cur+x*acnt < K;
        });
        cur += res*acnt;
        if (res < h) {
            rep(j, N) {
                A[j] = max(A[j]-(keys[i-1]+res), 0LL);
            }
            rep(j, N) {
                if (A[j] > 0) {
                    cur++;
                    A[j]--;
                }
                if (cur == K) {
                    print(A);
                    return;
                }
            }
        } else {
            acnt -= C[keys[i]];
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
