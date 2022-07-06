/*
・JOI埋め
・自力AC！
・座圧、二分探索、再帰全探索
・色々考えると、実は(次の文字のうち)両隣以外は候補として考えなくていいと分かる。
　これが分かれば、1回の選択肢が2通りで4回やるだけなので、
　全探索しても16通りで問題ない。隣の位置がどこかは二分探索で探せる。
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
    ll N;
    cin >> N;
    vector<ll> P(N);
    vector<char> S(N);
    Compress<ll> cp;
    rep(i, N) {
        cin >> P[i] >> S[i];
        cp.add(P[i]);
    }

    ll Q;
    cin >> Q;
    vector<pll> qs;
    rep(_, Q) {
        ll s, t;
        cin >> s >> t;
        qs.eb(s, t);
        cp.add(s), cp.add(t);
    }
    cp.build();
    ll M = cp.size();

    vector<Accumulate<ll>> acc(4, {M});
    rep(i, N) {
        if (S[i] == 'J') {
            acc[0].set(cp[P[i]], 1);
        } elif (S[i] == 'O') {
            acc[1].set(cp[P[i]], 1);
        } elif (S[i] == 'I') {
            acc[2].set(cp[P[i]], 1);
        } elif (S[i] == 'G') {
            acc[3].set(cp[P[i]], 1);
        }
    }
    rep(i, 4) acc[i].build();

    for (auto q : qs) {
        ll s, t;
        tie(s, t) = q;
        auto rec = [&](auto&& f, ll i, ll j, ll dist) {
            if (i == 4) {
                return dist + abs(cp.unzip(j)-t);
            }
            ll res = INF;
            ll l = acc[i].bisearch_back(0, j, 1);
            if (l != -1) {
                chmin(res, f(f, i+1, l, dist + abs(cp.unzip(j)-cp.unzip(l))));
            }
            ll r = acc[i].bisearch_fore(j, M-1, 1);
            if (r != -1) {
                chmin(res, f(f, i+1, r, dist + abs(cp.unzip(j)-cp.unzip(r))));
            }
            return res;
        };
        ll res = rec(rec, 0, cp[s], 0);
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
