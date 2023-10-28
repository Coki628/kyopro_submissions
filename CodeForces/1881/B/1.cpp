/*
・きっちり自力AC。
・何個に分けるか3～6個全部見る。そこが決まれば、
　値を何に揃えたいかが定まるので、うまくいけるか愚直シミュ。
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
    ll a, b, c;
    cin >> a >> b >> c;
    vector<ll> A = {a, b, c};

    ll sm = sum(A);
    rep(sz, 3, 7) {
        if (sm % sz != 0) continue;
        ll each = sm / sz;
        auto cur = A;
        ll cnt = 3;
        bool ok = true;
        for (auto a : cur) {
            while (a > each) {
                a -= each;
                cnt++;
            }
            if (a < each) {
                ok = false;
                break;
            }
        }
        if (ok and cnt == sz) {
            YES();
            return;
        }
    }
    NO();
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
