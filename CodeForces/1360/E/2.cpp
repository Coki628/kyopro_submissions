/*
・dojo camp_cfdiv3_1
・きっちり自力AC！
・詰まるところ、1があったら、右か下にも1があるかどうかだけチェックすればいい。
　(最終行、最終列は除く。)
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
    vector<string> grid(N);
    rep(i, N) {
        cin >> grid[i];
    }

    rep(i, N) {
        rep(j, N) {
            if (grid[i][j] == '0') continue;
            bool ok = false;
            if (i == N-1 or grid[i+1][j] == '1') {
                ok = true;
            }
            if (j == N-1 or grid[i][j+1] == '1') {
                ok = true;
            }
            if (not ok) {
                NO();
                return;
            }
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
