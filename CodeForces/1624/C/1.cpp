/*
・自力AC！
・使える値全列挙して、順列小さい方からだとサンプル合わなかったので大きい方から貪欲に使ったら通った。
　適当にガチャガチャして何とかするのやめたいね…。
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

    sort(ALL(A));
    vector<set<ll>> se(N);
    rep(i, N) {
        while (A[i]) {
            se[i].insert(A[i]);
            A[i] /= 2;
        }
    }
    vector<bool> used(N);
    rep(p, N, 0, -1) {
        bool ok = false;
        rep(i, N) {
            if (not used[i] and se[i].count(p)) {
                used[i] = true;
                ok = true;
                break;
            }
        }
        if (not ok) {
            NO();
            return;
        }
    }
    YES();
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
