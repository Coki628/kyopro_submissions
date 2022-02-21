/*
・きっちり自力AC！
・ランレングスぽい持ち方でスタックに詰めてシミュした。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<pll> st;
    ll cnt = 0;
    rep(i, N) {
        if (st.size() and st.back().first == A[i]) {
            st.back().second++;
        } else {
            st.eb(A[i], 1);
        }
        cnt++;
        if (st.back().second == st.back().first) {
            cnt -= st.back().second;
            st.pop_back();
        }
        print(cnt);
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
