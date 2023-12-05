/*
参考：https://atcoder.jp/contests/abc331/submissions/48133683
・自力ならず。
・ロリハ、1点更新、回文判定
・せっかく回文判定は作ってあったのに、1点更新ができなくて終了。。
　累積和みたいなんだからうまくやれば更新できそうだよね、って思ってたけどやっぱできるのね。
　とりあえずこっちが自分が元々やろうとした、累積和配列の代わりにBITにハッシュを乗せる方針。
　ただし累積の方法が元々の累積和配列と全く同じ形という訳にはいかず、
　累積の値を調整するために基数冪での除算が必要になり、前計算の逆元を用意した。
　一応、毎回MOD除算やるのと比較したら、0.26→0.16秒でちゃんと速くなった。
　log重なってはいないので定数倍なんだけど、まあBITのlogよりはMOD除算のlogのが絶対重いだろうから、
　効果はあるかなと思ったけど、ちゃんとあった。
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

#include "string/RollingHashUpdatable.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    RollingHashUpdatable rh;
    auto table = rh.build(S);
    auto rev = rh.build(reversed(S));
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            char c;
            cin >> x >> c;
            x--;
            rh.update(table, x, c);
            rh.update(rev, N - x - 1, c);
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
            YesNo(rh.is_palindrome(table, rev, l, r));
        }
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
