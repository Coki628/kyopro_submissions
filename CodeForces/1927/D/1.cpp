/*
・自力AC！
・最初ちょっと激ヤバな方向に迷走しかけたが、
　ちゃんと簡潔な方針に着地できてよかった。
　結局、次に違う値が来るindexを各位置で持っておけばよく、
　これは後ろからDPみたいに前計算できる。
　これで各クエリは、左端で上記をチェックして、
　右端までの範囲に収まってるかを見れば分かる。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vector<ll> nxdiff(N, N);
    rep(i, N - 2, -1, -1) {
        if (A[i] != A[i + 1]) {
            nxdiff[i] = i + 1;
        } else {
            nxdiff[i] = nxdiff[i + 1];
        }
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;

        if (nxdiff[l] < r) {
            ll i = l;
            ll j = nxdiff[l];
            print({i + 1, j + 1});
        } else {
            print({-1, -1});
        }
    }
    print();
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
