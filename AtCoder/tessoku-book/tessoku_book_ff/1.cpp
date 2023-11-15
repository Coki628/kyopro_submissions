/*
・きっちり自力AC！
・1等を10000通り全探索する。0埋めが結構罠。
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
    vector<string> A(N);
    vector<ll> B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    auto check = [&](ll one, string t, ll b) {
        auto s = zfill(tostr(one), 4);
        ll diff = 0;
        rep(i, 4) {
            if (s[i] != t[i]) diff++;
        }
        if (diff == 0) {
            return b == 1;
        } else if (diff == 1) {
            return b == 2;
        } else {
            return b == 3;
        }
    };
    ll okcnt = 0;
    string ans;
    rep(one, 10000) {
        bool ok = true;
        rep(i, N) {
            if (!check(one, A[i], B[i])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            okcnt++;
            ans = zfill(tostr(one), 4);
        }
    }
    assert(okcnt > 0);
    if (okcnt == 1) {
        print(ans);
    } else {
        print("Can't Solve");
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
