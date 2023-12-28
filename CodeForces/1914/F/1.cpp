/*
参考：https://twitter.com/shobonvip/status/1737160780683096360
　　　https://codeforces.com/blog/entry/123530
・自力ならず。これも色々大変。
・木グラフ、マッチング、DFS2回、根から決める
・むずい。そもそも考察も自力では出ず。
　本番Gに言ったけど、こっちにリソース割いても解けなかっただろう。
　気持ち的にどうしたらいいかはしょぼんさんのツイートを参考に。
・部分木サイズを先に求めておいて、根側から見て行く。(そもそもこの方針に行ける気がしない)
　今回は直系の関係以外でペアを組むとのことで、
　これは上から見て、一番大きい部分木が大き過ぎなければ、
　(奇数の1余りを無視すれば)適当に全部組める。
　一辺が長すぎなければ三角形が作れるアレみたいな感じに。
　で、ここで余ってしまった時は、使用済みの個数を持ってその最大の部分木に潜る。
　それ以外の部分木は全て使い切ったとみなしていい。
　(この辺の考察も自力だと出なそう…。)
　で、上の階層で減らした分を調整しつつ、次の階層でも同じようにマッチングする。
・考察はこれでいいんだけど、実装の細部調整が全然できなくて、
　諦めて公式解説のお手本コードから(本質部分は)ほぼ写経みたいになった。
　ぐっちゃぐちゃだったのがめちゃ簡潔にまとまってすごい。
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
    vector<ll> P(N - 1);
    vvi nodes(N);
    rep(i, N - 1) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i + 1);
    }

    vector<ll> sz(N, 1);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        vector<pll> vec;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 0, -1);

    ll ans = 0;
    auto dfs2 = [&](auto &&f, ll u, ll prv, ll done) -> void {
        if (done == sz[u] - 1) return;
        assert(done < sz[u]);
        vector<pll> vec;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            vec.eb(sz[v], v);
        }
        if (vec.size()) {
            sort(ALL(vec));
            ll total = sz[u] - 1;
            ll mx = vec.back().first;
            ll others = total - mx;
            // 親側で済んでいるものはmxに当てる方ががいい
            if (mx - done <= others) {
                // othersが足りるならここで全消しできる
                ans += (total - done) / 2;
            } else {
                // できないならothersをあるだけ使って減らすとする
                // (この時、mxも同数減っているので、これが次階層でのdoneに足される)
                ans += others;
                // 今まで消した分 + 今回消した分 - 1(vec.back().second自身は次階層には含めないので)
                f(f, vec.back().second, u, max(done + others - 1, 0LL));
            }
        }
    };
    dfs2(dfs2, 0, -1, 0);
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
