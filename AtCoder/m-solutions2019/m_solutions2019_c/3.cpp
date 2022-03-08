/*
参考：https://www.youtube.com/watch?v=toLRvmaUgo4
　　　https://kmjp.hatenablog.jp/entry/2019/06/04/1000
・dojo set_e_4_4
・期待値、nCr系
・全体の期待値は、Σそうなる確率*値 みたいに表せるので、今回は値として決着までの試合回数xを全探索していく。
　それぞれのxについて、
　aがN回勝つ確率 * bがx-N回勝つ確率 * 勝敗の配置順(x-1箇所にN-1個並べる通り数、最後だけa勝ち確定なので-1) * 試合の回数
　と、bでその逆をやる。
・引き分けの考慮は最後にまとめてでいい。期待値DPの空振り遷移みたいのを掛けるんだけど、
　「どちらかの勝利回数が増える確率」の逆数 → どちらかの勝利回数が増える期待値
　と考えて、これは回数が1回増えるまでの期待値なので、
　全体に掛ければ試合決着までの期待値にできる。
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

void solve() {
    ll N, a, b, c;
    cin >> N >> a >> b >> c;

    // (引き分けを考えずに)a,bが勝つ確率
    mint p = (mint)a/(a+b);
    mint q = (mint)b/(a+b);
    ModTools<mint> mt(N*2);
    mint ans = 0;
    // x回目で決着が着く場合を全探索
    rep(x, N, 2*N) {
        // aがN回勝つ確率 * bがx-N回勝つ確率 * 勝敗の配置順(x-1箇所にN-1個並べる通り数、最後だけa勝ち確定なので-1) * 試合の回数
        ans += p.pow(N)*q.pow(x-N)*mt.nCr(x-1, N-1)*x;
        // bで逆もやる
        ans += p.pow(x-N)*q.pow(N)*mt.nCr(x-1, N-1)*x;
    }
    // 引き分けの考慮は最後にまとめてでいい
    // 「どちらかの勝利回数が増える確率」の逆数 → どちらかの勝利回数が増える期待値
    ans *= (mint)100/(a+b);
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
