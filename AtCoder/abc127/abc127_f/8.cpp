/*
・方針生えたけど合ってるか分からんからやってみた。無事AC。
・クエリ先読み、座圧BITで中央値、BIT2本で個数と総和
・題意をよく読み解くと、最小値を取るxとして中央値が欲しくなる。
　これはクエリ先読みと座圧BITで取れる。
・最小値を取るxだけでなく、その時の値f(x)も必要なので、それをどうするか考える。
　2次元座標上で欲しい面に色塗りする考察をやると、欲しい三角形部分2つが出てくるので、
　これは個数と総和を持っておけば、足し引きして求まる。
・あとbはほぼブラフなので別途持って足すだけ。
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
    ll Q;
    cin >> Q;
    vector<array<ll, 3>> qs;
    Compress<ll> cp;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll a, b;
            cin >> a >> b;
            qs.pb({op, a, b});
            cp.add(a);
        } else {
            qs.pb({op, -1, -1});
        }
    }
    cp.build();
    ll N = cp.size();

    BIT<ll> bitcnt(N), bitsm(N);
    ll bsm = 0, acnt = 0;
    for (auto [op, a, b] : qs) {
        if (op == 1) {
            bitcnt.add(cp[a], 1);
            bitsm.add(cp[a], a);
            acnt++;
            bsm += b;
        } else {
            ll i = bitcnt.bisearch_fore(0, N - 1, ceil(acnt, 2LL));
            ll x = cp.unzip(i);
            ll fx = bitcnt.query(0, i) * x - bitsm.query(0, i) +
                    bitsm.query(i + 1, N) - bitcnt.query(i + 1, N) * x + bsm;
            print(mkp(x, fx));
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
