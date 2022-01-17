/*
・なんとか自力AC！時間かかった…。
・スタック、等差数列の和
・前の要素をどこまで取り込めるかがやってみるまで読めない。
　けど後ろにマージされた要素はもう使う必要がない。
　こういう時はスタックで持てばうまくいく。に気付くのがだいぶ遅かった。
・前からスタックで持って、今見ている位置にマージされる所は捨てる。
　最後まで見て残ったやつらを等差数列の和やる。
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

#include "../../../_lib/cpp/_src/numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<pll> st;
    rep(i, N) {
        ll cur = B[i];
        while (st.size() and st.back().second > A[i]-cur) {
            chmax(cur, st.back().first+(A[i]-st.back().second));
            st.pop_back();
        }
        st.eb(cur, A[i]);
    }
    ll ans = 0;
    for (auto [v, _] : st) {
        ans += arithmetic_sequence_sum(1LL, 1LL, v);
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
