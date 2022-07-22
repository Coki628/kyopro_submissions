/*
参考：https://twitter.com/kude_coder/status/1550163652707495936
・自力ならず。これはまあしゃあない。こういうの解けるようになりたいけど。
・木DP、パス、XORの性質、式変形、LCA、マージテク
・ある2頂点u,vのパスのXOR = 0 を式にすることを考えると、根をrとして、
　r~u ^ r~v ^ A[lca(u,v)] = 0 のようになる。これは普通にLCA使って
　加減算でパスのコストを取る時の応用になるけど、頂点属性なこともあって、
　共通部分が引かれた後、LCA部分だけ足しなおすみたいな形になる。
　これを式変形して r~u = r~v ^ A[lca(u,v)] のようにすると、
　今までに追加されたパスのxor集合の中に「今回追加するxor集合のいずれか^A[今見ている頂点]」
　と等しいものがあるか？のチェックにできる。
　これはsetで今までに見たxor集合を管理して、
　マージテクで小さい側の集合でループ回すようにすれば木DPできる。
・でもそもそもの、適当な頂点を根としても最適になるかってのが非自明なんだよなー。
　なんか根にする頂点によって、切らなきゃいけない場所変わっちゃう気がするんだけどね。
　制約の木DPみから、いけるんじゃないかと信じて突き進むしかないんだよぁ…。
・ちなみにHashSet使ってみてもそれほど速くならなかった。0.42秒→0.31秒。
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
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> acc(N);
    ll ans = 0;
    auto dfs = [&](auto&& f, ll u, ll prv) -> set<ll> {
        if (prv != -1) {
            acc[u] ^= acc[prv] ^ A[u];
        }
        set<ll> res = {acc[u]};
        bool removed = false;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            auto tmp = f(f, v, u);
            // 削除済ならここはもうやらない(けど部分木を見る必要はあるのでbreakはしない)
            if (removed) continue;
            if (res.size() < tmp.size()) swap(res, tmp);
            bool ok = true;
            for (auto rtov : tmp) {
                // rtou = rtov ^ A[u] となるようなものがあればこの頂点を消す
                if (res.count(rtov^A[u])) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                res.insert(ALL(tmp));
            } else {
                ans++;
                res.clear();
                removed = true;
            }
        }
        return res;
    };
    dfs(dfs, 0, -1);
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
