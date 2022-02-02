/*
・きっちり自力AC！
・辞書順最小の貪欲
・できる操作の中で、前から順に可能な限り小さくするのを考える。
　手前から順にiを進めて、区間[i+1, j)で後ろから最小値の位置を取って次のjとして、
　S[i]より小さければスワップ、i < jでなくなったら終了。ってやった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    vector<ll> A(ALL(S));
    auto seg = get_segment_tree([](ll a, ll b) { return min(a, b); }, INF);
    seg.build(A);
    ll i = 0, j = N;
    while (i < j) {
        ll mn = seg.query(i+1, j);
        if (mn < A[i]) {
            j = seg.find_last(j, [&](ll a) { return a <= mn; });
            seg.update(j, A[i]);
            swap(A[i], A[j]);
        }
        i++;
    }
    string ans(ALL(A));
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
