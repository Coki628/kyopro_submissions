/*
参考：https://twitter.com/nawawan_kpr/status/1534216202150502400
・自力ならず。。
　E粘着しないでこっち考えてたら解けたかもと思ってしばらく考えたけどダメだった…。
・順列、サイクル、Functional Graph、重複のある円環、ロリハ
・この問題、値がdistinctならサイクル長でLCM取るだけだと思うんだけど、
　文字列のサイクルには多数の同じ文字が含まれるからどうするか悩んだ。
　結局、1文字ずつずらしていって最初に合った所でいいみたいなんだけど、
　全体でLCM取る都合上、最初に合った所より次に合う所のが都合いいこととかない？
　って思ってしまって、この方針は棄却しちゃったんだよな。
　でも、例えば最初に合った場所が3だったとして、次の4でもぴったり合うなんてことは、
　多分あり得ないんだよね。この3が小さいサイクルみたいになって、
　次に合うのは(多分)絶対6になる。もし4で合うようならその前に1で合ってない？みたいな。
　なんかそうとも限らない気がしちゃったんだけど、そうなんだよね…。
・あと文字列の一致判定にロリハ使った。円環1周チェックするので文字列2倍にしてやる。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vector<bool> visited(N);
    vector<string> adj;
    rep(i, N) {
        if (not visited[i]) {
            string cur;
            ll j = i;
            while (not visited[j]) {
                cur += S[j];
                visited[j] = true;
                j = P[j];
            }
            adj.eb(cur);
        }
    }
    ll M = adj.size();

    ll ans = 1;
    RollingHash rh;
    rep(i, M) {
        ll n = adj[i].size();
        adj[i] += adj[i];
        auto table = rh.build(adj[i]);
        rep(l, 1, n+1) {
            ll r = l + n;
            if (rh.query(table, l, r) == rh.query(table, 0, n)) {
                ans = lcm(ans, l);
                break;
            }
        }
    }
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
