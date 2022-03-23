/*
参考：https://twitter.com/stoq_/status/1506313573454467074
・なんとか自力AC。大変だった。。
・括弧列、回文
・絶対ハズレ方針引いてると思いながらも、良い案も出ないので突き進む。
　括弧列は前から判定できるとして、回文。反転した文字列を持っとくと、
　適切な位置で比較すれば前半と後半の比較にできるから、部分文字列の一致判定になる。
　でも反転させてるのと、prefixがずれていくので添字が地獄になる。
　ロリハ持ち出したんだけどもっと賢い方法あったんかな…。
・あったよ。)(...で次に)が来たらって言われたらそれはそう過ぎる。。
・賢い解法が出るかは分からないので、stoqさんのを参考にロリハライブラリに回文判定を組み込んだ。
　これで今度高速な回文判定が欲しくなっても添字とか困らずさっと取り出せるはず。
・なんとシステス落ちてたので再提出。。
　確かに自分のコードよく見直したら、括弧列チェックと回文チェックを独立にやってるから、
　最悪を想定すると、片方すぐ終わって片方めっちゃ先まで行くみたいなのが連続する時に
　先まで行く方をN回近くやることになるので、2乗になってた。。
　チェックを同時並行で進める形にしたら無事AC。今回まじで終わってたな…。
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

    auto check = [&](ll i) {
        ll cnt = 0;
        rep(j, i, N) {
            // 括弧列の判定
            if (S[j] == '(') {
                cnt++;
            } else {
                cnt--;
            }
            if (cnt == 0) {
                return j + 1;
            } elif (cnt < 0) {
                // もう無理なので、適当に絶対0に到達しない値を突っ込む
                cnt = MOD;
            }
            // 回文の判定
            ll len = j - i + 1;
            if (len >= 2) {
                if (rh.is_palindrome(s_table, t_table, i, j+1)) {
                    return j + 1;
                }
            }
        }
        return INF;
    };

    ll cnt = 0, i = 0;
    while (i < N) {
        ll res = check(i);
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
