/*
・ライブラリ整備：抽象化Beats
・区間chmin・1点取得、復元、Beats
・復元付きをやってみたけど問題なく動作。
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

#include "segment/AbstructBeats.hpp"

struct Node {
    using T = ll;
    using F = array<ll, 3>;
    T sm = 0, sz = 1, g1 = 0, id = -1;
    T g2 = -INF, gc = 1, upd = 0;
    Node() {}
    Node(T n) : sm(n), g1(n) {}

    void update(Node& l, Node& r) {
        sm = l.sm + r.sm;
        sz = l.sz + r.sz;

        if (l.g1 == r.g1) {
            g1 = l.g1;
            g2 = max(l.g2, r.g2);
            gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            g1 = f ? l.g1 : r.g1;
            gc = f ? l.gc : r.gc;
            g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }
    }

    void push_update(T x, int i) {
        sm = x * sz;
        g1 = x;
        g2 = x;
        gc = sz;
        upd = x;
        id = i;
    }

    void push_min(T x, int i) {
        sm += (x - g1) * gc;
        g1 = x;
        id = i;
    }

    void push(Node& l, Node& r) {
        if (upd != 0) {
            l.push_update(upd, id);
            r.push_update(upd, id);
            upd = 0;
        }

        // 親のmax < 子のmaxなら子のmaxを更新(chmin)
        if (g1 < l.g1) l.push_min(g1, id);
        if (g1 < r.g1) r.push_min(g1, id);
    }

    bool apply(F p) {
        auto [cmd, x, i] = p;
        if (cmd == 1) {
            // 2nd max以下なら変化量が分からないので更新しない
            if (x <= g2) {
                return false;
            // 2nd max < x < max なら変化量が分かるのでg1を更新する
            } elif (g2 < x and x < g1) {
                push_min(x, i);
            }
        } elif (cmd == 2) {
            push_update(x, i);
        }
        return true;
    }
};

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    reverse(ALL(A));
    reverse(ALL(B));
    AbstructBeats<Node, ll, array<ll, 3>> seg(vector<ll>(N+1, INF));
    seg.apply(0, 1, {2, 0, 0});
    rep(i, N) {
        ll l = i - B[i];
        ll r = l + A[l];
        ll val = INF, j = -1;
        seg.query(i, i+1, [&](Node& a) { val = a.sm, j = a.id; });
        if (val == INF) continue;
        seg.apply(l+1, r+1, {1, val+1, i});
    }
    ll i = N;
    vector<ll> ans = {N-i};
    while (i > 0) {
        ll val = INF, j = -1;
        seg.query(i, i+1, [&](Node& a) { val = a.sm, j = a.id; });
        if (val == INF) {
            print(-1);
            return;
        }
        ans.eb(N-j);
        i = j;
    }
    ans.pop_back();
    reverse(ALL(ans));
    print(ans.size());
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
