/*
・Div.3残埋め
・なんとか自力AC！でもE,F,Gで一番悩んだと思う…。
・2人ゲーム、貪欲
・TL長めだし、何かデータ構造使うのかと思ったら普通にゲームによくある貪欲だった。
　最初「操作しなくていい場所」を数えてたんだけど、
　「操作しなきゃいけない場所」に注目したら見通しが良くなった。
　(今これ自分で書いてて、それはそうって気になってる…。)
　これを1人が必要な場所と2人が必要な場所それぞれで数えておいて、
　実際にゲームを貪欲にシミュしたら通った。
　勝利条件は、それぞれ必要な場所がなくなった状態で手番が来たら勝ち、
　2人とも必要な場所だけが最後に1つ残ってしまったら、
　(それを自分が取ったら次の相手番で勝たれるので)お互いずっとスキップになり引き分け。
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
    vector<ll> A(N);
    cin >> A;
    A--;

    ll aneed = 0, bneed = 0, bothneed = 0;
    rep(i, N) {
        if (A[i] != i and A[i] != N - i - 1) {
            bothneed++;
        } else if (A[i] != i) {
            aneed++;
        } else if (A[i] != N - i - 1) {
            bneed++;
        }
    }
    rep(t, N + 1) {
        // これを取ったら次で負ける状態
        if (aneed == 0 and bneed == 0 and bothneed == 1) {
            print("Tie");
            return;
        }
        if (t % 2 == 0) {
            if (aneed == 0 and bothneed == 0) {
                print("First");
                return;
            }
            if (aneed > 0) {
                aneed--;
            } else if (bothneed > 0) {
                bothneed--;
            }
        } else {
            if (bneed == 0 and bothneed == 0) {
                print("Second");
                return;
            }
            if (bneed > 0) {
                bneed--;
            } else if (bothneed > 0) {
                bothneed--;
            }
        }
    }
    assert(0);
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
