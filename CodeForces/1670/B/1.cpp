/*
・きっちり自力AC！
・最初に消せるindexを列挙して、差分の一番大きい所。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }
    vector<ll> C(26);
    ll M;
    cin >> M;
    rep(i, M) {
        char c;
        cin >> c;
        C[c-'a'] = 1;
    }

    ll ans = 0;
    vector<ll> ids = {-1};
    rep(i, N) {
        if (i > 0 and C[A[i]]) {
            ids.eb(i-1);
            ans = 1;
        }
    }
    rep(i, 1, ids.size()) {
        chmax(ans, ids[i]-ids[i-1]);
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
