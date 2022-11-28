/*
参考：https://atcoder.jp/contests/abc279/editorial/5284
・公式解の方針
・UF応用、番号の対応
・vectorとマージテクでやる場合、箱の元index番号そのものを使ったけど、
　これだと代わりにUFのグループ番号を使う感じ。
　まあでも箱が空の時に場合分けが必要だったり、
　結局番号の対応がとてもややこしいことに変わりはなさそう。
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
    ll N, Q;
    cin >> N >> Q;

    // ids[i] = 位置iにある箱のUF番号
    // rev[i] = UF番号iの箱がある位置
    vector<ll> ids(N+Q, -1), rev(N+Q, -1);
    UnionFind uf(N+Q);
    ll k = N;
    rep(i, N) {
        ids[i] = i;
        rev[ids[i]] = i;
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, y;
            cin >> x >> y;
            x--; y--;

            if (ids[y] == -1) {
                continue;
            } elif (ids[x] == -1) {
                ids[x] = ids[y];
                rev[ids[x]] = x;
                ids[y] = -1;
            } else {
                assert(not uf.same(ids[x], ids[y]));
                ids[x] = uf.merge(ids[x], ids[y]);
                rev[ids[x]] = x;
                ids[y] = -1;
            }
        } elif (op == 2) {
            ll x;
            cin >> x;
            x--;

            if (ids[x] == -1) {
                ids[x] = k;
                rev[ids[x]] = x;
            } else {
                ids[x] = uf.merge(ids[x], k);
                rev[ids[x]] = x;
            }
            k++;
        } elif (op == 3) {
            ll a;
            cin >> a;
            a--;

            print(rev[uf.find(a)] + 1);
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
