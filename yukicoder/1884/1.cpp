/*
・きっちり自力AC！
・間隔を広げることはできないので、一番小さい間隔に合わせる感じで大きいのを貪欲に切っていく。
　ハフマンみたいな貪欲で。最大と最小両方見たかったからプリキューじゃなくてmultisetで。
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

#include "mystl/my_multiset.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> A2;
    rep(i, N) {
        if (A[i] > 0) {
            A2.eb(A[i]);
        }
    }
    ll N2 = A2.size();
    if (N2 < 2) {
        Yes();
        return;
    }
    ll cnt = N - N2;
    sort(ALL(A2));
    my_multiset<ll> se;
    rep(i, N2-1) {
        se.insert(A2[i+1]-A2[i]);
    }
    ll mn = se.front();
    while (cnt and se.back() > se.front()) {
        ll b = se.pop_back();
        ll b1 = mn;
        ll b2 = b - mn;
        se.insert(b1);
        se.insert(b2);
        mn = se.front();
        cnt--;
    }
    if (se.front() == se.back()) {
        Yes();
    } else {
        No();
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
