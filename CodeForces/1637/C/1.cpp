/*
・自力AC！
・N=3だけ偶奇で、他は2以上が1つでもあるか、で通った。
　1箇所しかないN=3は別として、他は1箇所でも動かせれば、
　そこを起点にして周りを偶数に調整していけるからOK、ってことでいいと思う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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

    if (N == 3) {
        if (A[1]%2 == 1) {
            print(-1);
            return;
        }
    } else {
        bool ok = false;
        rep(i, 1, N-1) {
            if (A[i] >= 2) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            print(-1);
            return;
        }
    }

    ll cnt = 0;
    rep(i, 1, N-1) {
        cnt += ceil(A[i], 2LL);
    }
    print(cnt);
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
