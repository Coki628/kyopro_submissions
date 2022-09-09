/*
参考：https://twitter.com/AllDirections4/status/1567916846233567237
・自力ならず。これは解きたかったな悔しい。
・ゲームDP、2乗の区間DP
・辞書順最小で前に挿入なので、基本的に最後に2人が取った文字によって勝敗が決まる。
　引き分けなら前のターンに決着は持ち越し、みたいなメモ化再帰をやる。
　かなり近い形は作れてたのに、直前に使った文字を添字に持つのができなかった。
　途中ちょっと考えたんだけど、それをやったとしても、
　先行が取った後の勝敗分からなくない？って棄却してしまっていた。
　よく考えると、先行が取った直後は勝敗を決める必要がなくて、
　戻り値に応じて特に何もせずに自分に有利な方を選ぶだけでいい。
　後攻が引き分けを受け取った時だけ、直前の文字とその時選ぶ文字を比較して勝敗を決める。
　なお後攻から先行に渡す時の直前文字は使わないので何を渡してもいい。(ので常にaを渡した。)
・TLで最後の文字も記録ってのを見て、それ踏まえてちゃんと考えたら解けたんだよな。悔しいー。
・なお、TLからの情報によると、Bobが勝つパターンはないらしい。
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
    string S;
    cin >> S;
    ll N = S.size();

    ll M = 26;
    auto memo = listnd(M, N, N+1, -1);
    rep(c, M) {
        rep(i, N-1) {
            // Alice
            if (S[i] != S[i+1]) {
                memo[c][i][i+2] = 2;
            // Draw
            } else {
                memo[c][i][i+2] = 1;
            }
        }
    }
    auto rec = [&](auto&& f, ll l, ll r, char c) -> ll {
        if (memo[c-'a'][l][r] != -1) {
            return memo[c-'a'][l][r];
        }
        ll turn = (r-l) % 2;
        if (turn == 0) {
            ll res = max(f(f, l+1, r, S[l]), f(f,  l, r-1, S[r-1]));
            memo[c-'a'][l][r] = res;
            return res;
        } else {
            ll res1 = f(f, l+1, r, 'a');
            if (res1 == 1) {
                res1 = S[l] < c ? 0 : S[l] == c ? 1 : 2;
            }
            ll res2 = f(f, l, r-1, 'a');
            if (res2 == 1) {
                res2 = S[r-1] < c ? 0 : S[r-1] == c ? 1 : 2;
            }
            ll res = min(res1, res2);
            memo[c-'a'][l][r] = res;
            return res;
        }
    };
    ll res = rec(rec, 0, N, 'a');
    if (res == 2) {
        print("Alice");
    } elif (res == 1) {
        print("Draw");
    } else {
        print("Bob");
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
