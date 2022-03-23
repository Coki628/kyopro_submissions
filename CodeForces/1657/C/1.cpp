/*
・これは文字列比較愚直にやってるしTLE想定。
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
    string S;
    cin >> S;

    string T = reversed(S);

    auto check1 = [&](string& s) {
        ll cnt = 0;
        rep(i, s.size()) {
            if (s[i] == '(') {
                cnt++;
            } else {
                cnt--;
            }
            if (cnt == 0) {
                return i+1;
            } elif (cnt < 0) {
                return INF;
            }
        }
        return INF;
    };
    auto check2 = [&](string& s, string& t) {
        rep(len, 2, s.size()+1) {
            ll l1 = 0;
            ll r1 = len / 2;
            l1 = t.size() - r1;
            r1 = t.size();
            ll l2 = len%2 == 0 ? len / 2 : len / 2 + 1;
            ll r2 = len;
            if (t.substr(l1, r1-l1) == s.substr(l2, r2-l2)) {
                return len;
            }
        }
        return INF;
    };

    ll cnt = 0;
    while (1) {
        ll res = min(check1(S), check2(S, T));
        if (res == INF) break;
        S = S.substr(res);
        T = T.substr(0, T.size()-res);
        cnt++;
    }
    ll rest = S.size();
    print(mkp(cnt, rest));
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
