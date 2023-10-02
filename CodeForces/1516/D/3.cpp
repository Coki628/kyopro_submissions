/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・これは普通にやるとできなかった。左端を軸にしたかったから。
　でも後ろから回したら問題なくできた。その手間を織り込んでも、
　やっぱり添字が複雑に動かないメリットは大きいように思った。
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

#include "common/Doubling.hpp"

auto f = [](int prev, int power) {
    return power;
};

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    vector<int> nxt(N + 1);
    map<ll, ll> C;
    deque<ll> que;
    // 後ろから回せば左端を軸にしたい時も使える
    rep(i, N - 1, -1, -1) {
        que.eb(A[i]);
        ll ngcnt = 0;
        for (auto [k, v] : factorize(A[i])) {
            C[k]++;
            if (C[k] == 2) {
                ngcnt++;
            }
        }
        while (que.size() and ngcnt > 0) {
            for (auto [k, v] : factorize(que.front())) {
                C[k]--;
                if (C[k] == 1) {
                    ngcnt--;
                }
            }
            que.pop_front();
        }
        nxt[i] = i + que.size();
    }
    nxt[N] = N;
    auto db = get_doubling(17, nxt, -1, f);

    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        ll res = db.times(l, r);
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
