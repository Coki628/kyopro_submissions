/*
・なんとか自力AC。。
・前から貪欲
・基本的に隣接が逆順を向いている所は何とかしなければならず、
　今回の操作であればそこより手前を全部0にする必要がある。
　値毎にいっぺんに全部0になってしまうので、
　各値が既に0になったかを配列に持ちながら、
　現在昇順に向いていて残している値の集合も持つ。
　これでダメな場所が見つかったら、
　その集合にある値を全部0として、集合を空にすればいい。
　0にした値の種類数が操作回数になる。
・方針は合ってたんだけど、既に0になったかの配列で、
　0を最初からTrueにしておらず、これが原因でかなり手こずった。
　ランダムケース回して気付けたけど、遅すぎた…。
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

    set<ll> se = {A[0]};
    vector<bool> removed(N+1);
    removed[0] = true;
    ll ans = 0;
    rep(i, 1, N) {
        if (removed[A[i]]) A[i] = 0;
        if (A[i-1] > A[i]) {
            for (auto a : se) {
                removed[a] = true;
            }
            ans += se.size();
            se.clear();
        }
        if (not removed[A[i]]) se.insert(A[i]);
    }
    print(ans);
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
