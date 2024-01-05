/*
・自力AC！
・偶奇で分けて、ソートする。こどふぉこの偶奇で分けるの好きよね。
　やることは分かったのに若干もたついて良くなかった。
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
    vector<ll> A(N);
    cin >> A;

    vector<ll> B[2];
    for (auto a : A) {
        B[a % 2].eb(a);
    }
    sort(rbegin(B[0]), rend(B[0]));
    sort(rbegin(B[1]), rend(B[1]));
    auto C = concat(B[0], B[1]);
    ll p1 = 0, p2 = 0;
    for (auto a : C) {
        if (a % 2 == 0) {
            p1 += a;
        } else {
            p2 += a;
        }
        if (p1 <= p2) {
            NO();
            return;
        }
    }
    YES();
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
