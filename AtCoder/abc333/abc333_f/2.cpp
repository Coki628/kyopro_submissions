/*
・自力ならず。
・自己ループのある確率DP、メモ化再帰
・DP定義が微妙に外してて、そのままじゃ無理だった。
　初期状態を100%として配るDPする方針で
　dp[i] := i人いる状態で、ある人が先頭にいる確率
　を後ろから決めていこうとしたんだけど、これだと元々先頭の人以外を決める時に、
　DPの初期状態を変えねばならず、結局3乗から落とせなかった。
　で、これを逆に終了状態を100%として、期待値DPみたく貰うDPする
　memo[i] := i人いる状態で、その時点で先頭にいる人が最終的に生き残る確率
　の形にすると、遷移ほぼ一緒なんだけど、うまくいく。
　先頭以外の人を決める時に、DPの結果から欲しい確率を取れるようになるので、
　2乗オーダーで最終的な答えを求めることができる。
・なお、前に確率DPだと自己ループ補正なくてもいいみたいな話があった(abc300_e)けど、
　やっぱりそれは任意の場合にOKな訳ではなかった。
　今回は確率だけど自己ループ補正かけないと壊れる。
　多分だけど、今回は自己ループ以外に捨てる遷移(注目してる人が消えるパターン)
　もあるからダメなんだと思う。
・普通に出したら1.13秒で遅かったのでちょっと調整。
　最深部でやるmodpowとmod除算のlogは結構重いので前計算。これで0.11秒になった。
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

void solve() {
    ll N;
    cin >> N;

    ModTools<mint> mt(N + 1);
    vector<mint> pow2inv(N + 1);
    rep(i, N + 1) {
        pow2inv[i] = (mint)1 / pow(2LL, i, MOD);
    }
    // memo[i] := i人いる状態で、その時点で先頭にいる人が最終的に生き残る確率
    vector<mint> memo(N + 1);
    vector<int> visited(N + 1);
    auto rec = [&](auto &&f, ll i) -> mint {
        if (visited[i]) return memo[i];
        if (i == 1) return 1;

        mint total = pow(2LL, i, MOD);
        mint selfloop = total / (total - 1);
        mint res = 0;
        rep(j, i - 1, 0, -1) {
            // 遷移元 += 遷移先 * 自己ループ補正 * i-1人からj-1人残す(自分は絶対残すので-1) / 全通り
            res += f(f, j) * selfloop * mt.nCr(i - 1, j - 1) * pow2inv[i];
        }
        visited[i] = true;
        return memo[i] = res;
    };
    rec(rec, N);

    vector<mint> ans(N);
    rep(k, N) {
        rep(i, k + 1) {
            // 初期状態から(kより前にいたやつらが)i人残って人kが先頭になる確率
            ans[k] += rec(rec, N - (k - i)) * mt.nCr(k, i) * pow2inv[k];
        }
    }
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
