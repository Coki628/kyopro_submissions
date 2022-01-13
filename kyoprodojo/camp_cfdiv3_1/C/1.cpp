/*
・cf1360_C
・きっちり自力AC！
・偶奇
・まず偶奇で分けてそこでなるべく組ませるとすると、
　全部OKか1ペアだけ余る所までは行ける。
　1ペア余っていたら、もう1つの条件(差分が1)が使えるものがあるかは、
　2乗が効く制約なので普通に全探索できる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> A1, A2;
    rep(i, N) {
        if (A[i]%2 == 0) {
            A1.eb(A[i]);
        } else {
            A2.eb(A[i]);
        }
    }
    if (A1.size()%2 == 0) {
        YES();
        return;
    }

    for (auto a1 : A1) {
        for (auto a2 : A2) {
            if (abs(a1-a2) == 1) {
                YES();
                return;
            }
        }
    }
    NO();
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
