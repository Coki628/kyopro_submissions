/*
・Div.3残埋め
・自力AC！やったね。
・区間Set、にぶたん、繰り上がり
・にぶたんで、末尾桁が繰り上がるまでの「全部揃う最小回数」を探す。
　繰り上がり周辺を丁寧に処理して、
　0からもう一度にぶたんで「全部揃う最小回数」を探す。
　どのくらい揃ってるかの更新と確認は区間Setでやった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "datastructure/RangeSet.hpp"

void solve() {
    ll N, P;
    cin >> N >> P;
    auto A = LIST(N);

    RangeSet<ll> rs;
    for (auto a : A) {
        rs.insert(a);
    }
    if (rs.count() == P) {
        print(0);
        return;
    }
    ll cur = A.back();
    // 末尾桁の繰り上がりまで
    ll res = bisearch_min(cur, P, [&](ll x) {
        auto currs = rs;
        currs.insert(cur, x);
        return currs.count() == P;
    });
    ll opcnt = (res - cur);
    if (res < P) {
        print(opcnt);
        return;
    }
    rs.insert(cur, P - 1);
    // 末尾桁が繰り上がる
    ll i = N - 1;
    A[i] = P;
    rs.insert(0);
    while (A[i] == P) {
        A[i] = 0;
        if (i == 0) {
            rs.insert(1);
            break;
        }
        i--;
        A[i]++;
    }
    rs.insert(A[i]);
    if (rs.count() == P) {
        print(opcnt);
        return;
    }
    // 末尾桁繰り上がり後の0から
    res = bisearch_min(0, P, [&](ll x) {
        auto currs = rs;
        currs.insert(0, x);
        return currs.count() == P;
    });
    opcnt += res;
    assert(res < P);
    print(opcnt);
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
