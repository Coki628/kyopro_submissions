/*
・自力ならず。これはひどい。
・平方数
・順列全探索で13は無理なので、平方数を全列挙する方針を取る。
　順列で再現できるかはソート済同士を比較すれば判定できる。
　そこまではできていた。平方数0*0を見落としてた。これは気付けるべき…。
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
    string S;
    cin >> S;

    vector<string> vec;
    ll x = 0;
    while (x * x <= 1e13) {
        auto t = tostr(x * x);
        if (t.size() <= N) {
            while (t.size() < N) {
                t.pb('0');
            }
            vec.pb(t);
        }
        x++;
    }
    sort(ALL(S));
    ll ans = 0;
    for (auto t : vec) {
        sort(ALL(t));
        if (t == S) ans++;
    }
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
