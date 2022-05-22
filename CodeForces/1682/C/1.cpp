/*
・なんとか自力AC！
・二分探索、LIS
・数が多い方から貪欲に使って、x個とx-1個が用意できればOKみたいにする。
　(片方は反対側のを1つ使えるのでx-1)
・なんか数が多い方じゃなくて値が大きい方からと小さい方からで作るみたいな嘘やってて、
　ランダムテスト回してNGケース確認して何とか修正できた。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    Compress<ll> cp(A);
    ll M = cp.size();
    A = cp.zip(A);
    auto C = Counter(A, M);
    sort(C.rbegin(), C.rend());

    ll res = bisearch_max(1, M+1, [&](ll x) {
        auto cur = C;
        ll cnt1 = 0, cnt2 = 0;
        rep(i, M) {
            if (cnt1 == x) break;
            if (cur[i]) {
                cur[i]--;
                cnt1++;
            }
        }
        if (cnt1 < x) {
            return false;
        }
        rep(i, M) {
            if (cnt2 == x-1) break;
            if (cur[i]) {
                cur[i]--;
                cnt2++;
            }
        }
        if (cnt2 == x-1) {
            return true;
        } else {
            return false;
        }
    });
    print(res);
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
