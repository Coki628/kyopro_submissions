/*
・終了後自力AC！本番中詰め切れず…。
・優先度付きキューで貪欲、UF
・値が大きいので、同一視できる部分のUFで管理しながらプリキューで貪欲に。
　なんだけど、まーつらかった。苦しんで苦しんで、通し切った感じだ。
　PASTバチャ本番後半の疲弊した精神力じゃ、時間があったとして通せたかどうか…。
　こういうしんどい系をしんどくないように通し切るにはどうしたらいいもんかね。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    auto A = LIST(N);

    if (N == 1) {
        A[0] += K * M;
        print(A);
        return;
    }
    PriorityQueue<pll, vector<pll>, greater<pll>> que;
    vector<ll> D(N);
    rep(i, N) {
        D[i] = A[i] / K;
        que.push({D[i], i});
    }
    UnionFind uf(N);
    ll cur = M;
    while (que.size() >= 2) {
        auto [d1, i1] = que.pop();
        auto [d2, i2] = que.pop();
        ll res = bisearch_min(-1, cur + 1, [&](ll x) {
            return d1 + x >= d2;
        });
        ll sz = uf.size(i1);
        // 足りない時は使えるだけ使ってから打ち切り
        if (res == cur + 1) {
            ll each = cur / sz;
            cur -= each * sz;
            D[uf.find(i1)] += each;
            break;
        }
        if (cur < res * sz) {
            ll each = cur / sz;
            cur -= each * sz;
            D[uf.find(i1)] += each;
            break;
        }
        cur -= res * sz;
        ll r = uf.merge(i1, i2);
        D[r] = d1 + res;
        que.push({D[r], r});
    }
    rep(i, N) {
        A[i] = D[uf.find(i)] * K + A[i] % K;
    }
    while (que.size()) que.pop();

    if (uf.size() == 1) {
        auto [d, m] = divmod(cur, N);
        rep(i, N) {
            A[i] += d * K;
        }
        cur = m;
    }
    // ここからは愚直シミュ
    rep(i, N) {
        que.push({A[i], i});
    }
    rep(_, cur) {
        auto [a, i] = que.pop();
        a += K;
        que.push({a, i});
    }

    vector<ll> ans(N);
    while (que.size()) {
        auto [a, i] = que.pop();
        ans[i] = a;
    }
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
