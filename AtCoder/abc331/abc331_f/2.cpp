/*
・もう1つの方針。セグ木に物乗せるの慣れてたらこっちのが簡単だと思う。
・ロリハ、1点更新、回文判定、セグ木
・ハッシュ自体はマージがO(1)で可能なので、必要な情報(ハッシュ本体と長さ)を持てばセグ木に乗る。
　セグ木の各ノードに持たせてるのは長さ1のハッシュで、これは値そのものなので、更新も簡単。
　回文判定はセグ木に必要な添字を渡したいので、ロリハ内から必要な部分をコピペしてきた。
・ちなみにロリハ本体をBIT版に改造するより、こっちのがちょっと速かった。0.11秒。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    RollingHash rh;
    struct Node {
        ull hash;
        int sz;
    };
    auto f = [&](const Node &a, const Node &b) {
        Node res;
        res.hash = rh.combine(a.hash, b.hash, b.sz);
        res.sz = a.sz + b.sz;
        return res;
    };
    const Node T = {0, 0};

    auto seg = get_segment_tree(N, f, T);
    auto segrev = get_segment_tree(N, f, T);
    auto Srev = reversed(S);
    rep(i, N) {
        seg.set(i, {(ull)S[i], 1});
        segrev.set(i, {(ull)Srev[i], 1});
    }
    seg.build();
    segrev.build();
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            char c;
            cin >> x >> c;
            x--;
            seg.update(x, {(ull)c, 1});
            segrev.update(N - x - 1, {(ull)c, 1});
        } else {
            ll l, r;
            cin >> l >> r;
            l--;

            int n = N;
            int len = r - l;
            int sl = len % 2 == 0 ? l + len / 2 : l + len / 2 + 1;
            int sr = r;
            int tl = n - (l + len / 2);
            int tr = n - l;
            auto hash = seg.query(sl, sr).hash;
            auto hashrev = segrev.query(tl, tr).hash;
            YesNo(hash == hashrev);
        }
    }
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
