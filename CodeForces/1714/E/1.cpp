/*
・きっちり自力AC！
・グラフに帰着、サイクル
・5,0とその他で連結成分になる。5,0は0にして一致するか。
　その他は2,4,8,6のサイクルに持ってって、mod 20で同じ所にいればOKとした。
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
    auto A = LIST(N);

    vector<bool> tp(2);
    rep(i, N) {
        ll d = A[i] % 10;
        if (d == 0 or d == 5) {
            tp[0] = 1;
        } else {
            tp[1] = 1;
        }
    }
    if (tp[0] and tp[1]) {
        No();
        return;
    }

    // 5,0 only
    if (tp[0]) {
        rep(i, N) {
            if (A[i]%10 == 5) {
                A[i] += 5;
            }
        }
        set<ll> se(ALL(A));
        if (se.size() == 1) {
            Yes();
        } else {
            No();
        }
    // others
    } else {
        // 最初から全部一致
        set<ll> se(ALL(A));
        if (se.size() == 1) {
            Yes();
            return;
        }

        se.clear();
        rep(i, N) {
            while (A[i]%10 != 2) {
                ll d = A[i] % 10;
                A[i] += d;
            }
            se.insert(A[i]%20);
        }
        if (se.size() == 1) {
            Yes();
        } else {
            No();
        }
    }
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
