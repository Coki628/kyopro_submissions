/*
・これはWA。
・自力から解説見てちょっといじった後なんだけど、何で通らないのか考えた。
　正解の方針、結局[0]しか使わないし毎回サイクルさせる訳だから、
　前計算配列持つのもその場で陽に回すのも変わらなくない？って思って。
　色々動かしてみると、セグ木の2段目に行った時に、演算が
　XORしてからサイクルシフト、みたいになってて、
　サイクルシフトしてからXOR、になってないようだった。
　確かに前計算配列持つと、例えば[2]には下段のやつを2回回した後に
　XORされたやつが入ってるはずだから、これなら合う訳だ。むずい。
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

    auto f = [](ll a, ll b) -> ll {
        return a ^ b;
    };
    auto g = [D](ll a, ll b) -> ll {
        if (b == 0) return a;
        auto s = zfill(tostr(a), D);
        Deque<char> cur(ALL(s));
        rep(_, b % D) {
            cur.eb(cur.pop_front());
        }
        string t;
        for (auto c : cur) {
            t += c;
        }
        return toint(t);
    };
    auto h = [](ll a, ll b) { return a + b; };
    const ll T = 0;
    const ll E = 0;
    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, A[i]);
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
                ll res = seg.query(l, N) ^ seg.query(0, r);
                debug(seg.query(0, r));
                print(seg);
                print(res);
            } else {
                ll res = seg.query(l, r);
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
