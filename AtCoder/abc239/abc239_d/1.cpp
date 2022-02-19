/*
・きっちり自力AC！
・素数列挙、ゲーム
・各1ターンしかないゲームなので、
　後手が何やっても勝てないっていう手が先手に1つでもあれば先手の勝ち。
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

#include "numbers/Eratosthenes.hpp"

Eratosthenes era(1000000);

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    bool taka = false;
    rep(i, a, b+1) {
        bool aoki = false;
        rep(j, c, d+1) {
            if (era.is_prime(i+j)) {
                aoki = true;
                break;
            }
        }
        if (not aoki) {
            taka = true;
            break;
        }
    }
    if (taka) {
        print("Takahashi");
    } else {
        print("Aoki");
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
