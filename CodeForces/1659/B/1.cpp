/*
・自力AC。
・偶奇
・(自分の中では)Aよりは簡単。Kの偶奇で最終的にどうなる予定か分かるので、
　それで0になりそうな箇所を前からできる限り反転。余ったKは末尾で適当に使い切る。
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
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    string ans = S;
    ll k = K;
    vector<ll> C(N);
    if (K%2 == 1){
        rep(i, N) {
            ans[i] = tochar(1-toint(S[i]));
        }
    }
    rep(i, N) {
        if (k > 0 and ans[i] == '0') {
            ans[i] = '1';
            C[i] = 1;
            k--;
        }
    }
    C[N-1] += k;
    if (k%2 == 1) {
        ans[N-1] = '0';
        k = 0;
    }
    print(ans);
    print(C);
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
