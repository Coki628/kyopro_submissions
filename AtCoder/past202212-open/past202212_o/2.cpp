/*
・自力ならず。
・サイクルシフト、区間桁サイクルシフト・区間XOR取得、遅延セグ木
・ちょっと見て、遅延セグ木乗らないかな、と思って色々頑張って乗らなかった。。
　区間桁サイクルシフトを、回転回数を区間加算として持って、
　回転させてからXORできれば、と思ったんだけど、
　最下段はいけたんだけど、2段目以降の回転がうまくできなかった。
　下で適切に回転させても、2段目は回転させる前の情報しか持ってないし、みたいな。
　で、正解の方針なんだけど、回転後の情報も全部先に作って持っておけば良かった。
　これだと適切な順序でちゃんと演算ができる。
・あとどうでもいいけど1WAのバグ取り自力は諦めた。
　MOD取った後の区間境界がおかしくなってた。ありがち…。
・セグ木に乗せるの最初vectorで投げたけど、arrayにしたらやっぱ速くなった。0.42->0.21秒。
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

#include "datastructure/LazySegmentTree.hpp"

void solve() {
    ll N, D;
    cin >> N >> D;
    vector<ll> A(N);
    cin >> A;

    auto f = [D](const array<ll, 9> &a, const array<ll, 9> &b) -> array<ll, 9> {
        array<ll, 9> res = {};
        rep(i, D) {
            res[i] = a[i] ^ b[i];
        }
        return res;
    };
    auto g = [D](const array<ll, 9> &a, ll b) -> array<ll, 9> {
        if (b == 0) return a;
        array<ll, 9> res = {};
        rep(i, D) {
            res[i] = a[(i + b) % D];
        }
        return res;
    };
    auto h = [](ll a, ll b) { return a + b; };
    const array<ll, 9> T = {};
    const ll E = 0;
    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        array<ll, 9> arr = {};
        auto s = zfill(tostr(A[i]), D);
        Deque<char> cur(ALL(s));
        rep(b, D) {
            string t;
            for (auto c : cur) {
                t += c;
            }
            arr[b] = toint(t);
            cur.eb(cur.pop_front());
        }
        seg.set(i, arr);
    }
    seg.build();

    ll Q;
    cin >> Q;
    ll offset = 0;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            offset += x;
        } else if (op == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;
            l = (l + offset) % N;
            r = (r + offset) % N;
            // l > r だと1WA [0,N)が[0,0)になる
            if (l >= r) {
                seg.update(l, N, y);
                seg.update(0, r, y);
            } else {
                seg.update(l, r, y);
            }
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
            l = (l + offset) % N;
            r = (r + offset) % N;
            if (l >= r) {
                ll res = seg.query(l, N)[0] ^ seg.query(0, r)[0];
                print(res);
            } else {
                ll res = seg.query(l, r)[0];
                print(res);
            }
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
