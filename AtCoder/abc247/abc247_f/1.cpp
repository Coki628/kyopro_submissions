/*
・なんとか自力AC！時間迫る中、通し切れたのは偉い。
・順列、グラフに帰着、Functional Graph、辺被覆、リュカ数
・まず順列並べ替えなのでFunctional Graphにする。
　で、UFでつないで、連結成分毎に考えて最後に掛け合わす。
　成分内で選ぶ通り数は、連結の順序で見て行くと、
　1つ先か2つ先に遷移するフィボナッチみたいなDPにできる。
　最後閉路で微妙に困るので、1番目～最後、1番目～最後から2番目、2番目～最後の3つに分けて考えた。
　一応お気持ちは、前2つは1番目を使った通り数、3つ目は使わなかった通り数。
　でもこれで本当に重複がないかとかはもう時間ないし祈るしかなかった。
・終了後、TLの色々を見た。こういうの辺被覆って言うらしい。
　パス被覆みたいだけど微妙に違うね。
　「そのグラフの全ての点がその辺集合に含まれているもの」って感じ、多分。
　で、連結成分(今回は全部円環みたいなサイクル)毎にこれを数える。
　なんか小さいケースで愚直に列作ってOEISするとリュカ数ってのが出てくる。
　漸化式の定義も出てくる。これ調べてれば祈りながら出すことはしなくてもよかったね。
　(まあでも地味に愚直解作るの面倒そうだし、しょうがなかったかも。)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    rep(i, N) {
        A[i]--;
        B[i]--;
    }
    vector<ll> btoi(N);
    rep(i, N) {
        btoi[B[i]] = i;
    }
    UnionFind uf(N);
    rep(u, N) {
        ll v = btoi[A[u]];
        uf.merge(u, v);
    }

    // dp[i] := 最後にi番目の辺を使って、辺被覆となる通り数(サイクル未考慮)
    vector<mint> dp(N+1);
    dp[1] = 1;
    rep(i, 2, N+1) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    mint ans = 1;
    for (auto r : uf.get_roots()) {
        ll sz = uf.size(r);
        // 最後のサイクルになる所を考慮した通り数を掛ける
        ans *= dp[sz] + dp[sz-1]*2;
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
