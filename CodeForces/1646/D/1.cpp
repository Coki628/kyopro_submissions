/*
参考：https://twitter.com/kude_coder/status/1499804005362696192
・自力ならず。
・木DP、復元
・状況をまとめると、隣接した頂点を両方「良い頂点」とすることはできず(N=2を除く)、
　良い頂点とする場合は隣接頂点数、しない場合は1を自身の値にするのが最善(だと信じる)。
　ここまでは考え至ったんだけど、なんか貪欲ぐちゃぐちゃやって終わった。。
・正解はDPだった。しない場合は連続できて、どこに良い頂点を持っていくかを選べるので、
　dp[u][0/1] := 頂点uを良い頂点にしたか
　みたいな2状態でDPすれば最善を取れる。ここまでならまあ辿り着けるべきだったと思うけど、
　もう一段階、復元がある。木DPの復元って初めてやったと思う。
　やり方は、基本的には普通のDP復元みたいなことをするんだけど、
　対象が木なので、逆を辿る方法とかが結構違う。木DPがDFSの戻り側で確定していくので、
　DP時にその頂点への遷移でどっちの状態使ったかを覚えておいて、
　復元時には、再度DFSで今度は行き側で答えを確定していく感じに進める。
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    if (N == 2) {
        print(mkp(2, 2));
        print(mkp(1, 1));
        return;
    }

    struct Node {
        ll cnt = 0, sm = 0;
        Node &operator+=(const Node &a) {
            cnt += a.cnt;
            sm += a.sm;
            return *this;
        }
    };
    auto compare = [&](Node a, Node b) -> bool {
        if (a.cnt != b.cnt) {
            return a.cnt > b.cnt;
        } else {
            return a.sm < b.sm;
        }
    };
    auto dp = list2d(N, 2, Node{0, 0});
    vector<ll> nxt(N, -1);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            ll res = 1-compare(dp[v][0], dp[v][1]);
            // 遷移先を覚えておく
            nxt[v] = res;
            dp[u][0] += dp[v][res];
            dp[u][1] += dp[v][0];
        }
        // この頂点を使わない
        dp[u][0].sm++;
        // この頂点を使う
        dp[u][1].cnt++;
        dp[u][1].sm += nodes[u].size();
    };
    dfs(dfs, 0, -1);

    vector<ll> ans(N);
    auto dfs2 = [&](auto&& f, ll u, ll prv, ll k) -> void {
        if (k == 0) {
            ans[u] = 1;
        } else {
            ans[u] = nodes[u].size();
        }
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            if (k == 0) {
                f(f, v, u, nxt[v]);
            } else {
                f(f, v, u, 0);
            }
        }
    };
    ll res = 1-compare(dp[0][0], dp[0][1]);
    print(mkp(dp[0][res].cnt, dp[0][res].sm));
    dfs2(dfs2, 0, -1, res);
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
