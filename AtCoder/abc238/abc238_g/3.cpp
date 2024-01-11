/*
参考：https://trap.jp/post/1594/
ライブラリ整備：Zobrist Hash
・(素因数,指数 mod 3)を状態としてハッシュを作る。
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

#include "numbers/Eratosthenes.hpp"
#include "common/randrange.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    const int M = 1000000;
    Eratosthenes era(M);
    auto table = listnd(M + 1, 3, 0LL);
    rep(i, M + 1) {
        rep(j, 3) {
            table[i][j] = randrange(0, INF);
        }
    }
    vector<ll> C(M + 1);
    vector<ll> hash(N + 1);
    ll cur = 0;
    rep(i, N) {
        for (auto [k, v] : era.factorize(A[i])) {
            // 前の状態を消す
            cur ^= table[k][C[k]];
            C[k] = (C[k] + v) % 3;
            // 新しい状態に更新
            cur ^= table[k][C[k]];
        }
        // ここまでの累積のhash
        hash[i + 1] = cur;
    }

    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        YesNo(hash[l] == hash[r]);
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
