/*
・きっちり自力AC！
・スタックやる。
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
    string S;
    cin >> S;
    ll N = S.size();

    set<char> se;
    vector<char> st;
    rep(i, N) {
        if (islower(S[i])) {
            if (se.count(S[i])) {
                No();
                return;
            }
            st.eb(S[i]);
            se.insert(S[i]);
        } else if (S[i] == '(') {
            st.eb(S[i]);
        } else {
            while (st.size() and st.back() != '(') {
                se.erase(st.back());
                st.pop_back();
            }
            assert(st.size());
            st.pop_back();
        }
    }
    Yes();
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
