/*
・きっちり自力AC！
・インタラクティブ、にぶたん
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

ll ask(const vector<ll> &vec) {
    ll res;
    cout << "? " << vec.size() << ' ';
    cout << vec << endl;
    cin >> res;
    return res;
}

void answer(ll i) {
    cout << "! " << i + 1 << endl;
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    Accumulate<ll> acc(A);
    ll res = bisearch_max(-1, N, [&](ll x) {
        vector<ll> vec;
        rep(i, x + 1) {
            vec.eb(i);
        }
        vec++;
        ll res = ask(vec);
        return res == acc.query(0, x + 1);
    });
    answer(res + 1);
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
