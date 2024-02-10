/*
・きっちり自力AC！
・ビット全探索
・なんかシンプルなビット全探索久しぶりに書いたな。
　最近ABCでそういえば見てない。一時期よく出てたのに。
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
    ll N, M;
    cin >> N >> M;
    vv<pii> A(M);
    rep(i, M) {
        ll K;
        cin >> K;
        rep(j, K) {
            ll a, b;
            cin >> a >> b;
            a--;
            A[i].eb(a, b);
        }
    }

    rep(bit, 1LL << N) {
        bool okok = true;
        rep(i, M) {
            bool ok = false;
            for (auto [a, b] : A[i]) {
                if ((bit >> a & 1) == b) {
                    ok = true;
                    break;
                }
            }
            if (not ok) {
                okok = false;
                break;
            }
        }
        if (okok) {
            Yes();
            return;
        }
    }
    No();
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
