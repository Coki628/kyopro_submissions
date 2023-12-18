/*
・きっちり自力AC！
・サイクルシフト、全体リバース、ロリハ
・操作は右サイクルシフトと全体リバースだが、先にリバースしておけば
　左サイクルシフトもできる。逆にそれ以外の順序変更はできない。
　なので配列2倍で用意しておいて、それら両方を試せばOK。
　ソート済判定はロリハにソート済のハッシュ入れて確認したけど、
　差分列をMINセグ木に入れておくというのがあったね…。(TL見た)
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    RollingHash rh;
    auto sorted_a = sorted(A);
    auto sorted_a_rev = reversed(sorted_a);
    auto sorted_a_hash = rh.get_hash(sorted_a);
    auto sorted_a_rev_hash = rh.get_hash(sorted_a_rev);
    A = concat(A, A);
    ll ans = INF;
    auto table = rh.build(A);
    ll cnt = 0;
    rep(l, N, 0, -1) {
        ll r = l + N;
        if (rh.query(table, l, r) == sorted_a_hash) {
            chmin(ans, cnt);
        }
        if (rh.query(table, l, r) == sorted_a_rev_hash) {
            chmin(ans, cnt + 1);
        }
        cnt++;
    }
    cnt = 0;
    rep(l, N) {
        ll r = l + N;
        if (rh.query(table, l, r) == sorted_a_hash) {
            chmin(ans, cnt + 2);
        }
        if (rh.query(table, l, r) == sorted_a_rev_hash) {
            chmin(ans, cnt + 1);
        }
        cnt++;
    }
    if (ans >= INF) ans = -1;
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
