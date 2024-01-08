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

void solve() {
    ll N;
    cin >> N;

    ull p = MOD;
    const ull mod = (1ull << 61ull) - 1;
    using uint128_t = __uint128_t;
    auto add = [&](ull a, ull b) -> ull {
        if ((a += b) >= mod) a -= mod;
        return a;
    };
    auto mul = [&](ull a, ull b) -> ull {
        uint128_t c = (uint128_t)a * b;
        return add(c >> 61, c & mod);
    };
    // DP遷移
    // hash[u] = add(hash[u], mul(hash[v] + p, hash[v] + p));
    auto f1 = [&](ull a, ull b) -> ull {
        return add(a, b);
    };
    auto f2 = [&](ull a, ull v) -> ull {
        return mul(a + p, a + p);
    };
    auto rr1 = get_rerooting(N + 1, f1, f2, 0ULL, 0ULL);
    auto rr2 = get_rerooting(N, f1, f2, 0ULL, 0ULL);

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

    map<ull, vector<ll>> ok;
    rep(i, N + 1) {
        ok[hash1[i]].eb(i);
    }
    vector<ll> ans;
    rep(u, N) {
        // 頂点uから消された根に戻る辺を復元
        ull h = mul(hash2[u] + p, hash2[u] + p);
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
