/*
・自力AC！
・2次元累積和
・これ絶対大変な方針引いてるよなーって思いながら実装。
　まとめて処理できる「全部」以外の部分は8箇所に区別できる。
　計9箇所を丁寧に考えながら整理すると、答えが出る。
・やっぱり大変だった。1つの2次元累積和とみなして4点の足し引きにすれば、
　手前側の端数を考えなくて良くなるので大分楽になるようだった。。
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<string> grid(N);
    cin >> grid;

    Accumulate2D<ll> acc(N, N);
    rep(i, N) {
        rep(j, N) {
            if (grid[i][j] == 'B') {
                acc.set(i, j, 1);
            }
        }
    }
    acc.build();
    ll allsm = acc.query(0, 0, N, N);

    rep(_, Q) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        c++, d++;

        ll ma = a % N == 0 ? N : a % N;
        ll mb = b % N == 0 ? N : b % N;
        ll mc = c % N;
        ll md = d % N;
        a += (N - a % N) % N;
        b += (N - b % N) % N;
        c -= mc;
        d -= md;
        ll hlen = c - a;
        ll wlen = d - b;
        assert(hlen % N == 0);
        assert(wlen % N == 0);
        ll hcnt = hlen / N;
        ll wcnt = wlen / N;
        ll allcnt = hcnt * wcnt;
        ll res = 0;
        res += acc.query(ma, mb, N, N);
        res += acc.query(ma, 0, N, N) * wcnt;
        res += acc.query(ma, 0, N, md);
        res += acc.query(0, mb,  N,N) * hcnt;
        res += acc.query(0, mb, mc, N);
        res += acc.query(0, 0, mc, N) * wcnt;
        res += acc.query(0, 0, N, md) * hcnt;
        res += acc.query(0, 0, mc, md);
        res += allsm * allcnt;
        print(res);
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
