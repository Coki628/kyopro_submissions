/*
・クエリ先読み、座圧、BITにぶたん
・こっちもやってみた。まあどっちにしてもクエリ2の処理は
　決め打ちにぶたん*BITにぶたんみたいになるのでゴチャゴチャするんだけど、
　それでもBITが使い慣れてる分やっぱこっちのがやりやすかったかもしんない。
　クエリ先読みで座圧する手間を差し引いても。
　あと速度はやっぱ平衡二分探索木より速いよ。1.69秒。
・公式解説見たけど、BIT区間和取れるんだから、クエリ2って和取るだけじゃん。。
　なんでそんな難しく考えてしまったのか…。さすがにこれだと速くて、0.49秒。
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto P = LIST(N);

    Compress<ll> cp;
    rep(i, N) {
        cp.add(P[i]);
    }
    vector<tuple<ll, ll, ll>> qs;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll a, x;
            cin >> a >> x;
            a--;
            qs.pb({op, a, x});
            cp.add(x);
        } elif (op == 2) {
            ll a;
            cin >> a;
            a--;
            qs.pb({op, a, -1});
        } else {
            ll r;
            cin >> r;
            qs.pb({op, r, -1});
        }
    }

    cp.build();
    ll M = cp.size();
    P = cp.zip(P);
    vector<ll> ptoi(M, -1);
    BIT<ll> bit(M);
    rep(i, N) {
        ptoi[P[i]] = i;
        bit.add(P[i], 1);
    }
    rep(i, Q) {
        if (get<0>(qs[i]) == 1) {
            get<2>(qs[i]) = cp.zip(get<2>(qs[i]));
        }
    }

    rep(i, Q) {
        ll op, a, b;
        tie(op, a, b) = qs[i];
        if (op == 1) {
            bit.add(P[a], -1);
            ptoi[P[a]] = -1;
            P[a] = b;
            ptoi[P[a]] = a;
            bit.add(P[a], 1);
        } elif (op == 2) {
            // ll r = bisearch_min(0, N, [&](ll x) {
            //     ll px = bit.bisearch_fore(0, M-1, x);
            //     return P[a] <= px;
            // });
            // print(N-r+1);
            ll sm = bit.query(P[a], M);
            print(sm);
        } else {
            ll p = bit.bisearch_back(0, M-1, a);
            print(ptoi[p]+1);
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
