/*
参考：https://atcoder.jp/contests/abc223/editorial
・abc223_g
・自力ならず。そもそも全方位の方針が生えなかった。完全にマッチングに頭持ってかれてた。
・全方位木DP、二部マッチング
・よくよく話を整理すると、全ての頂点について同じ問いを求めるような題意なので、
　確かに全方位がハマる。けどこれ気付きにくく作るのうまいなぁと。。
・何となく、全体でのマッチングを求めてから、ちょっとずつ何かをずらして
　その頂点を減らしてもいいかを確認してく、みたいな方針に着地したくなる。
　(実際、別解として紹介されてたフローで解くやつがそんな感じ。)
・さて、全方位できると分かってもちょっと簡単じゃない。
　なんか実際のマッチング数を状態に持つDPやろうとすると、結構全方位への拡張がつらそう。
　実はその頂点の白黒だけ持って根まで戻ってきて、根がペアに関わったかの判定だけでいいので、
　これだとすごくシンプルな状態と遷移になって全方位にも簡単に乗る。
　まじでマッチング数を状態に持つと全方位できるのかな。。
　(ぐちゃぐちゃになりそうだったから試してない。)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/rerooting.hpp"

const auto f1 = [](ll a, ll b) -> ll {
    return a | b;
};
const auto f2 = [](ll a, ll v) -> ll {
    return 1-a;
};

void solve() {
    ll N;
    cin >> N;
    // vvi nodes(N);
    auto rr = get_rerooting(N, f1, f2, 0LL, 0LL);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        // nodes[u].eb(v);
        // nodes[v].eb(u);
        rr.add_edge(u, v, 1);
    }

    auto res = rr.build();
    ll ans = 0;
    rep(i, N) {
        if (res[i] == 0) {
            ans++;
        }
    }
    print(ans);

    // ll ans = 0;
    // rep(i, N) {
    //     vector<ll> dp(N);
    //     auto dfs = [&](auto&& f, ll u, ll prv) -> void {
    //         ll res = 0;
    //         for (ll v : nodes[u]) {
    //             if (v == prv) continue;
    //             f(f, v, u);
    //             dp[u] |= 1-dp[v];
    //         }
    //     };
    //     dfs(dfs, i, -1);
    //     if (dp[i] == 0) ans++;
    // }
    // print(ans);
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
