/*
参考：https://snuke.hatenablog.com/entry/2017/02/03/054210
　　　https://img.atcoder.jp/nikkei2019-2-final/editorial.pdf
　　　https://atcoder.jp/contests/nikkei2019-2-final/submissions/17078614
ライブラリ整備：根付き木のハッシュ、全方位木DPへの適用
・もう1つの方針。むげんさんの提出がとても参考になった。
　ハッシュの作り方として、子の2乗和と固定値の素数1つのみを使う方法を取ると、
　容易に全方位への拡張が可能になる。(ただしこのハッシュでどこまで安全なのかは分からん。)
　これを使えば、全ての頂点を根とした全体のハッシュが高速に取得できるし、
　辺を1本追加/削除した状態のハッシュも容易に再現できる。
　(辺1本であれば、その遷移分の2乗和1回を足し引きすればいい。)
・これやってて思ったけど、やっぱNyaanさんみたいにHashクラス作った方がスッキリするな。やってみるかー。
・作った。Hashクラスというか、ModInt64クラスだな。
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

#include "graph/ReRooting.hpp"
#include "combinatorics/ModInt64.hpp"

void solve() {
    ll N;
    cin >> N;

    const ull mod = (1ull << 61ull) - 1;
    using mint64 = ModInt64<mod>;
    mint64 p = MOD;
    // DP遷移
    // hash[u] += pow(hash[v] + p, 2);
    auto f1 = [&](mint64 a, mint64 b) -> mint64 {
        return a + b;
    };
    auto f2 = [&](mint64 a, mint64 v) -> mint64 {
        return (a + p).pow(2);
    };
    auto rr1 = get_rerooting(N + 1, f1, f2, (mint64)0, (mint64)0);
    auto rr2 = get_rerooting(N, f1, f2, (mint64)0, (mint64)0);

    vvi nodes1(N + 1), nodes2(N);
    rep(u, N) {
        ll v;
        cin >> v;
        v--;
        nodes1[u].eb(v);
        nodes1[v].eb(u);
        rr1.add_edge(u, v, 0);
    }
    rep(u, N - 1) {
        ll v;
        cin >> v;
        v--;
        nodes2[u].eb(v);
        nodes2[v].eb(u);
        rr2.add_edge(u, v, 0);
    }

    auto hash1 = rr1.build();
    auto hash2 = rr2.build();

    map<mint64, vector<ll>> ok;
    rep(i, N + 1) {
        ok[hash1[i]].eb(i);
    }
    vector<ll> ans;
    rep(u, N) {
        // 頂点uから消された根に戻る辺を復元
        mint64 h = (hash2[u] + p).pow(2);
        // そういう形の木が存在するならここは候補になる
        if (ok.count(h)) {
            for (auto v : ok[h]) {
                ans.eb(v);
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
