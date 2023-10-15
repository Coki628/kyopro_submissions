/*
・これはTLE。愚直にsubstr取るとダメなやつだった…。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string T;
    cin >> T;
    ll M = T.size();
    vector<string> S(N);
    cin >> S;

    auto check = [](string S, string T) {
        ll n = S.size();
        ll m = T.size();
        if (n == m) {
            ll diff = 0;
            rep(i, n) {
                if (S[i] != T[i]) diff++;
            }
            if (diff <= 1) {
                return true;
            }
        } else {
            if (n > m) {
                swap(n, m);
                swap(S, T);
            }
            rep(i, m) {
                auto T2 = T.substr(0, i) + T.substr(i + 1);
                if (T2 == S) {
                    return true;
                }
            }
        }
        return false;
    };
    vector<ll> ans;
    rep(i, N) {
        if (check(S[i], T)) {
            ans.eb(i);
        }
    }
    ans++;
    print(ans.size());
    print(ans);
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
