/*
・自力AC！
・互いに素、枝刈り
・値の範囲は1000で小さい。重複をやらなければ、
　20万の数列でも互いに素なペアはそう多くはないはず。
　i,jの条件から後ろのが有利なので、2重ループ両方後ろから回して、
　ペアが見つかったら内ループをbreak、使用済が来たら外ループをcontinueって枝刈りした。
　1.8秒かかって結構渋い。ハックされんのかな。
・制約3秒だけどハックされた。落ちた。
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
    auto A = LIST(N);

    ll ans = -1;
    vector<bool> used(1001);
    rep(i, N-1, -1, -1) {
        if (used[A[i]]) continue;
        used[A[i]] = true;
        rep(j, N-1, -1, -1) {
            if (gcd(A[i], A[j]) == 1) {
                chmax(ans, i+j+2);
                break;
            }
        }
    }
    print(ans);
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
