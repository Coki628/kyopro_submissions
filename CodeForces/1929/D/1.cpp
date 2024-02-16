/*
・終了後、なんとか自力AC！大変だった…。
・むずい木DP、数え上げ、パス、遷移元を更新しないように気にする木DP
・だいたいの方針は立ったけど、細かい所を中々詰め切れなかった。
　基本的には、今含んだdangerousな頂点の個数を管理しながら木DPなんだけど、
　そんなに簡単には行かない。色々整理していくと、
　親子で2個含んだ状態と、兄弟で2個含んだ状態は区別する必要がある。
　親子で2個ならそれより根側全てで1つも追加できないけど、
　兄弟で2個は1つ親側に戻れば1個とみなせるので、まだ追加できる。
　なんならこの兄弟間は(各部分木1個ずつなら)3個でも4個でもOKとなる。
　ただし今見ている頂点をdangerousにする場合は2個以上は不可。
　LCAと子孫2点みたいな感じで3個になっちゃうからね。
　これらを踏まえて的確に状態を持って遷移させるとうまくいく。
　(詳細はコード内コメントも参照)
　あと遷移元が絡む遷移を複数回やるので、遷移元に更新された値が使われないように、
　2乗の木DPみたく一時配列で値を逃がしておく必要がある。
　これもたまに出るんだけど、たまになのでだいたいもたつく…。
・強い人はこのくらいの木DPも典型の範疇として通すんだよなー。
　もっと経験値積んで、このくらいを迷いなく通せるようになんないと。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve(int testcase) {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    // dp[u][i] := 頂点uの部分木でdangerousな頂点が一番多いものがi個となる通り数(uの遷移後)
    auto dp = listnd(N, 3, (mint)0);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        // cur[i][j] := 頂点uの部分木でdangerousな頂点が一番多いものがi個、
        //              各部分木合わせた個数がj個(0,1,2以上)となるような通り数(uの遷移前)
        auto cur = listnd(3, 3, (mint)0);
        cur[0][0] = 1;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            auto nxt = listnd(3, 3, (mint)0);
            rep(i, 3) {
                rep(j, 3) {
                    rep(k, 3) {
                        // 既に2つ縦になってる箇所があったらそれ以上追加は無理
                        if (k == 2 and i > 0 or i == 2 and k > 0) continue;
                        // 逆に横はいくつあってもいいので2以上はまとめる
                        nxt[max(i, k)][min(j + k, 2LL)] += cur[i][j] * dp[v][k];
                    }
                }
            }
            cur = nxt;
        }
        rep(i, 3) {
            rep(j, 3) {
                // uをdangerousにしない
                dp[u][i] += cur[i][j];
                // uをdangerousにする(横が2個以上あるとこれは無理)
                if (j < 2) {
                    dp[u][max(i, j + 1)] += cur[i][j];
                }
            }
        }
    };
    dfs(dfs, 0, -1);
    mint ans = sum(dp[0]);
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
    rep(t, T) solve(t);

    return 0;
}
