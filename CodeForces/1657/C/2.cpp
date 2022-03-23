/*
・なんとか自力AC。大変だった。。
・括弧列、回文
・絶対ハズレ方針引いてると思いながらも、良い案も出ないので突き進む。
　括弧列は前から判定できるとして、回文。反転した文字列を持っとくと、
　適切な位置で比較すれば前半と後半の比較にできるから、部分文字列の一致判定になる。
　でも反転させてるのと、prefixがずれていくので添字が地獄になる。
　ロリハ持ち出したんだけどもっと賢い方法あったんかな…。
・あったよ。)(...で次に)が来たらって言われたらそれはそう過ぎる。。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    string T = reversed(S);
    RollingHash rh;
    auto s_table = rh.build(S);
    auto t_table = rh.build(T);

    auto check1 = [&](ll i) {
        ll cnt = 0;
        rep(j, i, N) {
            if (S[j] == '(') {
                cnt++;
            } else {
                cnt--;
            }
            if (cnt == 0) {
                return j + 1;
            } elif (cnt < 0) {
                return INF;
            }
        }
        return INF;
    };
    auto check2 = [&](ll i) {
        rep(len, 2, N+1) {
            ll l1 = i + 0;
            ll r1 = i + len / 2;
            ll tl = N - r1;
            ll tr = N - l1;
            ll l2 = len%2 == 0 ? i + len / 2 : i + len / 2 + 1;
            ll r2 = i + len;
            if (r2 > N) break;
            if (rh.query(t_table, tl, tr) == rh.query(s_table, l2, r2)) {
                return i + len;
            }
        }
        return INF;
    };

    ll cnt = 0, i = 0;
    while (i < N) {
        ll res = min(check1(i), check2(i));
        if (res == INF) break;
        i = res;
        cnt++;
    }
    ll rest = N - i;
    print(mkp(cnt, rest));
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
