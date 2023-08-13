/*
・きっちり自力AC！
・全体に影響するクエリが来たら、その時間と種類を覚えておく。
　これを最後に1回だけ適用させればいい。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;
    ll Q;
    cin >> Q;

    ll k = -1, kt = -1;
    vector<ll> T(N, -1);
    rep(i, Q) {
        ll op, x;
        char c;
        cin >> op >> x >> c;
        x--;
        if (op == 1) {
            S[x] = c;
            T[x] = i;
        } else if (op == 2) {
            k = 0;
            kt = i;
        } else if (op == 3) {
            k = 1;
            kt = i;
        }
    }

    if (k != -1) {
        rep(i, N) {
            if (T[i] < kt) {
                if (k == 0) {
                    S[i] = tolower(S[i]);
                } else if (k == 1) {
                    S[i] = toupper(S[i]);
                }
            }
        }
    }
    print(S);
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
