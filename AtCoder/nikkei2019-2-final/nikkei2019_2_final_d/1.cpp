/*
参考：https://snuke.hatenablog.com/entry/2017/02/03/054210
　　　https://img.atcoder.jp/nikkei2019-2-final/editorial.pdf
ライブラリ整備：根付き木のハッシュ、木の重心
・記事で紹介されてたから解いたけど、大変。
　重心を使えばいいっていう考察も知らなきゃ出ないけど、
　2つの木を突き合わせながらDFS潜ってくのがまた大変で。
　2つのmapから、共通でないものだけ抽出するのに便利な関数とかないもんかね。
　あと重心の頂点が2つの木で合ってなくて辻褄が合わなくなる場合もあるので、
　おかしくなった時は全部false返して無効みたいにしたんだけど、
　全てを考慮できてる気がしなくて、祈るように投げるしかなかったな。
　結果通ったからいいけど、これでWAが出てたらもう諦めちゃう所だ…。
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

#include "graph/get_centroids.hpp"
#include "graph/TreeHash.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes1(N + 1), nodes2(N);
    rep(u, N) {
        ll v;
        cin >> v;
        v--;
        nodes1[u].eb(v);
        nodes1[v].eb(u);
    }
    rep(u, N - 1) {
        ll v;
        cin >> v;
        v--;
        nodes2[u].eb(v);
        nodes2[v].eb(u);
    }

    TreeHash th(N + 1);
    auto centroids1 = get_centroids(nodes1);
    auto centroids2 = get_centroids(nodes2);
    vector<ll> ans;
    for (auto r1 : centroids1) {
        for (auto r2 : centroids2) {
            auto hash1 = th.get_hash(nodes1, r1);
            auto hash2 = th.get_hash(nodes2, r2);
            vector<ll> curans;
            auto dfs = [&](auto &&f, ll u1, ll prv1, ll u2, ll prv2) -> bool {
                // 部分木の各ハッシュから、差分を見つける
                map<TreeHash::mint64, vector<ll>> C1, C2;
                vector<ull> keys;
                for (auto v1 : nodes1[u1]) {
                    if (v1 == prv1) continue;
                    C1[hash1[v1]].eb(v1);
                    keys.eb(hash1[v1]);
                }
                for (auto v2 : nodes2[u2]) {
                    if (v2 == prv2) continue;
                    C2[hash2[v2]].eb(v2);
                    keys.eb(hash2[v2]);
                }
                UNIQUE(keys);
                vector<ll> nxt1, nxt2;
                for (auto k : keys) {
                    ll sz1 = C1[k].size();
                    ll sz2 = C2[k].size();
                    if (sz1 == sz2 + 1 and nxt1.empty()) {
                        nxt1 = C1[k];
                    } else if (sz1 + 1 == sz2 and nxt2.empty()) {
                        nxt2 = C2[k];
                    } else if (sz1 == sz2) {
                        // OK
                    } else {
                        return false;
                    }
                }
                // 部分木サイズが同じなら、消された葉はもっと深い所にある
                if (nodes1[u1].size() == nodes2[u2].size()) {
                    if (nxt1.size() and nxt2.size()) {
                        // 候補の頂点v1は全て見に行く
                        for (auto v1 : nxt1) {
                            // ここはv2はどれでもいいはず(いずれも同型の部分木なので)
                            if (!f(f, v1, u1, nxt2[0], u2)) {
                                return false;
                            }
                        }
                        return true;
                    } else {
                        return false;
                    }
                // 部分木サイズ1つ小さいなら、ここに消された葉があるはず
                } else if (nodes1[u1].size() == nodes2[u2].size() + 1) {
                    if (nxt1.size() and nxt2.empty()) {
                        for (auto v1 : nxt1) {
                            // ここは葉であるはず
                            if (nodes1[v1].size() != 1) {
                                return false;
                            }
                            // 全て削除された候補になる
                            curans.eb(v1);
                        }
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            };
            if (dfs(dfs, r1, -1, r2, -1)) {
                ans = concat(ans, curans);
            }
        }
    }
    UNIQUE(ans);
    ans++;
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
