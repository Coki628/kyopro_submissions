/*
・自力AC。
・特に考察とか難しいことはないんだけど、
　実装するのはまあまあめんどいみたいな感じだった。
　問題誤読で2ペナもらったのは悲しい。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(M);
    cin >> A;
    vector<string> mat(N);
    cin >> mat;

    vector<ll> init(N);
    rep(i, N) {
        init[i] += i + 1;
        rep(j, M) {
            if (mat[i][j] == 'o') {
                init[i] += A[j];
            }
        }
    }

    rep(p, N) {
        vector<ll> vec;
        rep(i, N) {
            if (p == i) continue;
            vec.eb(init[i]);
        }
        ll mx = max(vec);
        vector<ll> rest;
        rep(j, M) {
            if (mat[p][j] == 'x') {
                rest.eb(A[j]);
            }
        }
        sort(rest.rbegin(), rest.rend());
        ll cur = init[p];
        ll need = 0;
        if (cur > mx) {
            print(need);
        } else {
            rep(i, rest.size()) {
                need++;
                cur += rest[i];
                if (cur > mx) {
                    print(need);
                    break;
                }
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
